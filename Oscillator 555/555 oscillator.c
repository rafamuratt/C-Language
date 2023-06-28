/* ==============================================================================================
	Calculadora 555 astável
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
void calc555(float Ra, float Rb, float C);

/* ============================================================================================== */
/* Função Principal */


main()
{
	float Ra, Rb, C;
	
	puts("#########  555 calculator (astable) #########");
	printf("\nEnter Ra (Ohms): ");
	scanf("%f", &Ra);
	printf("Enter Rb (Ohms): ");
	scanf("%f", &Rb);
	printf("Enter C (F): ");
	scanf("%f", &C);
	
	calc555(Ra, Rb, C);
	
	
	system("PAUSE");
	return 0;
}/* end main */

/* ============================================================================================== */
/* Final do programa*/

void calc555(float Ra, float Rb, float C)
{
	float Freq;
	
	Freq = 1.44/((Ra + 2*Rb) * C);
	
	printf("\nThe oscillator's frequency is = %.4f Hz\n\n", Freq);
}
