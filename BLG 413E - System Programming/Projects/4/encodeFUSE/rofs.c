/*
 * ROFS - The read-only filesystem for FUSE.
 * Copyright 2005,2006,2008 Matthew Keller. kellermg@potsdam.edu and others.
 * v2008.09.24
 *
 * Mount any filesytem, or folder tree read-only, anywhere else.
 * No warranties. No guarantees. No lawyers.
 *
 * I read (and borrowed) a lot of other FUSE code to write this.
 * Similarities possibly exist- Wholesale reuse as well of other GPL code.
 * Special mention to Rémi Flament and his loggedfs.
 *
 * Consider this code GPLv2.
 *
 * Compile: gcc rofs.c -o rofs -Wall -ansi -W -std=c99 -g -ggdb -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -lfuse 
 * Mount: rofs readwrite_filesystem mount_point
 *
 */


#define FUSE_USE_VERSION 26

static const char* rofsVersion = "2008.09.24";

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <unistd.h>
#include <fuse.h>

#include <iconv.h>

#define UTF32 1
#define UTF8 2
#define UTF16 3
#define ISO8859_1 4
#define ISO8859_9 5

// Global to store our read-write path
char *rw_path;


//****************** Encoding Functions

void printBuffer(const char *buffer, const size_t bufferLen) {
	int i;
	for (i = 0; i < bufferLen; i++) {
		printf("%02x ", 0xff & buffer[i]);
	}
	printf("\n");
}


ssize_t encod(char **outputBuffer, char *inputBuffer, const size_t inputLen, const char *from, const char *to, const float multiplier) {
	iconv_t conv = iconv_open(to, from);
	if (conv == (iconv_t) -1) {
		printf("Conversion is not supported");
	}
	size_t ibl = inputLen;
	size_t obl = inputLen * multiplier * 2;
	char *converted = (char *) calloc(obl+1, sizeof(char));
	char *temp = converted;

	int enableTransliteration = 1;
	iconvctl (conv, ICONV_SET_TRANSLITERATE, &enableTransliteration);

	int enableILSEQ = 1;
	iconvctl (conv, ICONV_SET_DISCARD_ILSEQ, &enableILSEQ);

	int ret = iconv(conv, &inputBuffer, &ibl, &converted, &obl);
	if (ret == (size_t) -1) {
		perror("iconv");
	}
	iconv_close(conv);

	int resize;
	for (resize = obl; temp[resize] != 0x0a; resize--);
	resize++;
	if(!strncmp(to,"UTF-32",6)){
		resize += (4 - (resize % 4)) % 4;
	}
	else if(!strncmp(to,"UTF-16",6)){
		resize += (2 - (resize % 2)) % 2;
	}

	temp = (char *) realloc (temp, resize * sizeof(char));

	char *tempFinal =  (char *) calloc(resize+20, sizeof(char));	
	int size = 0;
	if(!strncmp(to,"UTF-16",6)){
		int i;
		for (i = 0; i < resize; i += 2){
			if ((temp[i] == 0x73) &&  (temp[i+2] == 0x65) && (temp[i+4] == 0x74) && (temp[i+6] == 0x3d) && (temp[i+8] == 0x22) ){
				i += 10;
				break;
			}
		}
		
		int j;
		for (j = 0; j < i; j++ )
			tempFinal[j] = temp[j];

		char encodStr[] = "UTF-16";
		int k;
		for (k = 0; k < strlen(encodStr); k++, j += 2 ){
			tempFinal[j] = encodStr[k];
		}

		while(temp[i] != '"')
			i++;
		
		for ( ; i < resize; i++, j++ )
			tempFinal[j] = temp[i]; 		
		size = j;
	}
	else if(!strncmp(to,"UTF-32",6)){
		int i;
		for (i = 3; i < resize; i += 4){
			if ((temp[i] == 0x73) &&  (temp[i+4] == 0x65) && (temp[i+8] == 0x74) && (temp[i+12] == 0x3d) && (temp[i+16] == 0x22) ){
				i += 20;
				break;
			}
		}
		
		int j;
		for (j = 0; j < i; j++ )
			tempFinal[j] = temp[j];

		char encodStr[] = "UTF-32";
		int k;
		for (k = 0; k < strlen(encodStr); k++, j += 4 ){
			tempFinal[j] = encodStr[k];
		}

		while(temp[i] != '"')
			i++;
		
		for ( ; i < resize; i++, j++ )
			tempFinal[j] = temp[i]; 		
		size = j;	
	}
	else{
		char *find = strstr(temp,"charset=\"");
		find += 9;
		int  i = find - temp;
		int j;
		
		for (j = 0; j < i; j++ )
			tempFinal[j] = temp[j];

		if(!strcmp(to,"UTF-8")){
			strcat(tempFinal,"UTF-8");
			j += 5;
		}
		else if(!strcmp(to,"ISO-8859-9")){
			strcat(tempFinal,"iso8859-9");
			j += 9;
		}
		else if(!strcmp(to,"ISO-8859-1")){
			strcat(tempFinal,"iso8859-1");
			j += 9;
		}
		
		while(temp[i] != '"')
			i++;
		
		for ( ; i < resize; i++, j++ )
			tempFinal[j] = temp[i]; 
		
		size = j;
	}
	
	free(temp);
	
	*outputBuffer = tempFinal;
	return size;
}

