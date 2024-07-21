#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer {
	char name[30];
	char address[40];
	char city[30];
	char phone[15];
	int number;
	int zipCode;	
};

struct customer info;   // struct type = customer, variable = info

int main() {
	
	printf("\nName: ");
	fgets(info.name, sizeof(info.name), stdin);         // fgets is safer than gets as it limits the number of characters read, preventing buffer overflow
	info.name[strcspn(info.name, "\n")] = 0;            // Remove newline character (it tells you the position of newline character in the string & replace with null)
	                                                    // Ex: input = "Rafa", info.name get also new line character "Rafa\n" and after strcspn becomes "Rafa\0"
	printf("Address: ");
	fgets(info.address, sizeof(info.address), stdin);
	info.address[strcspn(info.address, "\n")] = 0;      // Remove newline character 
	
	printf("Number: ");
	scanf("%d", &info.number);
	
	printf("Zip Code: ");
	scanf("%d", &info.zipCode);
	
	
	while ((getchar()) != '\n');                        // Clear input buffer before reading the next line
	
	printf("City: ");
	fgets(info.city, sizeof(info.city), stdin);
	info.city[strcspn(info.city, "\n")] = 0;            // Remove newline character
	
	printf("Phone: ");
	fgets(info.phone, sizeof(info.phone), stdin);
	info.phone[strcspn(info.phone, "\n")] = 0;          // Remove newline character
	
	putchar('\n');
	
	printf("Name: %s\n", info.name);
	printf("Address: %s, %d\n", info.address, info.number);
	printf("Zip Code: %d\n", info.zipCode);
	printf("City: %s\n", info.city);
	printf("Phone: %s\n", info.phone);
	
	putchar('\n');
	
	system("pause");
	return 0;
}
