#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/switch_to.h>		/* cli(), *_flags */
#include <asm/uaccess.h>	/* copy_*_user */

#include "scull_ioctl.h"

#define SCULL_MAJOR 0
#define SCULL_NR_DEVS 4
#define SCULL_QUANTUM 4096

int scull_major = SCULL_MAJOR;
int scull_minor = 0;
int scull_nr_devs = SCULL_NR_DEVS;
int scull_quantum = SCULL_QUANTUM;
int scull_inputEncoding = UTF8; // default inputEncoding
int scull_outputEncoding = UTF32; // default outputEncoding

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);

MODULE_AUTHOR("Alessandro Rubini, Jonathan Corbet");
MODULE_LICENSE("Dual BSD/GPL");

ssize_t iso8859_9toUTF32(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t iso8859_1toUTF32(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t UTF8toUTF32(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t UTF16toUTF32(char *deviceData, const char *userBuffer, size_t inputLen);

ssize_t UTF32toUTF32(char *deviceData, const char *userBuffer, size_t inputLen);

ssize_t UTF32toiso8859_9(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t UTF32toiso8859_1(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t UTF32toUTF8(char *deviceData, const char *userBuffer, size_t inputLen);
ssize_t UTF32toUTF16(char *deviceData, const char *userBuffer, size_t inputLen);


struct scull_dev {
    char *data;
    int quantum;
    unsigned long size;
    struct semaphore sem;
    struct cdev cdev;
	atomic_t scull_s_available;
};

struct scull_dev *scull_devices;


int scull_trim(struct scull_dev *dev) {
    if (dev->data) {
        kfree(dev->data);
    }
    dev->data = NULL;
    dev->quantum = scull_quantum;
    dev->size = 0;
    return 0;
}


int scull_open(struct inode *inode, struct file *filp) {
    struct scull_dev *dev;

    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filp->private_data = dev;

	if ((! atomic_dec_and_test (&dev->scull_s_available))){
		atomic_inc(&dev->scull_s_available);
		return -EBUSY; /* already open */
	}

    /* trim the device if open was write-only */
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
        if (down_interruptible(&dev->sem))
            return -ERESTARTSYS;
        scull_trim(dev);
        up(&dev->sem);
    }
    return 0;
}

int scull_release(struct inode *inode, struct file *filp) {
	struct scull_dev *dev;
    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	
	atomic_inc(&dev->scull_s_available); /* release the device */
    return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    struct scull_dev *dev = filp->private_data;
    int quantum = dev->quantum;
    int q_pos;
    size_t writenCount;
    ssize_t retval = 0;

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
    if (*f_pos >= dev->size)
        goto out;
    if (*f_pos + count > dev->size)
        count = dev->size - *f_pos;

    q_pos = (long) *f_pos;

    if (dev->data == NULL)
        goto out;

    /* read only up to the end of this quantum */
    if (count > quantum - q_pos)
        count = quantum - q_pos;


	char *userBuffer = kmalloc(count * sizeof(char), GFP_KERNEL);
    
	if (scull_outputEncoding == UTF32){ // utf32
		writenCount = UTF32toUTF32(userBuffer, dev->data + q_pos, count);
	}
	else if (scull_outputEncoding == UTF8){ // from utf32 to utf8
		writenCount = UTF32toUTF8(userBuffer, dev->data + q_pos, count);
	}
	else if (scull_outputEncoding == UTF16){ // from utf32 to utf16
		writenCount = UTF32toUTF16(userBuffer, dev->data + q_pos, count);
	}
	else if (scull_outputEncoding == ISO8859_1){ // from utf32 to iso8859-1
		writenCount = UTF32toiso8859_1(userBuffer, dev->data + q_pos, count);
	}
	else if (scull_outputEncoding == ISO8859_9){ // from utf32 to iso8859-9
		writenCount = UTF32toiso8859_9(userBuffer, dev->data + q_pos, count);
	}

	printk("count: %d, wcount: %d f_pos: %lld\n", count, writenCount, *f_pos);

    if (copy_to_user(buf, userBuffer, writenCount)) {
        retval = -EFAULT;
        goto out;
    }
    *f_pos += writenCount;
    retval = count;

	kfree(userBuffer);

  out:
    up(&dev->sem);
    return retval;
}


ssize_t scull_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos){
    struct scull_dev *dev = filp->private_data;
    int quantum = dev->quantum;
    int q_pos = (long) *f_pos;
    ssize_t retval = -ENOMEM;
    size_t writenCount;

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;

    if (*f_pos >= quantum) {
        retval = 0;
        goto out;
    }

    if (count > quantum - q_pos){
        retval = -ENOMEM;
        goto out;
	}
        
    printk("I: %d O: %d q: %d count: %d f_pos: %lld\n", scull_inputEncoding, scull_outputEncoding, quantum,  count, *f_pos);

    if (!dev->data) {
        dev->data = kmalloc(quantum * sizeof(char), GFP_KERNEL);
        if (!dev->data)
            goto out;
        memset(dev->data, 0, quantum * sizeof(char));
    }

	char *userBuffer = kmalloc(count * sizeof(char), GFP_KERNEL);
    if (copy_from_user(userBuffer, buf, count)) {
        retval = -EFAULT;
        goto out;
    }
	
	if (scull_inputEncoding == UTF32){ // utf32
		writenCount = UTF32toUTF32(dev->data + q_pos, userBuffer, count);
	}
	else if (scull_inputEncoding == UTF8){ // from utf8 to utf32
		writenCount = UTF8toUTF32(dev->data + q_pos, userBuffer, count);
	}
	else if (scull_inputEncoding == UTF16){ // from utf16 to utf32
		writenCount = UTF16toUTF32(dev->data + q_pos, userBuffer, count);
	}
	else if (scull_inputEncoding == ISO8859_1){ // from iso8859-1 to utf32
		writenCount = iso8859_1toUTF32(dev->data + q_pos, userBuffer, count);
	}
	else if (scull_inputEncoding == ISO8859_9){ // from iso8859-9 to utf32
		writenCount = iso8859_9toUTF32(dev->data + q_pos, userBuffer, count);
	}

	kfree(userBuffer);
    
    *f_pos += writenCount;
    retval = count;

    /* update the size */
    if (dev->size < *f_pos)
        dev->size = *f_pos;

  out:
    up(&dev->sem);
    return retval;
}

long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
	int err = 0, tmp;
	int retval = 0;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
	  case SCULL_IOCRESET:
		scull_quantum = SCULL_QUANTUM;
		scull_inputEncoding = UTF8; // default inputEncoding
		scull_outputEncoding = UTF32; // default outputEncoding
		break;

	  case SCULL_IOCSQUANTUM: /* Set: arg points to the value */
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_quantum, (int __user *)arg);
		break;

	  case SCULL_IOCGQUANTUM: /* Get: arg is pointer to result */
		retval = __put_user(scull_quantum, (int __user *)arg);
		break;

	  case SCULL_IOCSINPUTENCODING: /* Set: arg points to the value */
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_inputEncoding, (int __user *)arg);
		break;

	  case SCULL_IOCGINPUTENCODING: /* Get: arg is pointer to result */
		retval = __put_user(scull_inputEncoding, (int __user *)arg);
		break;

	  case SCULL_IOCSOUTPUTENCODING: /* Set: arg points to the value */
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_outputEncoding, (int __user *)arg);
		break;

	  case SCULL_IOCGOUTPUTENCODING: /* Get: arg is pointer to result */
		retval = __put_user(scull_outputEncoding, (int __user *)arg);
		break;

	  default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;
}


