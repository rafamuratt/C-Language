/* ============================================================================

    Battle Ship 2.0
    Jan 2023

============================================================================ */


/* ========================================================================= */
/* --- Libraries --- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>     /* required to use random numbers */              
#include <unistd.h>   /* required to use the sleep function */            
#include <Windows.h>  /* required to play *.wav sounds */
#include <Mmsystem.h>

/* ========================================================================= */
/* --- Macros --- */
       

#define gameSelect(input)   PlaySound(TEXT("intro.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); \
                            printf("\n\n   ------------------------------------------------------------\n"); \
							printf("   |     ######### BATTLE SHIP 2.0 by Rafamuratt #########    |\n"); \
                            printf("   |                                                          |\n"); \
							printf("   |                   Murat-Tech Channel                     |\n"); \
                            printf("   |     www.youtube.com/channel/UC1H5V-FIN7DCLTPmZ0Cm4zw     |\n"); \
                            printf("   ------------------------------------------------------------\n\n"); \
					   		printf("                   Please select the game mode:\n"); \
                       		printf("           | < E > easy | < M > medium | < H > hard |\n"); \
                       		printf("\n           >>> "); \
                       		scanf("%c", &input); \
                       		PlaySound(0,0,0)
                       		

       
                    
/* ========================================================================= */
/* --- Funtions prototypes --- */
                  
void battleChart(char b[][5]);                   /* draw the batle field */
void new_seed();                                 /* random numbers */
unsigned map_col(char col);                      /* convert column charcters in numbers */


char input, restart;
char start = 1;
int win = 0;
int fails = 0;

/* ========================================================================= */
int main()
{
  char 
       map,
       opt  = 'n',                              /* option to start new game */
       sort =  1,                               /* flag for new randomic numbers */
	   col  =  0,                               /* characters for the columns */
       rowChk,                                  /* to check the entry from user */
       colChk,
       quit = 'r';
       
  char boats[5][5] = {0};                        /* stores the enemies positions */
  
  unsigned num,                                  /* stores the random numbers */
           row     = 0,                          /* number of lines */
           success = 0,                          
		   enemies = 0,
		   shotEnemies;                          
  
  register int i,j,k,N;  
  
  if(start == 1)
  {
  	gameSelect(input);
  }

  
  switch(input)
  {
  	case 'E':
  	case 'e':
  	map = 'e';
  	N = 3;
  	break;
  	
  	case 'M':
  	case 'm':
  	map = 'm';
  	N = 4;
  	break;
  	
  	case 'H':
  	case 'h':
  	map = 'h';
  	N = 5;
  	break;
  	
  	default :
  	system("cls");
  	main();
  	
  }
  
                           
   
  do                                            
  { 
    if(sort)                                     
    {                                            
      system("cls"); 
	  enemies = 0;                            
      new_seed();             
  
      for(i=0;i<N;i++)                           /* 8 lines  */
      {
        for(j=0;j<N;j++)                        /* 10 columns */
        {
          num = rand()%100+1;                    /* random numbers from 1 to 100 */
          
          if(num%2) 
		  {
		  	boats[i][j] = '\xCA';                /* when odd number, "draw" an enemy */
		  	enemies++;
		  }
          
          
          else 
		  {
		  	boats[i][j] = 0x20;               /* when even number, "draw" a blank space */  
		   	if(map == 'm') 
			  {
			  	for (k = 0; k < 5; k++) 
				{
					boats[k][4] = 0x20;
					boats[4][k] = 0x20;
				}
			  }
			if(map == 'e') 
			  {
			  	for (k = 0; k < 5; k++) 
				{
					boats[k][3] = 0x20;
					boats[k][4] = 0x20;
					boats[3][k] = 0x20;
					boats[4][k] = 0x20;
				}
			  }
		  }
      
        } /* end for anin. */  
      
      } /* end for */
  
      if(((input == 'm')||(input == 'M')) && (start == 1)) win = 4;
      if(((input == 'h')||(input == 'H')) && (start == 1)) win = 7;
	  battleChart(boats);     
	  if(win == 4) PlaySound(TEXT("goal.wav"), NULL, SND_SYNC);
	  if(win == 7) PlaySound(TEXT("goal.wav"), NULL, SND_SYNC);
	      
      shotEnemies = enemies;
    } /* end if sort */
    
    else                                         
    {
      printf("  Invalid option, please try again.\n\n");                
      sort = 1;                                  /* flag to enable new sort */
      sleep(1);
	  system("cls"); 
	  battleChart(boats);

    }
         
    if (start == 1)
	{
		printf("  Sort a battle field [S].\n");
		printf("  New game [N].\n  >>> ");
		scanf(" %c", &opt);
	}  
	
	else opt = 'n';                                    
       
    if(opt!='s' && opt!='S') sort=0;             /* when not s, clear the flag */   
  
  }while(opt!='n' && opt!='N');                  
  system("cls");                                 
  battleChart(boats);                          
  
  while((quit != 'q')&&(quit != 'Q'))                                       
  {
    system("cls");                                 
  	battleChart(boats);
    	                    
  	printf("  | Successful shots: %2d | Failed shots: %2d |\n\n",success, fails);  
  	printf("  Total enemies     = %2d\n", enemies);
  	printf("  Remaining enemies = %2d\n", shotEnemies);	
  	
  	
    
	printf("\n  Type the coordenates to shot: "); 
    scanf(" %c%c", &rowChk, &colChk);       
	PlaySound(TEXT("shot.wav"), NULL, SND_SYNC);  
    
    	
	if(((rowChk >= 33 && rowChk <= 47) &&(colChk >= 33 && colChk <= 47)) ||  /* if the user type in sequence two characters are between ! and / (ASCII table) or */
	   ((rowChk >= 48 && rowChk <= 57)&&(colChk >= 48 && colChk <= 57))  ||  /* if the user type in sequence two numbers between 0 and 9 (ASCII table) or   */
	   ((rowChk >= 58 && rowChk <= 126)&&(colChk >= 58 && colChk <= 126)))   /* if the user type in sequence two characters are between : and ~ (ASCII table) */
	{
		printf("\n  Invalid entry, please try again!\n\n");  
		sleep(1);     
		system("cls");
	}
	
	else
	{
		if((rowChk >= 49 && rowChk <= 53)||(                                  /* if row is between 1 and 5 or */
		   (colChk >= 65 && colChk <= 69)&&(colChk >= 97 && colChk <= 101)))  /* if the column is between A and E or a and e, the type order and fix if needed */
		{
	        row = rowChk - 48;                          /* convert char to int and update row */
	        col = colChk;                               /* update col */
	    }
	    else
		{
	        row = colChk - 48;                          /* convert char to int and update row */
	        col = rowChk;                               /* update col */

	    }                              
	    
	    if(boats[row-1][map_col(col)] == '\xCA')        /* when the coordinate is the same of some target... */
	    {
	    	boats[row-1][map_col(col)] = '*';          /* update the coordinate with '*' */
	      	success++;      
		  	shotEnemies--;   
		  	if(shotEnemies == 0) 
		  	{
		  		system("cls");                                 
                battleChart(boats); 
                win++;
                PlaySound(TEXT("explosion.wav"), NULL, SND_SYNC);
                printf("\n  <<<   THIS LEVEL IS CLEARED   >>");   
				start = 0;
				sleep(3);
								
				if(win <= 3) 
				{
					input = 'e';
					main();
				}
				else if((win >= 4) && (win <= 6)) 
				{
					 
					input = 'm';
					main();
				}
				else if ((win >= 7) && (win <= 9))
				{
					
					input = 'h';
					main();
				}
				
				else if(win == 10)
				{
					printf("\n\n  CONGRATULATIONS, YOU DESTROYED ALL ENEMIES!!!\n\n");   
				    printf("\n  Do you want to play again? [Y] or [N]\n  >>> ");
				    scanf(" %c", &restart);
				    switch (restart)
				    {
				    	case 'y' :
				    	case 'Y' :
				    	start = 1;
				    	win = 0;
				    	main();
				    	break;
				    	
				    	case 'n' :
				    	case 'N' :
				    	exit(0);
				    	break;
				    	
				    	default :
				    	printf("\n  The application will be closed, thanks for being an hero!!!\n\n");
				    	sleep(5);
				    	exit(0);
					}
				}

		  	}  /* end if shotEnemies == 0 */                   
	      	system("cls");                                 
  			battleChart(boats);
    	                    
  			printf("  | Successful shots: %3d | Failed shots: %3d |\n\n",success, fails);  
  			printf("  Number of total enemies = %2d\n", enemies);
  			printf("  Remaining enemies = %2d\n", shotEnemies);	
			PlaySound(TEXT("explosion.wav"), NULL, SND_SYNC);
	      	 
	      
	    } /* end if boats */
	    
	    else                                         
	    {
	      	fails++;                                   
	      	PlaySound(TEXT("fail.wav"), NULL, SND_SYNC);                                                        
	      
	      	if(fails>5)                                /* if more than 5 errors, game over */
	      	{
	        	printf("\n\n  <<<<<   GAME OVER!!! >>>>>\n\n");                               
	          	PlaySound(TEXT("gameOver.wav"), NULL, SND_SYNC);                        
	        	system("PAUSE");                        
				exit(0);                                 /* immdiate stop of the application */
	                  
	      	} /* end if fails */
	    
	    } /* end else */
	    
	}
		
  	//printf("\n  To quit, press <Q> within 3s: ");
    //scanf(" %c", &quit);
    //printf("\r                                                    \r");
		   
  } /* end while */
  
  sleep(5);	                             
  return 0;                                      
  
} /* end main */


