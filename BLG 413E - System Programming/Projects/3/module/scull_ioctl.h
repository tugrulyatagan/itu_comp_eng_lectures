#ifndef __SCULL_H
#define __SCULL_H

#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */

#define SCULL_IOC_MAGIC  'k'
#define SCULL_IOCRESET    _IO(SCULL_IOC_MAGIC, 0)
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC,  1, int)
#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC,  2, int)
#define SCULL_IOCSINPUTENCODING _IOW(SCULL_IOC_MAGIC,  3, int)
#define SCULL_IOCGINPUTENCODING _IOR(SCULL_IOC_MAGIC,  4, int)
#define SCULL_IOCSOUTPUTENCODING _IOW(SCULL_IOC_MAGIC,  5, int)
#define SCULL_IOCGOUTPUTENCODING _IOR(SCULL_IOC_MAGIC,  6, int)
#define SCULL_IOC_MAXNR 6

#define UTF32 1
#define UTF8 2
#define UTF16 3
#define ISO8859_1 4
#define ISO8859_9 5

#endif
