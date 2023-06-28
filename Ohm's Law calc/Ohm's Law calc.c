#include <stdio.h>
#include<stdlib.h>

main()
{
    float E,
             R;
     int opcao;
             
    printf("Ohm's Law calculator'\n");
    printf("\nOptions:\n");
    printf("1 = Current (A)\n");
    printf("2 = Power (W)\n");
    printf("3 = Voltage (V) for current = 100mA\n "); 
    printf("\nType an option: ");
    scanf ("%d", &opcao);
    
    if(opcao == 1 || opcao == 2)
       {
       printf("\nType the voltage (V): ");
       scanf("%f", &E);
       }
    printf("\nType the resistor (Ohms): ");
    scanf("%f", &R);
    
    if(opcao == 1)
       printf("\nThe current is = %.2f A\n", E/ R);
    
    else if(opcao == 2)
                printf("\nThe Power is = %.2f W\n", (E *E)/R);
     else if(opcao == 3)
                printf("\nTo get 100mA with %.1f Ohms is needed %.2f V\n", R, R * 0.1);
    
    putchar('\n');
    
    system("PAUSE");
    return 0;
}
