/* ==============================================================================================
	Data Jammer
	Version: 1.0
	Author: Eng Aroldo Rafael Murat
	Date: Dezembro de 2022
   ============================================================================================== */
   
/* ============================================================================================== */
/* Libraries */
#include <stdio.h>
#include <stdlib.h>

/* ============================================================================================== */
/* Constants */

/* ============================================================================================== */
/* Functions Prototypes */
void encrypter(int byte[], int N);
void decrypter(int byte[], int N);

/* ============================================================================================== */
/* Global Variables */
int check[] = {}, crypt[] = {}, i;

/* ============================================================================================== */
/* Main Function */
main()
{
	char mode;
	int num;
	printf("\n########   HEX DATA JAMMER v1.0   ########");
	printf("\n\nTo encrypt(E) or to decrypt(D) the data? ");
	scanf(" %c", &mode);
	printf("How many bytes? ");
	scanf("%d", &num);
	int byte[num];
	
	
	putchar('\n');
	
	for(i=0; i<num; i++)
   	{
	    printf("Enter the byte %d: ", i);
       	scanf("%X", &byte[ i]);
   	}
   	putchar('\n');
	
	switch(mode)
	{
	    case 'E' :
	    case 'e' :
	        encrypter(byte, num);

        break;
                    
        case 'D' :
        case 'd' :
            decrypter(byte, num);
	    	
        break;   
        
	}/* end switch */
	
        printf("\n\n");
	 
	system("PAUSE");
	return 0;
}/* end main */



/* ============================================================================================== */
/* Auxiliary Functions */
void encrypter(int byte[], int N)
{
    printf("Data to encrypt:\n");
           	
	for(i=0; i<N; i++)
	    printf("0x%X\t", byte[i]);
	        
    putchar('\n');
                 
    printf("\nData encrypted:\n");
              	 
    for(i=0; i<N; i++)
        {
            check[i] = byte[i]% 2;
    
            if(check[i])
                {
                    crypt[i] = byte[i] - 3;
                    printf("0x%X\t", crypt[i]);
                }
                  
            else
   	           {
                    crypt[i] = byte[i] + 5;
                    printf("0x%X\t", crypt[i]);
  	           }
  	           
        }/* end for */	
        
}/* end encrypter */


void decrypter(int byte[], int N)
{
	printf("Data to decrypt:\n");
	    	
	for(i=0; i<N; i++)
        printf("0x%X\t", byte[i]);
                  
    putchar('\n');
          
    printf("\nData decrypted:\n");

    for(i=0; i<N; i++)
         {
            check[i] = (byte[i] + 5)% 2;

            if(check[i])
               {
                  crypt[i] = byte[i] + 3;
                  printf("0x%X\t", crypt[i]);
               }
          
           else
            {
                crypt[i] = byte[i] - 5;
                printf("0x%X\t", crypt[i]);
            }
            
         }/* end for */
         
}/* end decrypter */


/* ============================================================================================== */
/* Final do programa*/
