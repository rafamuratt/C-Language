/* ===============================================================================================================
	Project: Hex Reader 
	A simulator of dinamic memory population using malloc and realloc resources 
	
	### Memory size limit is not implemented, caution is required if implemented on automatic data acquisition ###
	
	Version: 1.0
	Author: B. Eng Aroldo Rafael Murat
	Data: May 2025
   =============================================================================================================== */
   
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
	
	register int i = 0, j;
	char getData, input = 1;
	int limit;
	unsigned char *data = malloc(1);
	
	if (data == NULL) {
        puts("Initial memory allocation failed");
        return 1;
    }
	
	
	putchar('\n');
		
	while(input){                                         // while data acquisition is required
		printf("\nEnter the hex data: ");
		scanf(" %hhx", &data[i]);
		printf("Stop the data acquisition(Y/N)?: ");
		scanf(" %c", &getData);
		
		if(getData == 'n' || getData == 'N'){             // if data acquisition continues...
			i++;

			unsigned char *tmp = realloc(data, i + 1);    // dinamically increase the memory space as well
			
			if (tmp == NULL) {
                puts("Reallocation failed");
                free(data);
                return 2;
            }
            data = tmp;	
		}
		
		else{                                             // stop the acquisition
		    input = 0;
		    limit = i;
		}
	}
	
	
	putchar('\n');

	for(i=0; i<10; i++)
		printf("%.2d\t", i);
	printf("\n\b");
	printf("===========================================================================");
	putchar('\n');

	i=0;
	
	for(j=0; j<=limit; j++){                          // print acquired data in a matrix format
	    printf("%.2X\t", data[i]);
		if ((j + 1) % 10 == 0)                        // jump to the next line when rows quantity is 10 (alternative to additional for loop) 
        printf("\n");
	    i++;
	}
	
	putchar('\n');
	putchar('\n');
		
	free(data);
    printf("Press Enter to exit...");                 // alternative to system("PAUSE"), the first getchar() consumes leftover newline
    getchar(); getchar();                                    
	return 0;
	
}

