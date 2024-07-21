#include <stdio.h>
#include <stdlib.h>

union items {
    unsigned short data;
    unsigned char  two_bytes[2];
} input;

unsigned short record(union items *write);

int main() {
       
    printf("\nConvert int to bin (2 bytes) & record it in external file.\n");
    printf("Enter the integer: ");
    
    if (scanf("%hu", &input.data) != 1) {            // Correctly read the unsigned short integer
        printf("Invalid input.\n");
        return 1;
    }
    
    if (!record(&input)) {                          // the function record is called here (with he address of input as parameter: &input)
        printf("File error.\n");
        return 1;
    }
    
    
    return 0;
}

unsigned short record(union items *write) {        // take the address of information available in input.data by means of *write... 
    FILE *file;
    if ((file = fopen("result.dat", "wb")) == NULL) {
    	printf("File error.\n");
        return 0;
    }
        
    fputc(write -> two_bytes[0], file);             // ...and distribute it in two bytes char vector
    fputc(write -> two_bytes[1], file);
    fclose(file);
    
    // Print binary content to the console
    printf("\nThis is the binary content written to file: ");
    printf("%02X %02X\n", write->two_bytes[1], write->two_bytes[0]);
    
    printf("\nSuccess to write the file result.dat.\n");

    putchar('\n');
    
    return 1;
}