loff_t scull_llseek(struct file *filp, loff_t off, int whence){
    struct scull_dev *dev = filp->private_data;
    loff_t newpos;

    switch(whence) {
        case 0: /* SEEK_SET */
            newpos = off;
            break;

        case 1: /* SEEK_CUR */
            newpos = filp->f_pos + off;
            break;

        case 2: /* SEEK_END */
			if (scull_outputEncoding == UTF16){
				newpos = dev->size/2 + off;
			}
			else if (scull_outputEncoding == UTF32){
				newpos = dev->size + off;
			}
			else{
				size_t writenCount;
				if (scull_outputEncoding == UTF8){ // from utf32 to utf8
					char *userBuffer = kmalloc(dev->size * sizeof(char), GFP_KERNEL);
					writenCount = UTF32toUTF8(userBuffer, dev->data, dev->size);
					kfree(userBuffer);
					newpos = (loff_t)writenCount + off;
				}
				else{
					newpos = dev->size/4 + off;
				}
			}
            break;

        default: /* can't happen */
            return -EINVAL;
    }
    if (newpos < 0)
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}


struct file_operations scull_fops = {
    .owner =    THIS_MODULE,
    .llseek =   scull_llseek,
    .read =     scull_read,
    .write =    scull_write,
    .unlocked_ioctl =  scull_ioctl,
    .open =     scull_open,
    .release =  scull_release,
};


