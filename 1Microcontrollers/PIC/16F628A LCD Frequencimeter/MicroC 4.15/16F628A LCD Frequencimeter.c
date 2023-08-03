/* PIC16F628A CCP acquisition mode - Frequencimeter + LCD
   Clock: 4MHz
   Machine cycle: 1us
*/

// Lcd pinout settings
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

// Global variables
char flag0 = 0x00;                          // flags aux. register
unsigned time1, time2;                      // aux. variables for the acquisition time
unsigned long freq;                         // variable to store the frequency (in Hz)
char *text = "Frequencimeter";              // pointer to the string
char *unit = "Hz";
char txt[12];                               // 12 positions string for the LCD

// Interrupt routine
void interrupt()
{
   if(CCP1IF_bit)                           // the interrupt is triggered every 16 rising edge (according with CCP1CON, see the Main function)
   {
      CCP1IF_bit = 0x00;                    // clear the flag for a new acquisition
      if(!flag0.B0)                         // is Flag0.B0 clear?
      {
         time1 = (CCPR1H << 8) + CCPR1L;    // multiply by 256 and add, making the time1 acquisition
         flag0.B0 = 0x01;                   // set the flag0.B0
      }
      else
      {
      time2 = (CCPR1H << 8) + CCPR1L;       // make the time2 acquisition
      flag0.B0 = 0x00;                      // Clear the flag0.B0
      flag0.B1 = 0x01;                      // Set the flag0.B1 (total acquisition happened)
      }
   }
}

void main()
{
   CMCON       = 0x07;                       // disable the comparators
   T1CON       = 0x01;                       // enable the Timer1 counter
   CCP1CON     = 0x07;                       // 0000 0111 make the acquisition on each 16 rising edges
   CCP1IE_bit  = 0x01;                       // enable the CCP interruption
   GIE_bit     = 0x01;                       // enable the global interruption
   PEIE_bit    = 0x01;                       // enable the peripheral interruption
   TRISA       = 0xFF;                       // whole PORTA as input
   TRISB       = 0x0C;                       // 0000 1100  RB2 and RB3 (CCP module) as digital input
   PORTA       = 0xFF;
   PORTB       = 0x00;

   Lcd_Init();
   Lcd_Cmd(_LCD_CURSOR_OFF);
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Out(1,2, text);                       // write "Frequencimeter" at LCD
   Lcd_Out(2,14, unit);                      // write "Hz" at LCD

   while(1)
   {
      time2 = abs(time2 - time1);            // abs is the same as "Module" in Math. It always will return a positive sign to calculate the 16 periods
      time2 = (time2) >> 4;                  // divide  by 16 (2^4) to get 1 period value
      freq = 1/ (time2 * 1E-6);              // convert time2 from us to s and calculate the frequency
      LongToStr(freq, txt);                  // Convert integer to string
      Lcd_Out(2,1, txt);                     // write the acquisition value at line 2, column 1
      flag0.B1 = 0x00;                       // clear the flag
      delay_ms(500);                         // refresh to check the frequency on each 500ms
   }
}