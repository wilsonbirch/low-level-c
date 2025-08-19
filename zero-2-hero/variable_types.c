#include <stdio.h>

int main(int argc, char *argv[]){
	
	int 			// 4 bytes, 32 bits
	char			// 1 byte, 8 bits
	short			// 2 bytes, 16 bits
	long long int 	// 8 byte, 64 bit

	// signed vars can be negative vs unsigned cannot be

	unsigned int x = 4;

	float f = 3.14;

	double d = 3.14159;

	// type casting

	int sx = (int)(x);

	unsinged int bigx  = 0xfffffefe; 	// this bigx int is 32 bits
	short kindabig = short(bigx);		// we can do this but stuffing 
										// 32 bits into a 16 bit type, 
										// there will be data loss, 
										// compiler should warn us

	float f = 3.14;
	int wasafloat = (int)f;				// rounds float to nearest int (3)


	(char *);
	(short *);
	short *mydata = (short*)argv[1];


}