void scull_cleanup_module(void){
    int i;
    dev_t devno = MKDEV(scull_major, scull_minor);

    if (scull_devices) {
        for (i = 0; i < scull_nr_devs; i++) {
            scull_trim(scull_devices + i);
            cdev_del(&scull_devices[i].cdev);
        }
    kfree(scull_devices);
    }

    unregister_chrdev_region(devno, scull_nr_devs);
}


int scull_init_module(void){
    int result, i;
    int err;
    dev_t devno = 0;
    struct scull_dev *dev;

    if (scull_major) {
        devno = MKDEV(scull_major, scull_minor);
        result = register_chrdev_region(devno, scull_nr_devs, "scull");
    } else {
        result = alloc_chrdev_region(&devno, scull_minor, scull_nr_devs,
                                     "scull");
        scull_major = MAJOR(devno);
    }
    if (result < 0) {
        printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
        return result;
    }

    scull_devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev),
                            GFP_KERNEL);
    if (!scull_devices) {
        result = -ENOMEM;
        goto fail;
    }
    memset(scull_devices, 0, scull_nr_devs * sizeof(struct scull_dev));

    /* Initialize each device. */
    for (i = 0; i < scull_nr_devs; i++) {
        dev = &scull_devices[i];
        dev->quantum = scull_quantum;
        sema_init(&dev->sem,1);
        atomic_set(&dev->scull_s_available,1);
        devno = MKDEV(scull_major, scull_minor + i);
        cdev_init(&dev->cdev, &scull_fops);
        dev->cdev.owner = THIS_MODULE;
        dev->cdev.ops = &scull_fops;
        err = cdev_add(&dev->cdev, devno, 1);
        if (err)
            printk(KERN_NOTICE "Error %d adding scull%d", err, i);
    }

    return 0; /* succeed */

  fail:
    scull_cleanup_module();
    return result;
}

// Encoding Functions 
// **************************************

ssize_t iso8859_9toUTF32(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = 4 * inputLen;
	char *deviceTemp = deviceData;
    int i;
    for(i = 0; i < inputLen; i++ ){		
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		char* temp = 0xff & userBuffer[i];
		if((userBuffer[i] & 0x80) && !(temp == 0xc7 || temp == 0xe7 || temp == 0xf6 ||
		    temp == 0xfc || temp == 0xdc || temp == 0xd6)){				
						
			if(temp == 0xde || temp == 0xf0 || temp == 0xfe ||
			   temp == 0xfd || temp == 0xd0 || temp == 0xdd)
			{			
				*deviceTemp--;
				*deviceTemp++ = 0x01;
				switch(0xff & userBuffer[i])
				{
					case 0xde:
						*deviceTemp++ = 0x5e;
						break;
					case 0xf0:
						*deviceTemp++ = 0x1f;						
						break;
					case 0xfe:
						*deviceTemp++ = 0x5f;
						break;
					case 0xfd:
						*deviceTemp++ = 0x31;
						break;
					case 0xd0:
						*deviceTemp++ = 0x1e;
						break;
					case 0xdd:
						*deviceTemp++ = 0x30;
						break;						
				}
			}
			else
			{
				*deviceTemp++ = 0xa4;
			}			
		}
		else{ 
			*deviceTemp++ = userBuffer[i];
		}
	}    
	return outputLen;
}

