
_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;16F628A LCD Frequencimeter.c,31 :: 		void interrupt()
;16F628A LCD Frequencimeter.c,33 :: 		if(CCP1IF_bit)                           // the interrupt is triggered every 16 rising edge (according with CCP1CON, see the Main function)
	BTFSS      CCP1IF_bit+0, 2
	GOTO       L_interrupt0
;16F628A LCD Frequencimeter.c,35 :: 		CCP1IF_bit = 0x00;                    // clear the flag for a new acquisition
	BCF        CCP1IF_bit+0, 2
;16F628A LCD Frequencimeter.c,36 :: 		if(!flag0.B0)                         // is Flag0.B0 clear?
	BTFSC      _flag0+0, 0
	GOTO       L_interrupt1
;16F628A LCD Frequencimeter.c,38 :: 		time1 = (CCPR1H << 8) + CCPR1L;    // multiply by 256 and add, making the time1 acquisition
	MOVF       CCPR1H+0, 0
	MOVWF      _time1+1
	CLRF       _time1+0
	MOVF       CCPR1L+0, 0
	ADDWF      _time1+0, 1
	BTFSC      STATUS+0, 0
	INCF       _time1+1, 1
;16F628A LCD Frequencimeter.c,39 :: 		flag0.B0 = 0x01;                   // set the flag0.B0
	BSF        _flag0+0, 0
;16F628A LCD Frequencimeter.c,40 :: 		}
	GOTO       L_interrupt2
L_interrupt1:
;16F628A LCD Frequencimeter.c,43 :: 		time2 = (CCPR1H << 8) + CCPR1L;       // make the time2 acquisition
	MOVF       CCPR1H+0, 0
	MOVWF      _time2+1
	CLRF       _time2+0
	MOVF       CCPR1L+0, 0
	ADDWF      _time2+0, 1
	BTFSC      STATUS+0, 0
	INCF       _time2+1, 1
;16F628A LCD Frequencimeter.c,44 :: 		flag0.B0 = 0x00;                      // Clear the flag0.B0
	BCF        _flag0+0, 0
;16F628A LCD Frequencimeter.c,45 :: 		flag0.B1 = 0x01;                      // Set the flag0.B1 (total acquisition happened)
	BSF        _flag0+0, 1
;16F628A LCD Frequencimeter.c,46 :: 		}
L_interrupt2:
;16F628A LCD Frequencimeter.c,47 :: 		}
L_interrupt0:
;16F628A LCD Frequencimeter.c,48 :: 		}
L__interrupt6:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;16F628A LCD Frequencimeter.c,50 :: 		void main()
;16F628A LCD Frequencimeter.c,52 :: 		CMCON       = 0x07;                       // disable the comparators
	MOVLW      7
	MOVWF      CMCON+0
;16F628A LCD Frequencimeter.c,53 :: 		T1CON       = 0x01;                       // enable the Timer1 counter
	MOVLW      1
	MOVWF      T1CON+0
;16F628A LCD Frequencimeter.c,54 :: 		CCP1CON     = 0x07;                       // 0000 0111 make the acquisition on each 16 rising edges
	MOVLW      7
	MOVWF      CCP1CON+0
;16F628A LCD Frequencimeter.c,55 :: 		CCP1IE_bit  = 0x01;                       // enable the CCP interruption
	BSF        CCP1IE_bit+0, 2
;16F628A LCD Frequencimeter.c,56 :: 		GIE_bit     = 0x01;                       // enable the global interruption
	BSF        GIE_bit+0, 7
;16F628A LCD Frequencimeter.c,57 :: 		PEIE_bit    = 0x01;                       // enable the peripheral interruption
	BSF        PEIE_bit+0, 6
;16F628A LCD Frequencimeter.c,58 :: 		TRISA       = 0xFF;                       // whole PORTA as input
	MOVLW      255
	MOVWF      TRISA+0
;16F628A LCD Frequencimeter.c,59 :: 		TRISB       = 0x0C;                       // 0000 1100  RB2 and RB3 (CCP module) as digital input
	MOVLW      12
	MOVWF      TRISB+0
;16F628A LCD Frequencimeter.c,60 :: 		PORTA       = 0xFF;
	MOVLW      255
	MOVWF      PORTA+0
;16F628A LCD Frequencimeter.c,61 :: 		PORTB       = 0x00;
	CLRF       PORTB+0
