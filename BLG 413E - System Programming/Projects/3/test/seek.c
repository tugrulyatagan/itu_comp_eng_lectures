#include <stdio.h>
#include <stdlib.h>

void printBuffer(const char *buffer, long inputFileLen){
	int i;
	for (i=0; i <inputFileLen; i++ ){
		printf("%02x ", 0xff & buffer[i]);
	}
	printf("\n");
}

int main(){
	char deviceName[] = "/dev/scull0";
	FILE *writeDevice = fopen(deviceName, "w+");
	fseek(writeDevice, 6, SEEK_SET);
	char writeChar[] = {0x00, 0x6d};
	fwrite(writeChar, sizeof(char), 2, writeDevice);
	fclose(writeDevice);
	
	
	char *readBuffer;
	long readBufferLen;
	FILE *readDevice = fopen(deviceName, "rb");

	fseek(readDevice, 0, SEEK_END);
	readBufferLen = ftell(readDevice); 
	rewind(readDevice);
	readBuffer = (char *)malloc((readBufferLen+1)*sizeof(char));
    fread(readBuffer, readBufferLen, 1, readDevice);
    fclose(readDevice);
    
    printBuffer(readBuffer, readBufferLen);

    return 0;
}
