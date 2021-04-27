#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function Prototypes
 */
void setVolume(int volume);
int getVolume(void);

/*
 * Global Variables
 */
int masterVolAddr = 47; //0x2F
float lsbVal = pow(2,-24);

/*
 * Main function
 * Accepts either a get command or percentage value to set the volume
 */
int main (int argc, char** argv){
	if (argc != 2) {
		printf("Enter one argument, volume percentage between 0-100\n");
		exit(0);
	}
	if (!strcmp(argv[1], "get")){
		int i = getVolume();
	}
	else{
		// Convert String to Integer
		char *endptr;
		int value = strtol(argv[1], &endptr, 10);
		if (endptr == argv[2]){
			printf("Invalid Number\n");
		}
		else if (*endptr){
			printf("Trailing characters after number\n");
		}
		setVolume(value);
	}
	return 0;

}

/*
 * Set Volume
 * Converts percentage to dB value
 * Converts dB value to Linear
 * Converts to hexadecimal format for sending to the DSP
 * Calls DSP write function
 */
void setVolume(int volume){

	printf("Set volume to %d\n", volume);

	float dB = ((float)volume*0.8)-80;
	printf("dB volume level: %f\n", dB);

	float tmp = dB/20;
	float lin = pow(10, tmp);
	uint32_t binValue = lin/lsbVal;

	printf("Hex value of volume to DSP: 0x%.8x\n", binValue);

	char s[50];
	sprintf(s, "dsptoolkit write-mem 0x%x 0x%.8x", masterVolAddr, binValue); 
	system(s);
}

/*
 * Get Volume
 * Sends read command to DSP
 * Pipes output into buffer to extract value
 * Removes whitespace from returned value
 * Convert from Hex to Percentage
 */
int getVolume(){
	// Readback function
	char s[50];
	sprintf(s, "dsptoolkit read-hex 0x%x", masterVolAddr); 
	
	FILE *fp;
	char data[16];

	fp = popen(s, "r");
	if (fp == NULL) {
		printf("Failed to run command\n");
		exit(1);
	}

	while (fgets(data, sizeof(data), fp) != NULL) {
		printf("%s", data);
	}

	pclose(fp);
	
	// Remove Whitespace
	int j;
	char c = ' ';	
	for (int i=j=0; i<strlen(data); i++){
		if (data[i] != c){
			data[j++] = data[i];
		}
	}
	data[j] = '\0';

	// Data conversion
	uint32_t vol = strtol(data, NULL, 16);	
	printf("Hex value = %x\n", vol);
	float lin = (float)vol * lsbVal;
	float tmp = log10f(lin);
	float dB = tmp*20;

	printf("dB Value = %f\n", dB);

	int volume = ceil((dB+80)/0.8);

	printf("Volume = %d\n", volume);

	return 0;
}
