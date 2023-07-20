

/* ============================================================================
	Lesson of my C language studies: Pointer Arithmetics
	It's a basic memory stack simulator that uses a pointer to update an array.
	Author: B.Eng Rafamuratt
    Date:   19/07/23
      
/* ========================================================================= */
/* --- Libraries --- */

#include <stdio.h>
#include <stdlib.h>


/* ========================================================================= */
/* --- Global variables --- */

int stkLevel,             // stack level
    usrSel,                // menu choice
    stk[]={},              // stack array
	*ptrStk,               // stack pointer
	usrEntry,              // data entry to the array
	countDw;               // control variable, from stkLevel to zero
	
char usrOpt;               // user opt to keep or delete the data


/* ========================================================================= */
/* --- Functions Prototypes --- */

void addStk();             // function to add data to the stack
void rmvStk();             // function to clear the stack
void showStk();            // function to display the stack data


/* ========================================================================= */
/* --- Main Function --- */
main()
{
	printf("\n <<< Hex stack filler v 1.0 by Rafamuratt >>>\n"); 
	printf("\n Type the stack level: "); 
    scanf("%d", &stkLevel);   
	stk[stkLevel];
	countDw = stkLevel;  
	
	while(1)
	{
		register i;	
		system("cls");
		ptrStk = stk;
				
		printf("\n <<< The stack size is set to %d levels. >>>\n", stkLevel);
		printf("\n 1- Add data.\n");
		printf(" 2- Clear the stack.\n");
		printf(" 3- Show the stack.\n");
		printf(" 4- Exit.\n\n");
		printf(" Type an option: ");
		scanf("%d", &usrSel);
			
		if(usrSel >= 1 && usrSel <= 4)
		{
			switch(usrSel)
			{
				case 1: 
					addStk();
				break;
				
				case 2:
					rmvStk();
				break;
				
				case 3:
					showStk();
				break;
				
				case 4:
					exit(0);
				break;
			}	
		
			for(i=0; i<21E8;i++);                         // short delay only
	
		} /* end if usrSel */
		
		else
			{
				printf(" Invalid entry.");
				for(i=0; i<21E8;i++);                     // short delay only
			}
		
	} /* end while */
	
} /* end main */
    
    
/* ========================================================================= */
/* --- Additional Functions --- */

/* --- addStk()  -->>> add data to the stack --- */

void addStk()
{
	register i;
	
	for(i=0; i<stkLevel; i++)
	{
		printf("\n Level %d. Type the hex number (max 2 bytes): ", i+1);
		scanf("%X", &usrEntry);
		
		if((usrEntry >= 0x00) && (usrEntry <= 0xFF))
		{
			printf(" Keep the entry 0x%X? (Y)/(N): ", usrEntry);		
			scanf(" %c", &usrOpt);
		
			if(usrOpt == 'N' || usrOpt == 'n')
				i--;
			
			else
			{
				*ptrStk = usrEntry;                                    // pointer to update the array upwards with the new data
				ptrStk++;
			}
		} /* end if usrEntry */
		
		else
		{
			printf(" <<<Invalid data or out of range. >>>\n");
			i--;
		}  
		
	} /* end for */
	
	countDw = stkLevel;

} /* end addStk */
	

/* ========================================================================= */
/* --- rmvStk()  -->>> clear the stack --- */

void rmvStk()
{
	register i;
		
	if(countDw > 0)
	{
		printf("\n Do you really want to clear the stack? (Y)/(N): ", usrEntry);
		scanf(" %c", &usrOpt);
		
		if(usrOpt == 'Y' || usrOpt == 'y')
		{
			for(i=stkLevel;i>0;i--)
			{
				*(ptrStk + (countDw-1)) = 0;                              // pointer to update the array downwards with 0
				countDw--;
			}
		
		printf("\n <<< All data has been erased. >>>");
		for(i=0; i<21E8;i++);                                             // short delay to present the msg only
		
		} /* end if usrOpt */
		
		else
			{}
		
	} /* end if countDw */
	
	else
		printf("\n <<< The stack is empty. >>>");

} /* end rmvStk */


/* ========================================================================= */
/* --- showStk()  -->>> display the stack data--- */

showStk()
{
	register i;
	putchar('\n');
	
	for(i=0; i<stkLevel; i++)
		printf(" 0x%X\t", stk[i]);

	 putchar('\n');
	 
} /* end showStk */