;16F628A LCD Frequencimeter.c,63 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;16F628A LCD Frequencimeter.c,64 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;16F628A LCD Frequencimeter.c,65 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;16F628A LCD Frequencimeter.c,66 :: 		Lcd_Out(1,2, text);                       // write "Frequencimeter" at LCD
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _text+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;16F628A LCD Frequencimeter.c,67 :: 		Lcd_Out(2,14, unit);                      // write "Hz" at LCD
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      14
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _unit+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;16F628A LCD Frequencimeter.c,69 :: 		while(1)
L_main3:
;16F628A LCD Frequencimeter.c,71 :: 		time2 = abs(time2 - time1);            // abs is the same as "Module" in Math. It always will return a positive sign to calculate the 16 periods
	MOVF       _time1+0, 0
	SUBWF      _time2+0, 0
	MOVWF      FARG_abs_a+0
	MOVF       _time1+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	SUBWF      _time2+1, 0
	MOVWF      FARG_abs_a+1
	CALL       _abs+0
	MOVF       R0+0, 0
	MOVWF      _time2+0
	MOVF       R0+1, 0
	MOVWF      _time2+1
;16F628A LCD Frequencimeter.c,72 :: 		time2 = (time2) >> 4;                  // divide  by 16 (2^4) to get 1 period value
	MOVLW      4
	MOVWF      R2+0
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	MOVF       R2+0, 0
L__main7:
	BTFSC      STATUS+0, 2
	GOTO       L__main8
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+1, 7
	ADDLW      255
	GOTO       L__main7
L__main8:
	MOVF       R4+0, 0
	MOVWF      _time2+0
	MOVF       R4+1, 0
	MOVWF      _time2+1
;16F628A LCD Frequencimeter.c,73 :: 		freq = 1/ (time2 * 1E-6);              // convert time2 from us to s and calculate the frequency
	MOVF       R4+0, 0
	MOVWF      R0+0
	MOVF       R4+1, 0
	MOVWF      R0+1
	CALL       _Word2Double+0
	MOVLW      189
	MOVWF      R4+0
	MOVLW      55
	MOVWF      R4+1
	MOVLW      6
	MOVWF      R4+2
	MOVLW      107
	MOVWF      R4+3
	CALL       _Mul_32x32_FP+0
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	MOVF       R0+2, 0
	MOVWF      R4+2
	MOVF       R0+3, 0
	MOVWF      R4+3
	MOVLW      0
	MOVWF      R0+0
	MOVLW      0
	MOVWF      R0+1
	MOVLW      0
	MOVWF      R0+2
	MOVLW      127
	MOVWF      R0+3
	CALL       _Div_32x32_FP+0
	CALL       _Double2Longword+0
	MOVF       R0+0, 0
	MOVWF      _freq+0
	MOVF       R0+1, 0
	MOVWF      _freq+1
	MOVF       R0+2, 0
	MOVWF      _freq+2
	MOVF       R0+3, 0
	MOVWF      _freq+3
;16F628A LCD Frequencimeter.c,74 :: 		LongToStr(freq, txt);                  // Convert integer to string
	MOVF       R0+0, 0
	MOVWF      FARG_LongToStr_input+0
	MOVF       R0+1, 0
	MOVWF      FARG_LongToStr_input+1
	MOVF       R0+2, 0
	MOVWF      FARG_LongToStr_input+2
	MOVF       R0+3, 0
	MOVWF      FARG_LongToStr_input+3
	MOVLW      _txt+0
	MOVWF      FARG_LongToStr_output+0
	CALL       _LongToStr+0
;16F628A LCD Frequencimeter.c,75 :: 		Lcd_Out(2,1, txt);                     // write the acquisition value at line 2, column 1
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _txt+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;16F628A LCD Frequencimeter.c,76 :: 		flag0.B1 = 0x00;                       // clear the flag
	BCF        _flag0+0, 1
;16F628A LCD Frequencimeter.c,77 :: 		delay_ms(500);                         // refresh to check the frequency on each 500ms
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main5:
	DECFSZ     R13+0, 1
	GOTO       L_main5
	DECFSZ     R12+0, 1
	GOTO       L_main5
	DECFSZ     R11+0, 1
	GOTO       L_main5
	NOP
	NOP
;16F628A LCD Frequencimeter.c,78 :: 		}
	GOTO       L_main3
;16F628A LCD Frequencimeter.c,79 :: 		}
	GOTO       $+0
; end of _main
