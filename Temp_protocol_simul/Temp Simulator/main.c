/* ======================================================================================================================================================================
	Project: Protocol Simulator.
	version: 1.0
	Author: B.Eng A. Rafael Murat
	Data: March 2025
	
	This software convert up to two digits temperature data, its error status and unit (Celsius / Fahrenheit)	
	The output will show a protocol in 16 bits hexadecimal format.
	It also creates the 16 bits binary protocol (sensor ID, error state, unit and the temperature itself.
   =======================================================================================================================================================:::============ */
   
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Libraries */

#include <stdio.h>
#include <stdlib.h>   

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Function Prototypes */

void print_bin(unsigned int temp);                          // show the protocol data in binary format
void printError();                                          // error help

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Main Function */

int main() {
	
	unsigned char data[5];
	char loop = 0, newCk, errorCh, dataOK = 0, errorInput = 1;                                       
	
	unsigned int  sigScale, msg, error, temperature, digit1, digit2;
	

    while(!loop){
    	
		while(!dataOK){
			printf("\nEnter the temperature (-)XX\xF8 \bC (\xF8 \bF): ");	 
			gets(data);                                     // Examples of input data: 18°C, -18°C, 25°F
	
			
			if(data[0] >= 0x30 && data[0] <= 0x39){         // add the char '+' and displace the whole data index if the user do not type it for positive temperatures
				data[4] = data[3];
				data[3] = data[2];
				data[2] = data[1];
				data[1] = data[0];	
				data[0] = '+';
				
				                                            // make sure the input data is a number (0..9) and check if the unit is properly entered   
				if ((data[1] < 0x30 || data[1] > 0x39) ||
				    (data[2] < 0x30 || data[2] > 0x39) ||
			        (data[3] != 0xF8)||
				    (data[4] != 'C' && data[4] != 'c' && data[4] != 'F' && data[4] != 'f')){
				   		printError();
				   }
					 
				
				else
					dataOK = 1;
			}
			                                                // make sure the input data is a number (0..9) and check if the unit is properly entered		 			   
			else if((data[0] != '-') && (data[0] != '+') || (data[1] < 0x30 || data[1] > 0x39)
				                                         || (data[2] < 0x30 || data[2] > 0x39)
				                                         || (data[3] != 0xF8)
									                     || (data[4] != 'C' && data[4] != 'c' && data[4] != 'F' && data[4] != 'f')){
				   		printError();
				   }
	
			else
			 	dataOK = 1;                                 // control flag
		}
		
		
		while(errorInput){
			printf("Sensor error(Y/N)? ");
			scanf(" %c", &errorCh);
	
		
			if(errorCh == 'Y' || errorCh == 'y'){           // attribute an hex number if 'Y' or 'y'
				error = 0xA400;
				errorInput = 0;       
			} 
				
				
			else if(errorCh == 'N' || errorCh == 'n'){      // attribute an hex number if 'N' or 'n'
				error = 0xA000;
				errorInput = 0;
			}
			    
			    
			else
				errorInput = 1;
		}
		
		
			
		                                                                    // Data manipulation for temperature signals and scales:	
		if(data[0] == '+' && (data[4] == 'C' || data[4] == 'c'))             //1010 0000 0000 0000
			sigScale = 0xA000;
			
		else if (data[0] == '+' && (data[4] == 'F'|| data[4] == 'f'))        //1010 0001 0000 0000
			sigScale = 0xA100;
			
		else if (data[0] == '-' && (data[4] == 'C'|| data[4] == 'c'))        //1010 0010 0000 0000
			sigScale = 0xA200;
		
		else if (data[0] == '-' && (data[4] == 'F'|| data[4] == 'f'))        //1010 0011 0000 0000
			sigScale = 0xA300;
			
		
		                                                    // Convert ASCII characters to integers
	    digit1 = data[1] - '0';                             // Convert the second character to a digit 
	    digit2 = data[2] - '0';                             // Convert the third  character to a digit 
	
	    
	    temperature = (digit1 * 10) + digit2;               // Combine the two digits into a single number
			
		msg = error | sigScale | temperature;               // data manipulation for the final protocol composition
				 
		printf("\nSensor protocol in hex: %Xh\n\n", msg);
		
		print_bin(msg);
		
		printf("New check? (Y/N): ");
		scanf(" %c", &newCk);
		
		if((newCk == 'Y') || (newCk == 'y')){
			loop = 0;                                       // control flag
			dataOK = 0;                                     // control flag
			errorInput = 1;                                 // control flag
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
	printf("Please type in the following format: XX\xF8 \bC or -XX\xF8 \bC; XX\xF8 \bF or -XX\xF8 \bF,\n");
	printf("where 'XX' is your two digits temperature data.\n\n");
	system("PAUSE");
    system("cls");
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

