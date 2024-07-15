
/*txt version: it creates a new file and ask to populate with temperature data
It also read a file and ask to update it, showing the new data at Console
07/2024 by rafamuratt
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                            // needed for strcspn function

#define samples 10

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/
// Global variables

float value[samples] = {};                                                     // store the new temperatures
char line[100];                                                                // Buffer to hold each line
int tempNumber = 1;                                                            // to print the temperature numbers
short choice;                                                                  // choice to update data or not
FILE *file;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------/

int main() {
	register i;
	
	file = fopen("celsius.txt", "r");                                          // set to read ASCII data

	if(file == NULL){
		fclose(file);
		printf("\n\nFile not found, a new file celsius.txt has been created.\n");
		printf("There's no temperature's data recorded.\n");
		file = fopen("celsius.txt","w");                                       // set to write ASCII data
    }
    
    else{
    	putchar('\n');
	    printf("The previous temperatures are:\n");
	
		while (fgets(line, sizeof(line), file) != NULL) {                      // Read each line from the file
		    line[strcspn(line, "\n")] = '\0';                                  // strcspn = string complement span. Here it find the newline character '\n' and replace with 
    		                                                                   // null '\0', so the printf keep 'C at same line after get temperature data from external file
			
			printf("Temperature %2d: %s'C\n", tempNumber, line);               // print at console the formatted output
    		tempNumber++;
    	}
	}

	putchar('\n');
	printf("Do you want to update them? (Y/N) ");
	scanf("%c", &choice);
	
	if(choice == 'y' || choice == 'Y'){
		fclose(file);
    	    file = fopen("celsius.txt","w");
    	    
    	    for(i=1; i < samples + 1; i++){                                    
				printf("Temperature %2d aqquired ('C): ", i);
				scanf ("%f", &value[i]);                                       // get the new data and store at matrix
				fprintf(file, "%.2f\n", value[i]);
			}
	
	        fclose(file);
	        putchar('\n');
			printf("The temperatures now are:\n");
			file = fopen("celsius.txt", "r");
			tempNumber = 1;
			
			while (fgets(line, sizeof(line), file) != NULL) {                  // Read each line from the file
			    line[strcspn(line, "\n")] = '\0';                                                           
				printf("Temperature %2d: %s'C\n", tempNumber, line);           // Print the formatted output
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