int findEncoding(char *buffer, size_t s){
	if(strstr(buffer, "UTF-8")){
		return UTF8;
	}
	else if(strstr(buffer, "iso8859-1")){
		return ISO8859_1;
	}
	else if(strstr(buffer, "iso8859-9")){
		return ISO8859_9;
	}	
	else if ((buffer[0] == 0x00) && (buffer[1] == 0x00)){
		int i;
		for (i = 3; i < s; i += 4){
			if ((buffer[i] == 0x55) &&  (buffer[i+4] == 0x54) && (buffer[i+8] == 0x46) && (buffer[i+12] == 0x2d) && (buffer[i+16] == 0x33) && (buffer[i+20] == 0x32) )
				return UTF32;
		}
	}
	else{
		int i;
		for (i = 0; i < s; i += 2){
			if ((buffer[i] == 0x55) &&  (buffer[i+2] == 0x54) && (buffer[i+4] == 0x46) && (buffer[i+6] == 0x2d) && (buffer[i+8] == 0x31) && (buffer[i+10] == 0x36) )
				return UTF16;
		}
	}
	return -1;

}

//********************************


/******************************
*
* Callbacks for FUSE
*
******************************/

static int rofs_getattr(char *path, struct stat *st_data)
{
    int res;

    memset(st_data, 0, sizeof(struct stat));

    if (!strcmp(path, "/") || !strcmp(path, "/UTF8") || !strcmp(path, "/UTF16") || !strcmp(path, "/UTF32") || !strcmp(path, "/iso8859-1") || !strcmp(path, "/iso8859-9") ) {
        st_data->st_mode = S_IFDIR | 0755;
        st_data->st_nlink = 2;
    }
	else{
		if (path[strlen(path)-1]== '/') {
			path[strlen(path)-1]= '\0';
		}

		int i, slashNumber = 0;
		for (i = 0; i < strlen(path); i++){
			if (path[i] == '/')
				slashNumber++;
		}
		
		if (slashNumber < 2){
			return -ENOENT;
		}

		char *originalFileName, *originalFilePath;
		
		originalFileName = strtok(path, "/");		
		originalFileName = strtok(NULL, "/");
		
		originalFilePath = malloc(sizeof(char)*(strlen(originalFileName) + strlen(rw_path)+ 1));

		strcpy(originalFilePath,rw_path);
		strcat(originalFilePath,originalFileName);
						
		res = lstat(originalFilePath, st_data);
		
		if (!strncmp(path+1,"UTF",3)){
			st_data->st_size *= 4;
		}
		else {
			st_data->st_size += 5;
		}

		printf("\n***@getattr Path: %s rw: %s original path: %s size: %d\n\n", path, rw_path, originalFilePath, st_data->st_size);
		free(originalFilePath);
		
		if(res == -1) {
			return -errno;
		}
	}
    return 0;
}

static int rofs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi)
{
    DIR *dp;
    struct dirent *de;
    int res;

    (void) offset;
    (void) fi;

    if (strcmp(path, "/") == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "UTF8", NULL, 0 );
		filler(buf, "UTF16", NULL, 0 );
		filler(buf, "UTF32", NULL, 0 );
		filler(buf, "iso8859-1", NULL, 0 );
		filler(buf, "iso8859-9", NULL, 0 );
	}
	else{
		dp = opendir(rw_path);
		if(dp == NULL) {
			res = -errno;
			return res;
		}

		while((de = readdir(dp)) != NULL) {
			struct stat st;
			memset(&st, 0, sizeof(st));
			st.st_ino = de->d_ino;
			st.st_mode = de->d_type << 12;
						
			if (filler(buf, de->d_name, &st, 0))
				break;
		}
		closedir(dp);
	}

    return 0;
}

