#include <stdio.h>

int main(){
	char deviceName[] = "/dev/scull0";
	FILE *readDevice = fopen(deviceName, "rb");
	if(readDevice){
		printf("Device %s opened\n", deviceName);
		getchar();
		fclose(readDevice);
	}
	else{
		printf("Device %s could not be opened!\n", deviceName);
	}
	
    return 0;
}
