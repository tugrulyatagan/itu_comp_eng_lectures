#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "scull_ioctl.h"


void printBuffer(const char *buffer, long inputFileLen){
	int i;
	for (i=0; i <inputFileLen; i++ ){
		printf("%02x ", 0xff & buffer[i]);
	}
	printf("\n");
}

void writeToDevice(const char *inputFileName, const char *deviceName){
	long readFileLen;
	FILE *readFile = fopen(inputFileName, "rb");
	if (readFile == NULL){
		printf("%s ", inputFileName);
		perror("FILE COULD NOT BE OPENED!");
		exit(0);
	}
	fseek(readFile, 0, SEEK_END);
	readFileLen = ftell(readFile); 
	rewind(readFile);
    char *readFileBuffer = (char *)malloc((readFileLen+1)*sizeof(char));
    fread(readFileBuffer, readFileLen, 1, readFile);
    fclose(readFile);
	
	FILE *writeDevice = fopen(deviceName, "wb");
	fwrite(readFileBuffer, 1, readFileLen, writeDevice);
	fclose(writeDevice);

	printf("Read from input file %s and writen to device %s:\n", inputFileName, deviceName);
	printBuffer(readFileBuffer,readFileLen);
}

void readFromDevice(const char *outputFileName, const char *deviceName){
	char *readBuffer;
	long readBufferLen;
	FILE *readDevice = fopen(deviceName, "rb");
	fseek(readDevice, 0, SEEK_END);
	readBufferLen = ftell(readDevice); 
	rewind(readDevice);
    readBuffer = (char *)malloc((readBufferLen+1)*sizeof(char));
    fread(readBuffer, readBufferLen, 1, readDevice);
    fclose(readDevice);
   
   	FILE *writeFile = fopen(outputFileName, "wb");
   	if (writeFile == NULL){
		printf("%s ", outputFileName);
		perror("FILE %s COULD NOT BE OPENED!");
		exit(0);
	}
	fwrite(readBuffer, 1, readBufferLen, writeFile);
	fclose(writeFile);
   
    printf("Read from device %s and writen to output file %s:\n", deviceName, outputFileName);
	printBuffer(readBuffer,readBufferLen);	
}

void setioctl(char *deviceName, int command, int *argument){
	int ioctlDevice = open(deviceName, O_RDWR);
	if (ioctl(ioctlDevice, command, argument) == -1){
		printf("%s\n", strerror(errno));
	}
	close(ioctlDevice);
}

int main(){
	char deviceName[] = "/dev/scull0";
	char filename[20];
	int inputencoding, outputencoding;
	
	char choice;
	printf("SET INPUT ENCODING\n");
	printf("(1) for ISO8859-1\n");
    printf("(2) for ISO8859-9\n");
    printf("(3) for UTF8\n");
    printf("(4) for UTF16\n");
    printf("(5) for UTF32\n>>> ");
    scanf (" %c", &choice);
    
    if (choice == '1') {
		inputencoding = ISO8859_1;
		strcpy(filename, "iso8859-1.txt");
	}
	else if (choice == '2') {
		inputencoding = ISO8859_9;
		strcpy(filename, "iso8859-9.txt");
	}
	else if (choice == '3') {
		inputencoding = UTF8;
		strcpy(filename, "utf8.txt");
	}
	else if (choice == '4') {
		inputencoding = UTF16;
		strcpy(filename, "utf16.txt");
	}
	else if (choice == '5') {
		inputencoding = UTF32;
		strcpy(filename, "utf32.txt");
	}
	else{
		printf("Wrong option!\n");
		exit(0);
	}
	setioctl(deviceName, SCULL_IOCSINPUTENCODING, &inputencoding);
	
	printf("SET OUTPUT ENCODING\n");
	printf("(1) for ISO8859-1\n");
    printf("(2) for ISO8859-9\n");
    printf("(3) for UTF8\n");
    printf("(4) for UTF16\n");
    printf("(5) for UTF32\n>>> ");
    scanf (" %c", &choice);
    
    if (choice == '1') {
		outputencoding = ISO8859_1;
	}
	else if (choice == '2') {
		outputencoding = ISO8859_9;
	}
	else if (choice == '3') {
		outputencoding = UTF8;
	}
	else if (choice == '4') {
		outputencoding = UTF16;
	}
	else if (choice == '5') {
		outputencoding = UTF32;		
	}
	else{
		printf("Wrong option!\n");
		exit(0);
	}
	setioctl(deviceName, SCULL_IOCSOUTPUTENCODING, &outputencoding);
	
	writeToDevice(filename, deviceName);
	//writeToDevice("input.txt", deviceName);
	printf("\n");
	readFromDevice("output.txt", deviceName);
	return 0;
}
