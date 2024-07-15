
/*bin version: it creates a new file and ask to populate with temperature data
It also read a file and ask to update it, showing the new data at Console
07/2024 by rafamuratt
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/

#include <stdio.h>
#include <stdlib.h>

#define samples 10

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/
// Global variables

float value[samples];                                                          // store the new temperatures
int tempNumber = 1;                                                            // to print the temperature numbers
short choice;                                                                  // choice to update data or not
FILE *file;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/

int main() {
	register i;
	
	file = fopen("celsius.dat", "rb");                                         // set to read binary data

	if(file == NULL){
		fclose(file);
		printf("\n\nFile not found, a new file celsius.dat has been created.\n");
		printf("There's no temperature's data recorded.\n");
		file = fopen("celsius.dat","wb");                                      // set to write binary data
    }
    
    else{
    	putchar('\n');
	    printf("The previous temperatures are:\n");	           
		fread(value, sizeof(float), samples, file);                            // write the binary data
				
			for(i=0; i < samples; i++){
				printf("Temperature %2d: %.2f'C\n", tempNumber, value[i]);     // print at console the formatted output
    			tempNumber++;
			}
				
		fclose(file);
	}

	putchar('\n');
	printf("Do you want to update them? (Y/N) ");
	scanf("%c", &choice);
	
	if(choice == 'y' || choice == 'Y'){
		fclose(file);
    	    file = fopen("celsius.dat","wb");
    	    		
			for(i=0; i < samples; i++){                                        // get the new data and store at matrix
				printf("Temperature %2d aqquired ('C): ", i+1);
				scanf ("%f", &value[i]);
			}
				fwrite(value, sizeof(float), samples, file);
	
	
	        fclose(file);
	        putchar('\n');
			
			printf("The temperatures now are:\n");
			file = fopen("celsius.dat", "rb");
			tempNumber = 1;
			
			fread(value, sizeof(float), samples, file);
				
				for(i=0; i < samples; i++){
					printf("Temperature %2d: %.2f'C\n", tempNumber, value[i]);     
        			tempNumber++;
			}
				
			fclose(file);
			printf("\nThe program will now quit.\n\n");
	        putchar('\n');
	}
	    
    else{
    	fclose(file);
    	printf("\nNo changes has been made, the program will now quit.\n\n");
	}
	    	
	system("pause");
	return 0;
}