static int rofs_open(char *path, struct fuse_file_info *finfo)
{
    int res;

    /* We allow opens, unless they're tring to write, sneaky
     * people.
     */
    int flags = finfo->flags;

    if ((flags & O_WRONLY) || (flags & O_RDWR) || (flags & O_CREAT) || (flags & O_EXCL) || (flags & O_TRUNC) || (flags & O_APPEND)) {
        return -EROFS;
    }

	if (strcmp(path, "/") && (path[strlen(path)-1]== '/')) {
		path[strlen(path)-1]= '\0';
	}
	int i, slashNumber = 0;
	for (i = 0; i < strlen(path); i++){
		if (path[i] == '/')
			slashNumber++;
	}
	if (slashNumber < 2){
		return -ENOENT;
	}
	char *originalFileName, *originalFilePath;
	originalFileName = strtok(path, "/");		
	originalFileName = strtok(NULL, "/");
	originalFilePath = malloc(sizeof(char)*(strlen(originalFileName) + strlen(rw_path)+ 1));
	strcpy(originalFilePath,rw_path);
	strcat(originalFilePath,originalFileName);

    res = open(originalFilePath, flags);

    free(originalFilePath);
    if(res == -1) {
        return -errno;
    }
    close(res);
    return 0;
}

static int rofs_read(char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *finfo)
{
    int fd;
    int res;
    (void)finfo;
    
	if (strcmp(path, "/") && (path[strlen(path)-1]== '/')) {
		path[strlen(path)-1]= '\0';
	}
	int i, slashNumber = 0;
	for (i = 0; i < strlen(path); i++){
		if (path[i] == '/')
			slashNumber++;
	}
	if (slashNumber < 2){
		return -ENOENT;
	}
	char *originalFileName, *originalFilePath;
	originalFileName = strtok(path, "/");		
	originalFileName = strtok(NULL, "/");
	originalFilePath = malloc(sizeof(char)*(strlen(originalFileName) + strlen(rw_path)+ 1));
	strcpy(originalFilePath,rw_path);
	strcat(originalFilePath,originalFileName);
    
    fd = open(originalFilePath, O_RDONLY);
    if(fd == -1) {
        res = -errno;
        return res;
    }
    
    int fileSize =  lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);
    
    size = fileSize;
    
    char *inputBuffer = malloc(size * sizeof(char));
    
    res = pread(fd, inputBuffer, size, offset);
    if(res == -1) {
        res = -errno;
    }
    close(fd);

	int inputEncoding = findEncoding(inputBuffer, size);
	
	int outputEncoding = -1;
	if (!strcmp(path+1,"UTF8")){
		outputEncoding = UTF8;
	}
	else if (!strcmp(path+1,"UTF16")){
		outputEncoding = UTF16;
	}
	else if (!strcmp(path+1,"UTF32")){
		outputEncoding = UTF32;
	}
	else if (!strcmp(path+1,"iso8859-1")){
		outputEncoding = ISO8859_1;
	}
	else if (!strcmp(path+1,"iso8859-9")){
		outputEncoding = ISO8859_9;
	}
	
	printf("\n***@read Encoding input: %d  output: %d\n", inputEncoding, outputEncoding);

	char *outputBuffer;
	size_t outputBufferLen;
	size_t inputBufferLen = size;
	
	if ((inputEncoding == UTF32) && (outputEncoding == UTF32)) {
		for (; inputBuffer[inputBufferLen] != 0x0a; inputBufferLen--);
		inputBufferLen++;
		outputBufferLen = inputBufferLen;
		outputBuffer = inputBuffer;
	} else if ((inputEncoding == UTF32) && (outputEncoding == UTF8)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-32BE", "UTF-8", 1);
	} else if ((inputEncoding == UTF32) && (outputEncoding == UTF16)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-32BE", "UTF-16LE", 1);
	} else if ((inputEncoding == UTF32) && (outputEncoding == ISO8859_1)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-32BE", "ISO-8859-1", 0.25);
	} else if ((inputEncoding == UTF32) && (outputEncoding == ISO8859_9)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-32BE", "ISO-8859-9", 0.25);
	} else if ((inputEncoding == UTF8) && (outputEncoding == UTF32)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-8", "UTF-32BE", 4);
	} else if ((inputEncoding == UTF8) && (outputEncoding == UTF8)) {
		for (; inputBuffer[inputBufferLen] != 0x0a; inputBufferLen--);
		inputBufferLen++;
		outputBufferLen = inputBufferLen;
		outputBuffer = inputBuffer;
	} else if ((inputEncoding == UTF8) && (outputEncoding == UTF16)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-8", "UTF-16LE", 2);
	} else if ((inputEncoding == UTF8) && (outputEncoding == ISO8859_1)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-8", "ISO-8859-1", 1);
	} else if ((inputEncoding == UTF8) && (outputEncoding == ISO8859_9)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-8", "ISO-8859-9", 1);
	} else if ((inputEncoding == UTF16) && (outputEncoding == UTF32)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-16LE", "UTF-32BE", 2);
	} else if ((inputEncoding == UTF16) && (outputEncoding == UTF8)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-16LE", "UTF-8", 1);
	} else if ((inputEncoding == UTF16) && (outputEncoding == UTF16)) {
		for (; inputBuffer[inputBufferLen] != 0x0a; inputBufferLen--);
		inputBufferLen++;
		outputBufferLen = inputBufferLen;
		outputBuffer = inputBuffer;
	} else if ((inputEncoding == UTF16) && (outputEncoding == ISO8859_1)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-16LE", "ISO-8859-1", 0.5);
	} else if ((inputEncoding == UTF16) && (outputEncoding == ISO8859_9)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "UTF-16LE", "ISO-8859-9", 0.5);
	} else if ((inputEncoding == ISO8859_1) && (outputEncoding == UTF32)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-1", "UTF-32BE", 4);
	} else if ((inputEncoding == ISO8859_1) && (outputEncoding == UTF8)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-1", "UTF-8", 4);
	} else if ((inputEncoding == ISO8859_1) && (outputEncoding == UTF16)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-1", "UTF-16LE", 4);
	} else if ((inputEncoding == ISO8859_1) && (outputEncoding == ISO8859_1)) {
		for (; inputBuffer[inputBufferLen] != 0x0a; inputBufferLen--);
		inputBufferLen++;
		outputBufferLen = inputBufferLen;
		outputBuffer = inputBuffer;
	} else if ((inputEncoding == ISO8859_1) && (outputEncoding == ISO8859_9)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-1", "ISO-8859-9", 1);
	} else if ((inputEncoding == ISO8859_9) && (outputEncoding == UTF32)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-9", "UTF-32BE", 4);
	} else if ((inputEncoding == ISO8859_9) && (outputEncoding == UTF8)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-9", "UTF-8", 4);
	} else if ((inputEncoding == ISO8859_9) && (outputEncoding == UTF16)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-9", "UTF-16LE", 4);
	} else if ((inputEncoding == ISO8859_9) && (outputEncoding == ISO8859_1)) {
		outputBufferLen = encod(&outputBuffer, inputBuffer, inputBufferLen, "ISO-8859-9", "ISO-8859-1", 1);
	} else if ((inputEncoding == ISO8859_9) && (outputEncoding == ISO8859_9)) {
		for (; inputBuffer[inputBufferLen] != 0x0a; inputBufferLen--);
		inputBufferLen++;
		outputBufferLen = inputBufferLen;
		outputBuffer = inputBuffer;
	} 
	
	size = outputBufferLen;
	memcpy(buf,outputBuffer,size);


	printf("***@read Size: %d Readed:\n", size);
	printBuffer(outputBuffer, size);
	
	free(originalFilePath);
    return outputBufferLen;
}

