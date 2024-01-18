#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fileTreat(char nameInput[50]);
char newFileName[50];

int main() 
{
	
	FILE *read, *encode;
	int ch, crypt;
	char data[50], originalFileName[50], fileName[50];

	// Create the original file
	printf("File to be encrypted (with extension): ");
	gets(fileName);
	
	strcpy(originalFileName, fileName);
	
	read = fopen(fileName, "w");		
	if(read == NULL)
	{
		printf("\nFile not created.\n");
		exit(1);
	}
	
	printf("\nType the data to be encrypted: ");
	gets(data);
	fputs(data, read);
	fclose(read);
	
	fileTreat(fileName);
	
	encode = fopen(newFileName, "w");
	if(encode == NULL)
	{
		printf("\nError creating the encrypted file.\n");
		exit(2);
	}
	
	read = fopen(originalFileName, "r");
	printf("The encrypted data is: ");
	while((ch=fgetc(read)) != EOF)
	{
		crypt = ch+3;
		printf("%c", crypt);
		fputc(crypt, encode);
	}
	putchar('\n');
	
	
	fclose(read);
	fclose(encode); 
	
	printf("\nThe file was successfuly processed.\n\n");
	
	system("PAUSE");
	return 0;
	
}

char fileTreat(char nameInput[50])
{
	// Find the last '.' character in fileName (file extention)
	size_t len = strlen(nameInput);
	int i, dotIndex = -1;
	for (i = len -1; i >= 0; i--)
	{
		if(nameInput[i] == '.')
			{
				dotIndex = i;
				break;	
			}
	}
	
	// copy the file extension to a new string
	char fileExtension[6] = "";
	if(dotIndex != -1 && dotIndex + 1 < len)
		strcpy(fileExtension, nameInput + dotIndex +1);
	
	// delete the characters until the position of '.'
	if(dotIndex != -1)
		nameInput[dotIndex] = '\0';
	
	// generate the new filename with encrypted information
	
	strcpy(newFileName, nameInput);
	strcat(newFileName, "_encrypted");
	
	// add the original file extension to the new file
	strcat(newFileName, ".");
	strcat(newFileName, fileExtension);
	
	return newFileName[50];
}
	
	
	