/* ========================================================================= */
void battleChart(char b[][5])
{
  putchar('\n');   
  printf("\n   Battle Ship - Level %2d \n\n", win);
  printf(" [Y]\n");
  printf("     ---------------------\n");
  printf("  5  | %c | %c | %c | %c | %c |\n", b[4][0], b[4][1], b[4][2], b[4][3], b[4][4]);
  printf("     ---------------------\n");
  printf("  4  | %c | %c | %c | %c | %c |\n", b[3][0], b[3][1], b[3][2], b[3][3], b[3][4]);
  printf("     ---------------------\n");
  printf("  3  | %c | %c | %c | %c | %c |\n", b[2][0], b[2][1], b[2][2], b[2][3], b[2][4]);
  printf("     ---------------------\n");
  printf("  2  | %c | %c | %c | %c | %c |\n", b[1][0], b[1][1], b[1][2], b[1][3], b[1][4]);
  printf("     ---------------------\n");
  printf("  1  | %c | %c | %c | %c | %c |\n", b[0][0], b[0][1], b[0][2], b[0][3], b[0][4]);
  printf("     ---------------------\n");
  printf("       A   B   C   D   E   [X]\n");
  putchar('\n');   
       
} /* end naval */  

/* ========================================================================= */
void new_seed() 
{ 
 	time_t capture;                  
	time(&capture); 
	srand((unsigned)capture); 
}


/* ========================================================================= */
unsigned map_col(char col)
{
  switch(col)
  {
    case 'a':
    case 'A': return 0; break;  
    case 'b':
    case 'B': return 1; break;     
    case 'c':
    case 'C': return 2; break; 
    case 'd':
    case 'D': return 3; break; 
    case 'e':
    case 'E': return 4; break; 
             
  } /* end switch */    
     
} /* end map_col*/