ssize_t iso8859_1toUTF32(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = 4 * inputLen;
	char *deviceTemp = deviceData;
    int i;
    for(i = 0; i < inputLen; i++ ){		
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		char* temp = 0xff & userBuffer[i];
		if((userBuffer[i] & 0x80) && !(temp == 0xc7 || temp == 0xe7 || temp == 0xf6 ||
		    temp == 0xfc)){	
			
			*deviceTemp++ = 0xa4;						
		}
		else{ 
			*deviceTemp++ = userBuffer[i];
		}
	}    
	return outputLen;
}

ssize_t UTF8toUTF32(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = 4 * inputLen;
	char *deviceTemp = deviceData;
    int i;
    for(i = 0; i < inputLen; i++ ){		
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		char* temp = 0xff & userBuffer[i];
		//printf("%02x\n",temp);
		if(userBuffer[i] & 0x80){
			if(temp == 0xc3 || temp == 0xc4 || temp == 0xc5)
			{			
				*deviceTemp--;
				i++;
				outputLen = outputLen - 4;
				if(temp == 0xc3)
				{
					*deviceTemp++ = 0x00;										
					switch(0xff & userBuffer[i])
					{
						case 0x87:
							*deviceTemp++ = 0xc7;		
							break;	
						case 0xa7:
							*deviceTemp++ = 0xe7;		
							break;	
						case 0x9c:
							*deviceTemp++ = 0xdc;		
							break;	
						case 0xbc:
							*deviceTemp++ = 0xfc;		
							break;	
						case 0x96:						
							*deviceTemp++ = 0xd6;		
							break;	
						case 0xb6:
							*deviceTemp++ = 0xf6;		
							break;	
					}
				}
				else if(temp == 0xc4)
				{
					*deviceTemp++ = 0x01;										
					switch(0xff & userBuffer[i])
					{
						case 0x9e:
							*deviceTemp++ = 0x1e;		
							break;	
						case 0x9f:
							*deviceTemp++ = 0x1f;		
							break;	
						case 0xb0:
							*deviceTemp++ = 0x30;		
							break;	
						case 0xb1:
							*deviceTemp++ = 0x31;		
							break;						
					}
				}
				else if(temp == 0xc5)
				{
					*deviceTemp++ = 0x01;										
					switch(0xff & userBuffer[i])
					{
						case 0x9e:
							*deviceTemp++ = 0x5e;	
							break;	
						case 0x9f:
							*deviceTemp++ = 0x5f;		
							break;							
					}
				}
			}
			else
			{
				*deviceTemp++ = 0xa4;
			}			
		}
		else{ 
			*deviceTemp++ = userBuffer[i];
		}
	}    
	return outputLen;
}

ssize_t UTF16toUTF32(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = 2 * inputLen;
	char *deviceTemp = deviceData;
    int i;
    for(i = 0; i < inputLen; i++ ){		
		*deviceTemp++ = 0x00;
		*deviceTemp++ = 0x00;
		char* temp = 0xff & userBuffer[i];
			
		if(userBuffer[i] & 0x80){
			if(temp == 0xc3 || temp == 0xc4 || temp == 0xc5)
			{
				*deviceTemp++ = userBuffer[i];
				i++;				
				*deviceTemp++ = userBuffer[i];				
			}
			else
			{
				*deviceTemp++ = 0xa4;
			}			
		}
		else{ 
			*deviceTemp++ = userBuffer[i];
			i++;			
			*deviceTemp++ = userBuffer[i];
		}
	}    
	return outputLen;
}

ssize_t UTF32toUTF32(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = inputLen;
	char *deviceTemp = deviceData;
    int i;
    for(i = 0; i < inputLen; i++ ){
		*deviceTemp++ = userBuffer[i];
	}
	return outputLen;
}

