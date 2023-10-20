#include <stdio.h>
#include <stdlib.h>

/* This program runs at Windows console */
/* Just write the file name and the voltage/ current to calculate the resistor */
/* Please use the following sintaxe:  file_name voltage1 current1 voltage2 current2 voltageN currentN */

int main(int argc, char *argv[]) 
{
	float V, I, R;
	int i;
	
	
	
	for(i=1; i<(argc-1); i++)
	{
		V= atof(argv[i]);
		I= atof(argv[i+1]);
		
		putchar('\n');
	    printf(" Parameters entered:\n");
		printf(" Voltage = %2.2f V\n", V);
		printf(" Current = %2.2f A\n", I);
			
		R= V/I;
		
		printf(" Calculated resistor: %2.2f Ohms |\n", R);
		i++;
	}
	
	putchar('\n');
	system("PAUSE");
	return 0;
}
