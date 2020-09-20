#include <stdio.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

//#define KEY_LENGTH 2 // Can be anything from 1 to 13

int main(){
	unsigned char ch;
	FILE *fpIn, *fpOut;
	int i;
	unsigned char key[] = {0xBA, 0x1F, 0x91, 0xB2, 0x53, 0xCD, 0x3E};
	/* of course, I did not use the all-0s key to encrypt */

	fpIn = fopen("ptext.txt", "r");
	fpOut = fopen("ctext.txt", "w");
	i=0;
	while (fscanf(fpIn, "%c", &ch) != EOF) {
		/* avoid encrypting newline characters */
		/* In a "real-world" implementation of the Vigenere cipher,
		   every ASCII character in the plaintext would be encrypted.
		   However, I want to avoid encrypting newlines here because
		   it makes recovering the plaintext slightly more difficult... */
		/* ...and my goal is not to create "production-quality" code =) */
		if (ch!='\n') {
			fprintf(fpOut, "%02X", ch ^ key[i % NELEMS(key)]); // ^ is logical XOR
			//printf( "%c", ch ^ key[i % NELEMS(key)] ^ key[i % NELEMS(key)]); // ^ is logical XOR
			i++;
		}
	}

	fclose(fpIn);
	fclose(fpOut);
	return 0;
}