struct fuse_operations rofs_oper = {
    .getattr     = rofs_getattr,
    .readdir     = rofs_readdir,
    .open        = rofs_open,
    .read        = rofs_read,
};
enum {
    KEY_HELP,
    KEY_VERSION,
};

static void usage(const char* progname)
{
    fprintf(stdout,
            "usage: %s readwritepath mountpoint [options]\n"
            "\n"
            "   Mounts readwritepath as a read-only mount at mountpoint\n"
            "\n"
            "general options:\n"
            "   -o opt,[opt...]     mount options\n"
            "   -h  --help          print help\n"
            "   -V  --version       print version\n"
            "\n", progname);
}

static int rofs_parse_opt(void *data, const char *arg, int key,
                          struct fuse_args *outargs)
{
    (void) data;

    switch (key)
    {
    case FUSE_OPT_KEY_NONOPT:
        if (rw_path == 0)
        {
            rw_path = strdup(arg);
            return 0;
        }
        else
        {
            return 1;
        }
    case FUSE_OPT_KEY_OPT:
        return 1;
    case KEY_HELP:
        usage(outargs->argv[0]);
        exit(0);
    case KEY_VERSION:
        fprintf(stdout, "ROFS version %s\n", rofsVersion);
        exit(0);
    default:
        fprintf(stderr, "see `%s -h' for usage\n", outargs->argv[0]);
        exit(1);
    }
    return 1;
}

static struct fuse_opt rofs_opts[] = {
    FUSE_OPT_KEY("-h",          KEY_HELP),
    FUSE_OPT_KEY("--help",      KEY_HELP),
    FUSE_OPT_KEY("-V",          KEY_VERSION),
    FUSE_OPT_KEY("--version",   KEY_VERSION),
    FUSE_OPT_END
};

int main(int argc, char *argv[])
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    int res;

    res = fuse_opt_parse(&args, &rw_path, rofs_opts, rofs_parse_opt);
    if (res != 0)
    {
        fprintf(stderr, "Invalid arguments\n");
        fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
        exit(1);
    }
    if (rw_path == 0)
    {
        fprintf(stderr, "Missing readwritepath\n");
        fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
        exit(1);
    }

    fuse_main(args.argc, args.argv, &rofs_oper, NULL);

    return 0;
}
