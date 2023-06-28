/* ==============================================================================================
	Calculadora Filtro RC Passa Baixas & Tau
	versão: 1.0
	Autor: Eng Aroldo Rafael Murat
	Data: Dezembro de 2022
   ============================================================================================== */
   
/* ============================================================================================== */
/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>

/* ============================================================================================== */
/* Protótipo das Funções */
void calculator(char Opt, float R, float C);

/* ============================================================================================== */
/* Função Principal */


main()
{
	char Opt;
	float R, C;
	
	putchar('\n');
	puts("###### A --> RC Low Pass Filter calculator ######");
	puts("###### B --> RC Time constant calculator   ######");
	
	printf("\nPick a choice (A or B): ");
	scanf("%c", &Opt);
	
	if(Opt == 'A' || Opt == 'a' || Opt == 'B' || Opt =='b')
	{
		printf("\nEnter the value of resistor (Ohms): ");
	    scanf("%f", &R);
	
	    printf("Enter the value of capacitor (Fahrad): ");
	    scanf("%f", &C);
	
	    calculator(Opt, R, C);
	}
	
	else
		puts("\nInvalid option, please restart the app.\n");
	
	system("PAUSE");
	return 0;
}/* end main */

/* ============================================================================================== */
/* Final do programa*/


void calculator(char Opt, float R, float C)
{
	float Pi = 3.1415926535897932384626433832795, freq, tau;
	
	switch(Opt)
	{
		case 'A':
		case 'a':
		 freq = 1 /(2*Pi*R*C);
		 printf("\nLow pass RC Filter.\n");
		 printf("The cut off frequency is %.3f Hz\n\n", freq);
		break;
		 
		case 'B':
		case 'b':
		 tau = R*C;
		 printf("\nRC Time constant.\n");
		 printf("The capacitor will get charged up to 63.2%% its capacity in %.6fs\n", tau);
		 printf("The capacitor will discharge down to 36.8%% its capacity in %.6fs\n\n", tau);
		break;
		
		}
		 
}
