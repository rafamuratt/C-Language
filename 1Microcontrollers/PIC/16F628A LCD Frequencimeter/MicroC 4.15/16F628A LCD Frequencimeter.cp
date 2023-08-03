#line 1 "C:/1Rafa/005 - Engenharia/1 - Estudos/001 Aulas/1-Autodidata/You Tube/PIC WR Kits/Circuitos úteis/16F628A LCD Frequencimeter/MicroC 4.15/16F628A LCD Frequencimeter.c"
#line 7 "C:/1Rafa/005 - Engenharia/1 - Estudos/001 Aulas/1-Autodidata/You Tube/PIC WR Kits/Circuitos úteis/16F628A LCD Frequencimeter/MicroC 4.15/16F628A LCD Frequencimeter.c"
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;


sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;


char flag0 = 0x00;
unsigned time1, time2;
unsigned long freq;
char *text = "Frequencimeter";
char *unit = "Hz";
char txt[12];


void interrupt()
{
 if(CCP1IF_bit)
 {
 CCP1IF_bit = 0x00;
 if(!flag0.B0)
 {
 time1 = (CCPR1H << 8) + CCPR1L;
 flag0.B0 = 0x01;
 }
 else
 {
 time2 = (CCPR1H << 8) + CCPR1L;
 flag0.B0 = 0x00;
 flag0.B1 = 0x01;
 }
 }
}

void main()
{
 CMCON = 0x07;
 T1CON = 0x01;
 CCP1CON = 0x07;
 CCP1IE_bit = 0x01;
 GIE_bit = 0x01;
 PEIE_bit = 0x01;
 TRISA = 0xFF;
 TRISB = 0x0C;
 PORTA = 0xFF;
 PORTB = 0x00;

 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,2, text);
 Lcd_Out(2,14, unit);

 while(1)
 {
 time2 = abs(time2 - time1);
 time2 = (time2) >> 4;
 freq = 1/ (time2 * 1E-6);
 LongToStr(freq, txt);
 Lcd_Out(2,1, txt);
 flag0.B1 = 0x00;
 delay_ms(500);
 }
}
