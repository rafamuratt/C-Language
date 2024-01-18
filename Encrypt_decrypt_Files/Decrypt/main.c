#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fileTreat(char nameInput[50]);
char newFileName[50];

int main() 
{
	
	FILE *read, *decode;
	int ch, decrypt;
	char data[50], originalFileName[50], fileName[50];

	// Create the original file
	printf("File to be decrypted (with extension): ");
	gets(fileName);
	
	strcpy(originalFileName, fileName);
	
	read = fopen(fileName, "r");		
	if(read == NULL)
	{
		printf("\nFile not found.\n");
		exit(1);
	}
	fclose(read);
	
	/*printf("\nType the data to be encrypted: ");
	gets(data);
	fputs(data, read);
	fclose(read); */
	
	fileTreat(fileName);
	
	decode = fopen(newFileName, "w");
	if(decode == NULL)
	{
		printf("\nError creating the decrypted file.\n");
		exit(2);
	}
	
	read = fopen(originalFileName, "r");
	printf("The decrypted data is: ");
	while((ch=fgetc(read)) != EOF)
	{
		decrypt = ch-3;
		printf("%c", decrypt);
		fputc(decrypt, decode);
	}
	putchar('\n');
	
	
	fclose(read);
	fclose(decode); 
	
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
	
	// Find the last '_' character in fileName
	int j, traceIndex = -1;
	for (j = len -1; j >= 0; j--)
	{
		if(nameInput[j] == '_')
			{
				traceIndex = j;
				break;	
			}
	}
	
	
	
	// delete the characters until the position of '_'
	if(traceIndex != -1)
		nameInput[traceIndex] = '\0';
	
	// generate the new filename with encrypted information
	
	strcpy(newFileName, nameInput);
	strcat(newFileName, "_decrypted");
	
	// add the original file extension to the new file
	strcat(newFileName, ".");
	strcat(newFileName, fileExtension);
	
	return newFileName[50];
}
	
	
	