ssize_t UTF32toUTF8(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = inputLen / 4 ;
	char *deviceTemp = deviceData;
    int i;   			
    for(i = 0; i < inputLen; i++ ){		
		i++;
		i++;
		i++;
		char* temp = 0xff & userBuffer[i];
			
		if((userBuffer[i-1] == 0x01) || (userBuffer[i] & 0x80)){
						
			switch(0xff & userBuffer[i])
			{
				case 0x30:				
					*deviceTemp++ = 0xc4;
					*deviceTemp++ = 0xb0;
					break;
				case 0x31:				
					*deviceTemp++ = 0xc4;
					*deviceTemp++ = 0xb;
					break;
				case 0x1e:				
					*deviceTemp++ = 0xc4;
					*deviceTemp++ = 0x9e;
					break;
				case 0x1f:				
					*deviceTemp++ = 0xc4;
					*deviceTemp++ = 0x9f;
					break;
				case 0x5e:				
					*deviceTemp++ = 0xc5;
					*deviceTemp++ = 0x9e;
					break;
				case 0x5f:				
					*deviceTemp++ = 0xc5;
					*deviceTemp++ = 0x9f;
					break;
				case 0xc7:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0x87;
					break;
				case 0xe7:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0xa7;
					break;
				case 0xdc:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0x9c;
					break;
				case 0xfc:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0xbc;
					break;
				case 0xd6:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0x96;
					break;
				case 0xf6:				
					*deviceTemp++ = 0xc3;
					*deviceTemp++ = 0xb6;
					break;
				default:				
					*deviceTemp++ = 0xa4;
					break;
			}
			outputLen++;
		}
		else{ 
			*deviceTemp++ = userBuffer[i];			
		}
	}    
	return outputLen;	
}

ssize_t UTF32toUTF16(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = inputLen / 2;
	char *deviceTemp = deviceData;
    int i;			
    for(i = 0; i < inputLen; i++ ){		
		i++;
		i++;
		char* temp = 0xff & userBuffer[i];
			
		if(userBuffer[i] & 0x80){
			if(temp == 0xc3 || temp == 0xc4 || temp == 0xc5)
			{
				*deviceTemp++ = userBuffer[i];
				i++;				
				*deviceTemp++ = userBuffer[i];				
			}
			else
			{
				*deviceTemp++ = 0xa4;
			}			
		}
		else{ 
			*deviceTemp++ = userBuffer[i];
			i++;			
			*deviceTemp++ = userBuffer[i];
		}
	}    
	return outputLen;
}

ssize_t UTF32toiso8859_1(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = inputLen / 4 ;
	char *deviceTemp = deviceData;
    int i;   			
    for(i = 0; i < inputLen; i++ ){		
		i++;
		i++;
		i++;
		char* temp = 0xff & userBuffer[i];
			
		if(userBuffer[i-1] == 0x01){					
						
				*deviceTemp++ = 0xa4;
		}
		else{ 
			*deviceTemp++ = userBuffer[i];			
		}
	}    
	return outputLen;	
}

ssize_t UTF32toiso8859_9(char *deviceData, const char *userBuffer, size_t inputLen){
	ssize_t outputLen = inputLen / 4 ;
	char *deviceTemp = deviceData;
    int i;   			
    for(i = 0; i < inputLen; i++ ){		
		i++;
		i++;
		i++;
		char* temp = 0xff & userBuffer[i];
			
		if(userBuffer[i-1] == 0x01){
			
			switch(0xff & userBuffer[i])
				{
					case 0xe:
						*deviceTemp++ = 0xde;
						break;
					case 0x1f:
						*deviceTemp++ = 0xf0;						
						break;
					case 0x5f:
						*deviceTemp++ = 0xfe;
						break;
					case 0x31:
						*deviceTemp++ = 0xfd;
						break;
					case 0x1e:
						*deviceTemp++ = 0xd0;
						break;
					case 0x30:
						*deviceTemp++ = 0xdd;
						break;
					default:
						*deviceTemp++ = 0xa4;
						break;					
				}		
		}
		else{ 
			*deviceTemp++ = userBuffer[i];			
		}
	}    
	return outputLen;	
}


// **************************************

module_init(scull_init_module);
module_exit(scull_cleanup_module);
