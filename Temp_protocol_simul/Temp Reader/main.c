
/* ======================================================================================================================================================================
	Project: Hex Protocol Reader.
	version: 1.0
	Author: B.Eng A. Rafael Murat
	Data: March 2025
	
	This software interpret 16 bits hexadecimal data, simulating a digital temperature sensor.
	The output will show the sensor ID, error state and the temperature (positive or negative, Celsius or Fahrenheit)
   =======================================================================================================================================================:::============ */
   
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Libraries */

#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Function Prototypes */

void print_bin(unsigned int temp);                          // show the protocal data in binary format
void printError();                                          // error help                                  


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Main Function */

int main(){
	unsigned char dataRead[3], tempHex[3];
	char signCh, unitCh, newCk, dataOK = 0, loop = 0;
	unsigned int tempDec, data0, data1, pos0, pos1, err, sign, unit, outBin;
	
	while(!loop){
	
		while(!dataOK){
			printf("\n16 bits protocol in hex (AXXXh): ");  // Examples of input data: A612h = -18°C with sensor error
			gets(dataRead);                                    
                                                            // make sure the input data is HEX (capital letters) ASCII
			if((dataRead[0] != 'A') || ((dataRead[1] < 0x30 || dataRead[1] > 0x39) && (dataRead[1] < 0x41 || dataRead[1] > 0x46))   
			                        || ((dataRead[2] < 0x30 || dataRead[2] > 0x39) && (dataRead[2] < 0x41 || dataRead[2] > 0x46))
			                        || ((dataRead[3] < 0x30 || dataRead[3] > 0x39) && (dataRead[3] < 0x41 || dataRead[3] > 0x46)))
			    printError();
			    
			else
				dataOK = 1;                                 // control flag
			}
			                                                
		tempHex[0] = dataRead[2];                          // data manipulation to interpret only the positions 2 and 3 as temperature data
		tempHex[1] = dataRead[3];                            
		tempHex[2] = '\0';
		
		sscanf(tempHex, "%x", &tempDec);                    // convert hex to decimal
					
		data0 = 0xA;                                        // atributes the sensor ID 0xA to data0
		pos0  = data0 << 12;                                // data manipulation for the correct protocol sequence
		data1 = dataRead[1] - '0';                          // convert char to decimal according with ASCII
		pos1  = (data1 << 8);                               // data manipulation for the correct protocol sequence
		
		
		
		err = data1 & 0x4;                                  // data manipulation to interpret only the positions 1 to identify the error status
		if(err == 0x4)
			printf("\nSensor status: ERROR, ");
			
		else
		    printf("\nSensor status: OK, ");
		
		
		    
		sign = data1 & 0x2;                                 // data manipulation to interpret only the positions 1 to identify the signal (+ or -)
		if(sign == 0x2)
			signCh = '-';
			
		else
		    signCh = '+';
		
		
		    
		unit = data1 & 0x1;                                 // data manipulation to interpret only the positions 1 to identify the unit (°C or °F)
		if(unit == 0x1)
			unitCh = 'F';
			
		else
		    unitCh = 'C';
		
		
	
		printf("temperature= %c%d\xF8%c\n\n", signCh, tempDec, unitCh);
			
			
		outBin = pos0 | pos1 | tempDec;                     // data manipulation for the final protocol composition
		
		print_bin(outBin);
	
			
		printf("New check? (Y/N): ");
		scanf(" %c", &newCk);
		
		if((newCk == 'Y') || (newCk == 'y')){
			loop = 0;                                       // control flag
			dataOK = 0;                                     // control flag
			while (getchar() != '\n');                      // Clear the buffer by consuming characters until newline is found
            system("cls");                                  // Clear the screen for the next sw run
		}
			
		else{
		    loop = 1;
		    dataOK = 1;
		}
			
   }

    	
	system("PAUSE");
	return 0;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Other Functions */

void print_bin(unsigned int temp){                          //show the protocol data in binary format
	register int i;
	
	printf("\n|SensorID|Err|S|U|  Temperature  |\n");
	printf("  ");
	
	for(i=15; i>=0; i--)
		(temp >> i) &1 ? printf("1 ") : printf("0 ");
	
	putchar(0x0A);                                          // another way to print a new line '\n'
	putchar(0x0A);
	
	puts(" -------------------------------------------- ");
	puts("| Error     : 01 = active,   00 = inative    |");
	puts("| S (signal):  0 = positive,  1 = negative   |");
	puts("| U (unit)  :  0 = Celsius,   1 = Fahrenheit |");
	puts(" -------------------------------------------- ");
	putchar('\n');
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printError(){                                          // error help
	printf("\nData format error.\n");
	printf("Please type using CAPITAL LETTERS in the following format: AXXX,\n");
	printf("where 'A' is the sensor ID and XXX is the protocol data in hexadecimal.\n\n");
	system("PAUSE");
    system("cls");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

