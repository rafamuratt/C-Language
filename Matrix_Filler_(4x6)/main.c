/* ==============================================================================================
	Matrix chart
	versão: 1.0
	Autor: Eng Aroldo Rafael Murat
	Data: Janeiro de 2023
   ============================================================================================== */
   
/* ============================================================================================== */
/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>


/* ============================================================================================== */
/* Macros */


/* ============================================================================================== */
/* Protótipo das Funções */


/* ============================================================================================== */
/* Variáveis Globais */


/* ============================================================================================== */
/* Função Principal */


main()
{
	int graph[4][6] = {0};
	int i, j, linha, coluna, numero;
	char control = 'y';
	
	while(control == 'y' || control == 'Y')
	{
		system("CLS");
		
		puts("====== Matrix 4x6 filler v1.0 ======");
		
		printf("\nPlease type:\n");
		printf("The line number: ");
		scanf("%d", &linha);
		printf("The column number: ");
		scanf("%d", &coluna);
		printf("Some number (0-999): ");
		scanf("%d", &numero);
		
		if((numero>0 && numero <=999) && (linha>0 && linha <=4) && (coluna>0 && coluna <=6))
			graph[linha-1][coluna-1] = 	numero;
		
		putchar('\n');
				
		for(i=0; i<9; i++)
		{
			for(j=0; j<6; j++)
			{
				if(i%2)                               // se houver resto na divisão por 2, é um número impar
					printf("| %3d ", graph[i/2][j]);  // [i/2] limpa lixo de memoria ao colocar zero na matrix
				
				else
					printf("------");	              // se nao houver resto na divisao por 2, é um número par    
			}
			
			if(i%2) 
				printf("|");
			
			else 
				printf("-");
				
					
			putchar('\n');
		}

		printf("\nDo you want to continue? (Y/N): ");
		scanf(" %c", &control);
	}
	
	return 0;
}/* end main */


/* ============================================================================================== */
/* Funções Auxiliares */


/* ============================================================================================== */
/* Final do programa*/
