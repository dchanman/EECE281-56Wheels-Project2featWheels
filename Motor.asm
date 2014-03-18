;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1034 (Dec 12 2012) (MSVC)
; This file was generated Tue Mar 18 15:23:18 2014
;--------------------------------------------------------
$name Motor
$optc51 --model-small
	R_DSEG    segment data
	R_CSEG    segment code
	R_BSEG    segment bit
	R_XSEG    segment xdata
	R_PSEG    segment xdata
	R_ISEG    segment idata
	R_OSEG    segment data overlay
	BIT_BANK  segment data overlay
	R_HOME    segment code
	R_GSINIT  segment code
	R_IXSEG   segment xdata
	R_CONST   segment code
	R_XINIT   segment code
	R_DINIT   segment code

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	public _main
	public _updateUI
	public _pwmcounter
	public __c51_external_startup
	public _LCD_Init
	public _LCD_WriteString
	public _direction
	public _pwm1
	public _pwmcount
	public _LCD_Clear
	public _LCD_Put
;--------------------------------------------------------
; Special Function Registers
;--------------------------------------------------------
_ACC            DATA 0xe0
_B              DATA 0xf0
_PSW            DATA 0xd0
_SP             DATA 0x81
_SPX            DATA 0xef
_DPL            DATA 0x82
_DPH            DATA 0x83
_DPLB           DATA 0xd4
_DPHB           DATA 0xd5
_PAGE           DATA 0xf6
_AX             DATA 0xe1
_BX             DATA 0xf7
_DSPR           DATA 0xe2
_FIRD           DATA 0xe3
_MACL           DATA 0xe4
_MACH           DATA 0xe5
_PCON           DATA 0x87
_AUXR           DATA 0x8e
_AUXR1          DATA 0xa2
_DPCF           DATA 0xa1
_CKRL           DATA 0x97
_CKCKON0        DATA 0x8f
_CKCKON1        DATA 0xaf
_CKSEL          DATA 0x85
_CLKREG         DATA 0xae
_OSCCON         DATA 0x85
_IE             DATA 0xa8
_IEN0           DATA 0xa8
_IEN1           DATA 0xb1
_IPH0           DATA 0xb7
_IP             DATA 0xb8
_IPL0           DATA 0xb8
_IPH1           DATA 0xb3
_IPL1           DATA 0xb2
_P0             DATA 0x80
_P1             DATA 0x90
_P2             DATA 0xa0
_P3             DATA 0xb0
_P4             DATA 0xc0
_P0M0           DATA 0xe6
_P0M1           DATA 0xe7
_P1M0           DATA 0xd6
_P1M1           DATA 0xd7
_P2M0           DATA 0xce
_P2M1           DATA 0xcf
_P3M0           DATA 0xc6
_P3M1           DATA 0xc7
_P4M0           DATA 0xbe
_P4M1           DATA 0xbf
_SCON           DATA 0x98
_SBUF           DATA 0x99
_SADEN          DATA 0xb9
_SADDR          DATA 0xa9
_BDRCON         DATA 0x9b
_BRL            DATA 0x9a
_TCON           DATA 0x88
_TMOD           DATA 0x89
_TCONB          DATA 0x91
_TL0            DATA 0x8a
_TH0            DATA 0x8c
_TL1            DATA 0x8b
_TH1            DATA 0x8d
_RL0            DATA 0xf2
_RH0            DATA 0xf4
_RL1            DATA 0xf3
_RH1            DATA 0xf5
_WDTRST         DATA 0xa6
_WDTPRG         DATA 0xa7
_T2CON          DATA 0xc8
_T2MOD          DATA 0xc9
_RCAP2H         DATA 0xcb
_RCAP2L         DATA 0xca
_TH2            DATA 0xcd
_TL2            DATA 0xcc
_SPCON          DATA 0xc3
_SPSTA          DATA 0xc4
_SPDAT          DATA 0xc5
_SSCON          DATA 0x93
_SSCS           DATA 0x94
_SSDAT          DATA 0x95
_SSADR          DATA 0x96
_KBLS           DATA 0x9c
_KBE            DATA 0x9d
_KBF            DATA 0x9e
_KBMOD          DATA 0x9f
_BMSEL          DATA 0x92
_FCON           DATA 0xd2
_EECON          DATA 0xd2
_ACSRA          DATA 0xa3
_ACSRB          DATA 0xab
_AREF           DATA 0xbd
_DADC           DATA 0xa4
_DADI           DATA 0xa5
_DADL           DATA 0xac
_DADH           DATA 0xad
_CCON           DATA 0xd8
_CMOD           DATA 0xd9
_CL             DATA 0xe9
_CH             DATA 0xf9
_CCAPM0         DATA 0xda
_CCAPM1         DATA 0xdb
_CCAPM2         DATA 0xdc
_CCAPM3         DATA 0xdd
_CCAPM4         DATA 0xde
_CCAP0H         DATA 0xfa
_CCAP1H         DATA 0xfb
_CCAP2H         DATA 0xfc
_CCAP3H         DATA 0xfd
_CCAP4H         DATA 0xfe
_CCAP0L         DATA 0xea
_CCAP1L         DATA 0xeb
_CCAP2L         DATA 0xec
_CCAP3L         DATA 0xed
_CCAP4L         DATA 0xee
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
_ACC_0          BIT 0xe0
_ACC_1          BIT 0xe1
_ACC_2          BIT 0xe2
_ACC_3          BIT 0xe3
_ACC_4          BIT 0xe4
_ACC_5          BIT 0xe5
_ACC_6          BIT 0xe6
_ACC_7          BIT 0xe7
_B_0            BIT 0xf0
_B_1            BIT 0xf1
_B_2            BIT 0xf2
_B_3            BIT 0xf3
_B_4            BIT 0xf4
_B_5            BIT 0xf5
_B_6            BIT 0xf6
_B_7            BIT 0xf7
_P              BIT 0xd0
_F1             BIT 0xd1
_OV             BIT 0xd2
_RS0            BIT 0xd3
_RS1            BIT 0xd4
_F0             BIT 0xd5
_AC             BIT 0xd6
_CY             BIT 0xd7
_EX0            BIT 0xa8
_ET0            BIT 0xa9
_EX1            BIT 0xaa
_ET1            BIT 0xab
_ES             BIT 0xac
_ET2            BIT 0xad
_EC             BIT 0xae
_EA             BIT 0xaf
_PX0            BIT 0xb8
_PT0            BIT 0xb9
_PX1            BIT 0xba
_PT1            BIT 0xbb
_PS             BIT 0xbc
_PT2            BIT 0xbd
_IP0D           BIT 0xbf
_PPCL           BIT 0xbe
_PT2L           BIT 0xbd
_PLS            BIT 0xbc
_PT1L           BIT 0xbb
_PX1L           BIT 0xba
_PT0L           BIT 0xb9
_PX0L           BIT 0xb8
_P0_0           BIT 0x80
_P0_1           BIT 0x81
_P0_2           BIT 0x82
_P0_3           BIT 0x83
_P0_4           BIT 0x84
_P0_5           BIT 0x85
_P0_6           BIT 0x86
_P0_7           BIT 0x87
_P1_0           BIT 0x90
_P1_1           BIT 0x91
_P1_2           BIT 0x92
_P1_3           BIT 0x93
_P1_4           BIT 0x94
_P1_5           BIT 0x95
_P1_6           BIT 0x96
_P1_7           BIT 0x97
_P2_0           BIT 0xa0
_P2_1           BIT 0xa1
_P2_2           BIT 0xa2
_P2_3           BIT 0xa3
_P2_4           BIT 0xa4
_P2_5           BIT 0xa5
_P2_6           BIT 0xa6
_P2_7           BIT 0xa7
_P3_0           BIT 0xb0
_P3_1           BIT 0xb1
_P3_2           BIT 0xb2
_P3_3           BIT 0xb3
_P3_4           BIT 0xb4
_P3_5           BIT 0xb5
_P3_6           BIT 0xb6
_P3_7           BIT 0xb7
_RXD            BIT 0xb0
_TXD            BIT 0xb1
_INT0           BIT 0xb2
_INT1           BIT 0xb3
_T0             BIT 0xb4
_T1             BIT 0xb5
_WR             BIT 0xb6
_RD             BIT 0xb7
_P4_0           BIT 0xc0
_P4_1           BIT 0xc1
_P4_2           BIT 0xc2
_P4_3           BIT 0xc3
_P4_4           BIT 0xc4
_P4_5           BIT 0xc5
_P4_6           BIT 0xc6
_P4_7           BIT 0xc7
_RI             BIT 0x98
_TI             BIT 0x99
_RB8            BIT 0x9a
_TB8            BIT 0x9b
_REN            BIT 0x9c
_SM2            BIT 0x9d
_SM1            BIT 0x9e
_SM0            BIT 0x9f
_IT0            BIT 0x88
_IE0            BIT 0x89
_IT1            BIT 0x8a
_IE1            BIT 0x8b
_TR0            BIT 0x8c
_TF0            BIT 0x8d
_TR1            BIT 0x8e
_TF1            BIT 0x8f
_CP_RL2         BIT 0xc8
_C_T2           BIT 0xc9
_TR2            BIT 0xca
_EXEN2          BIT 0xcb
_TCLK           BIT 0xcc
_RCLK           BIT 0xcd
_EXF2           BIT 0xce
_TF2            BIT 0xcf
_CF             BIT 0xdf
_CR             BIT 0xde
_CCF4           BIT 0xdc
_CCF3           BIT 0xdb
_CCF2           BIT 0xda
_CCF1           BIT 0xd9
_CCF0           BIT 0xd8
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	rbank0 segment data overlay
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
_pwmcount:
	ds 1
_pwm1:
	ds 1
_direction:
	ds 2
_updateUI_s_1_58:
	ds 56
_main_input_1_61:
	ds 2
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg R_OSEG
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	rseg R_ISEG
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	DSEG
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	rseg R_BSEG
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	rseg R_PSEG
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	rseg R_XSEG
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	XSEG
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	rseg R_IXSEG
	rseg R_HOME
	rseg R_GSINIT
	rseg R_CSEG
;--------------------------------------------------------
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
	CSEG at 0x000b
	ljmp	_pwmcounter
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	rseg R_HOME
	rseg R_GSINIT
	rseg R_GSINIT
;--------------------------------------------------------
; data variables initialization
;--------------------------------------------------------
	rseg R_DINIT
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_LongDelay'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:36: void LCD_LongDelay(void){
;	-----------------------------------------
;	 function LCD_LongDelay
;	-----------------------------------------
_LCD_LongDelay:
	using	0
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:45: _endasm;
	
  ;For a 22.1184MHz crystal one machine cycle
  ;takes 12/22.1184MHz=0.5425347us
	  mov R1, #7
	  L2_50:
	mov R0, #184
	  L1_50:
	djnz R0, L1_50 ; 2 machine cycles-> 2*0.5425347us*184=200us
	  djnz R1, L2_50 ; 200us*25=0.005s
	  ret
	 
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_ShortDelay'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:52: void LCD_ShortDelay(void){
;	-----------------------------------------
;	 function LCD_ShortDelay
;	-----------------------------------------
_LCD_ShortDelay:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:59: _endasm;
	
  ;For a 22.1184MHz crystal one machine cycle
  ;takes 12/22.1184MHz=0.5425347us
	  mov R0, #46
	  shortL1:
	djnz R0,shortL1 ; 2 machine cycles-> 2*0.5425347us*184=49.9us
	  ret
	 
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_Clear'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:67: void LCD_Clear(){
;	-----------------------------------------
;	 function LCD_Clear
;	-----------------------------------------
_LCD_Clear:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:68: LCD_RS = 0;
	clr	_P4_1
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:69: LCD_E = LCD_ENABLE;
	setb	_P3_2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:70: LCD_ShortDelay();
	lcall	_LCD_ShortDelay
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:71: LCD_D = 1;
	mov	_P1,#0x01
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:72: LCD_ShortDelay();
	lcall	_LCD_ShortDelay
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:73: LCD_E = LCD_DISABLE;
	clr	_P3_2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:74: LCD_LongDelay();
	ljmp	_LCD_LongDelay
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_Put'
;------------------------------------------------------------
;c                         Allocated to registers r2 
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:83: void LCD_Put(unsigned char c){
;	-----------------------------------------
;	 function LCD_Put
;	-----------------------------------------
_LCD_Put:
	mov	r2,dpl
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:84: LCD_E = LCD_ENABLE;
	setb	_P3_2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:85: LCD_ShortDelay();
	push	ar2
	lcall	_LCD_ShortDelay
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:86: LCD_D = c;
	mov	_P1,r2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:87: LCD_ShortDelay();
	lcall	_LCD_ShortDelay
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:88: LCD_E = LCD_DISABLE;
	clr	_P3_2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:89: LCD_ShortDelay();
	ljmp	_LCD_ShortDelay
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_WriteString'
;------------------------------------------------------------
;c                         Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:97: void LCD_WriteString(unsigned char *c){
;	-----------------------------------------
;	 function LCD_WriteString
;	-----------------------------------------
_LCD_WriteString:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:98: LCD_RS = 1;
	setb	_P4_1
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:99: while(*c != '\0'){
L006001?:
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	jz	L006004?
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:100: LCD_Put(*c);
	mov	dpl,r5
	push	ar2
	push	ar3
	push	ar4
	lcall	_LCD_Put
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:101: printf("%c",*c); 
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
	mov	r6,#0x00
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	mov	a,#__str_0
	push	acc
	mov	a,#(__str_0 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:102: c++;
	sjmp	L006001?
L006004?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_Init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:113: void LCD_Init(){
;	-----------------------------------------
;	 function LCD_Init
;	-----------------------------------------
_LCD_Init:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:114: LCD_E = 0;
	clr	_P3_2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:115: LCD_Clear();
	lcall	_LCD_Clear
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:116: LCD_Put(((unsigned char)0b00111000));	//Function set, 8 bit, 2 lines, 5ื7
	mov	dpl,#0x38
	lcall	_LCD_Put
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:117: LCD_Put(((unsigned char)0b00001111));	//Display ON, Cursor On, Cursor Blinking
	mov	dpl,#0x0F
	lcall	_LCD_Put
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:118: LCD_Put(((unsigned char)0b00000011));   //Entry Mode, Increment cursor position, No display shift
	mov	dpl,#0x03
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\/LCD.c:119: return;
	ljmp	_LCD_Put
;------------------------------------------------------------
;Allocation info for local variables in function '_c51_external_startup'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:39: unsigned char _c51_external_startup(void)
;	-----------------------------------------
;	 function _c51_external_startup
;	-----------------------------------------
__c51_external_startup:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:42: P0M0=0;	P0M1=0;
	mov	_P0M0,#0x00
	mov	_P0M1,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:43: P1M0=0;	P1M1=0;
	mov	_P1M0,#0x00
	mov	_P1M1,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:44: P2M0=0;	P2M1=0;
	mov	_P2M0,#0x00
	mov	_P2M1,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:45: P3M0=0;	P3M1=0;
	mov	_P3M0,#0x00
	mov	_P3M1,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:46: AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	mov	_AUXR,#0x11
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:47: P4M0=0;	P4M1=0;
	mov	_P4M0,#0x00
	mov	_P4M1,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:50: PCON|=0x80;
	orl	_PCON,#0x80
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:51: SCON = 0x52;
	mov	_SCON,#0x52
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:52: BDRCON=0;
	mov	_BDRCON,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:53: BRL=BRG_VAL;
	mov	_BRL,#0xFA
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:54: BDRCON=BRR|TBCK|RBCK|SPD;
	mov	_BDRCON,#0x1E
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:57: TR0=0; // Stop timer 0
	clr	_TR0
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:58: TMOD=0x01; // 16-bit timer
	mov	_TMOD,#0x01
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:63: TH0=RH0=TIMER0_RELOAD_VALUE/0x100;
	mov	_RH0,#0xFF
	mov	_TH0,#0xFF
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:64: TL0=RL0=TIMER0_RELOAD_VALUE%0x100;
	mov	_RL0,#0x48
	mov	_TL0,#0x48
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:65: TR0=1; // Start timer 0 (bit 4 in TCON)
	setb	_TR0
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:66: ET0=1; // Enable timer 0 interrupt
	setb	_ET0
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:67: EA=1;  // Enable global interrupts
	setb	_EA
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:69: pwmcount=0;
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:71: direction = 0;
	clr	a
	mov	_pwmcount,a
	mov	_direction,a
	mov	(_direction + 1),a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:72: LCD_Init();
	lcall	_LCD_Init
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:74: return 0;
	mov	dpl,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'pwmcounter'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:79: void pwmcounter (void) interrupt 1
;	-----------------------------------------
;	 function pwmcounter
;	-----------------------------------------
_pwmcounter:
	push	acc
	push	psw
	mov	psw,#0x00
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:81: if(++pwmcount>99){
	inc	_pwmcount
	mov	a,_pwmcount
	add	a,#0xff - 0x63
	jnc	L009002?
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:82: pwmcount=0;
	mov	_pwmcount,#0x00
L009002?:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:84: if(direction){
	mov	a,_direction
	orl	a,(_direction + 1)
	jz	L009004?
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:85: PWM_OUTPUT1=(pwm1>pwmcount)?1:0;
	clr	c
	mov	a,_pwmcount
	subb	a,_pwm1
	mov	_P4_3,c
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:86: PWM_OUTPUT2= 0;
	clr	_P3_7
	sjmp	L009006?
L009004?:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:89: PWM_OUTPUT2=(pwm1>pwmcount)?1:0;
	clr	c
	mov	a,_pwmcount
	subb	a,_pwm1
	mov	_P3_7,c
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:90: PWM_OUTPUT1 = 0;
	clr	_P4_3
L009006?:
	pop	psw
	pop	acc
	reti
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'updateUI'
;------------------------------------------------------------
;input                     Allocated to registers r2 r3 
;k                         Allocated to registers r2 r3 
;s                         Allocated with name '_updateUI_s_1_58'
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:123: void updateUI(int input){
;	-----------------------------------------
;	 function updateUI
;	-----------------------------------------
_updateUI:
	mov	r2,dpl
	mov	r3,dph
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:127: printf( CLEAR_SCREEN );
	push	ar2
	push	ar3
	mov	a,#__str_1
	push	acc
	mov	a,#(__str_1 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:128: printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	clr	a
	push	acc
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:129: printf("ษออออออออออออหออออออออออออป\n");
	mov	a,#__str_3
	push	acc
	mov	a,#(__str_3 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:130: printf("บ Speed:     บ            บ\n");
	mov	a,#__str_4
	push	acc
	mov	a,#(__str_4 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:131: printf("ฬออออออออออออฮออออออออออออน\n");
	mov	a,#__str_5
	push	acc
	mov	a,#(__str_5 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:132: printf("บ Direction: บ            บ\n");
	mov	a,#__str_6
	push	acc
	mov	a,#(__str_6 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:133: printf("ฬออออออออออออฮออออออออออออน\n");
	mov	a,#__str_5
	push	acc
	mov	a,#(__str_5 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:134: printf("บ            บ            บ\n");
	mov	a,#__str_7
	push	acc
	mov	a,#(__str_7 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:135: printf("ศออออออออออออสออออออออออออผ\n");
	mov	a,#__str_8
	push	acc
	mov	a,#(__str_8 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:136: printf( GOTO_YX , 2, 18);
	mov	a,#0x12
	push	acc
	clr	a
	push	acc
	mov	a,#0x02
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:137: printf( FORE_BACK , COLOR_RED, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	mov	a,#0x01
	push	acc
	clr	a
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:138: printf("%d", input);
	push	ar2
	push	ar3
	push	ar2
	push	ar3
	mov	a,#__str_10
	push	acc
	mov	a,#(__str_10 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:139: printf( GOTO_YX , 4, 18);
	mov	a,#0x12
	push	acc
	clr	a
	push	acc
	mov	a,#0x04
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:140: printf( FORE_BACK , COLOR_RED, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	mov	a,#0x01
	push	acc
	clr	a
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:141: printf("%s", (direction ? "CW ":"CCW"));
	mov	a,_direction
	orl	a,(_direction + 1)
	jz	L010007?
	mov	r4,#__str_12
	mov	r5,#(__str_12 >> 8)
	sjmp	L010008?
L010007?:
	mov	r4,#__str_13
	mov	r5,#(__str_13 >> 8)
L010008?:
	mov	r6,#0x80
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	mov	a,#__str_11
	push	acc
	mov	a,#(__str_11 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:144: sprintf(s, "spd: %d%% %s                                     ", input, (direction ? "CW ":"CCW"));
	mov	a,_direction
	orl	a,(_direction + 1)
	jz	L010009?
	mov	r4,#__str_12
	mov	r5,#(__str_12 >> 8)
	sjmp	L010010?
L010009?:
	mov	r4,#__str_13
	mov	r5,#(__str_13 >> 8)
L010010?:
	mov	r6,#0x80
	push	ar4
	push	ar5
	push	ar6
	push	ar2
	push	ar3
	mov	a,#__str_14
	push	acc
	mov	a,#(__str_14 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	mov	a,#_updateUI_s_1_58
	push	acc
	mov	a,#(_updateUI_s_1_58 >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	lcall	_sprintf
	mov	a,sp
	add	a,#0xf5
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:146: s[42] = '|';			//2nd row of display starts at index 40
	mov	(_updateUI_s_1_58 + 0x002a),#0x7C
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:147: for(k = 1; k <= 10; k++){
	mov	r2,#0x01
	mov	r3,#0x00
	mov	r4,#0x0A
	mov	r5,#0x00
L010001?:
	clr	c
	mov	a,#0x0A
	subb	a,r2
	clr	a
	xrl	a,#0x80
	mov	b,r3
	xrl	b,#0x80
	subb	a,b
	jc	L010004?
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:148: s[42+k] = (pwm1 >= 10*k ? '-':' ');	//boolean expression determines if - or _
	mov	ar6,r2
	mov	a,#0x2A
	add	a,r6
	add	a,#_updateUI_s_1_58
	mov	r0,a
	mov	r6,_pwm1
	mov	r7,#0x00
	clr	c
	mov	a,r6
	subb	a,r4
	mov	a,r7
	xrl	a,#0x80
	mov	b,r5
	xrl	b,#0x80
	subb	a,b
	cpl	c
	clr	a
	rlc	a
	mov	r6,a
	jz	L010011?
	mov	r6,#0x2D
	sjmp	L010012?
L010011?:
	mov	r6,#0x20
L010012?:
	mov	@r0,ar6
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:147: for(k = 1; k <= 10; k++){
	mov	a,#0x0A
	add	a,r4
	mov	r4,a
	clr	a
	addc	a,r5
	mov	r5,a
	inc	r2
	cjne	r2,#0x00,L010001?
	inc	r3
	sjmp	L010001?
L010004?:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:150: sprintf(&s[53], "|   \0");
	mov	a,#__str_15
	push	acc
	mov	a,#(__str_15 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	mov	a,#(_updateUI_s_1_58 + 0x0035)
	push	acc
	mov	a,#((_updateUI_s_1_58 + 0x0035) >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	lcall	_sprintf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:151: LCD_WriteString(s);
	mov	dptr,#_updateUI_s_1_58
	mov	b,#0x40
	ljmp	_LCD_WriteString
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;input                     Allocated with name '_main_input_1_61'
;oldinput                  Allocated to registers r2 r3 
;------------------------------------------------------------
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:154: void main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:157: pwm1=50;
	mov	_pwm1,#0x32
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:158: input = 50;
	mov	_main_input_1_61,#0x32
	clr	a
	mov	(_main_input_1_61 + 1),a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:159: LCD_WriteString("Hi");
	mov	dptr,#__str_16
	mov	b,#0x80
	lcall	_LCD_WriteString
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:160: while(1){
L011002?:
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:161: updateUI(input);		
	mov	dpl,_main_input_1_61
	mov	dph,(_main_input_1_61 + 1)
	lcall	_updateUI
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:164: printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	clr	a
	push	acc
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:165: printf( GOTO_YX , 6, 3);
	mov	a,#0x03
	push	acc
	clr	a
	push	acc
	mov	a,#0x06
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:166: printf("New Speed:");
	mov	a,#__str_17
	push	acc
	mov	a,#(__str_17 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:167: printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	mov	a,#0x04
	push	acc
	clr	a
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:168: printf( GOTO_YX , 6, 18);
	mov	a,#0x12
	push	acc
	clr	a
	push	acc
	mov	a,#0x06
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:169: scanf("%d", &input);
	mov	a,#_main_input_1_61
	push	acc
	mov	a,#(_main_input_1_61 >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	mov	a,#__str_10
	push	acc
	mov	a,#(__str_10 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_scanf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:170: pwm1 = ((unsigned char)input);
	mov	_pwm1,_main_input_1_61
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:172: oldinput = input;
	mov	r2,_main_input_1_61
	mov	r3,(_main_input_1_61 + 1)
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:173: updateUI(input);
	mov	dpl,r2
	mov	dph,r3
	push	ar2
	push	ar3
	lcall	_updateUI
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:176: printf( GOTO_YX , 8, 28);
	mov	a,#0x1C
	push	acc
	clr	a
	push	acc
	mov	a,#0x08
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:177: printf( FORE_BACK , COLOR_GREEN, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	mov	a,#0x02
	push	acc
	clr	a
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:178: printf("(0 for CCW, 1 for CW)");
	mov	a,#__str_18
	push	acc
	mov	a,#(__str_18 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:179: printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	clr	a
	push	acc
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:180: printf( GOTO_YX , 6, 3);
	mov	a,#0x03
	push	acc
	clr	a
	push	acc
	mov	a,#0x06
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:181: printf("New Dir:");
	mov	a,#__str_19
	push	acc
	mov	a,#(__str_19 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:182: printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
	mov	a,#0x07
	push	acc
	clr	a
	push	acc
	mov	a,#0x04
	push	acc
	clr	a
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:183: printf( GOTO_YX , 6, 18);
	mov	a,#0x12
	push	acc
	clr	a
	push	acc
	mov	a,#0x06
	push	acc
	clr	a
	push	acc
	mov	a,#__str_9
	push	acc
	mov	a,#(__str_9 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf9
	mov	sp,a
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:184: scanf("%d", &direction);		
	mov	a,#_direction
	push	acc
	mov	a,#(_direction >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	mov	a,#__str_10
	push	acc
	mov	a,#(__str_10 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_scanf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
	pop	ar3
	pop	ar2
;	C:\Users\Derek\Documents\GitHub\EECE281-56Wheels-Project2featWheels\Motor.c:186: input = oldinput;
	mov	_main_input_1_61,r2
	mov	(_main_input_1_61 + 1),r3
	ljmp	L011002?
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST
__str_0:
	db '%c'
	db 0x00
__str_1:
	db 0x1B
	db '[2J'
	db 0x00
__str_2:
	db 0x1B
	db '[0;3%d;4%dm'
	db 0x00
__str_3:
	db 0xC9
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCB
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xBB
	db 0x0A
	db 0x00
__str_4:
	db 0xBA
	db ' Speed:     '
	db 0xBA
	db '            '
	db 0xBA
	db 0x0A
	db 0x00
__str_5:
	db 0xCC
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCE
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xB9
	db 0x0A
	db 0x00
__str_6:
	db 0xBA
	db ' Direction: '
	db 0xBA
	db '            '
	db 0xBA
	db 0x0A
	db 0x00
__str_7:
	db 0xBA
	db '            '
	db 0xBA
	db '            '
	db 0xBA
	db 0x0A
	db 0x00
__str_8:
	db 0xC8
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCA
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xCD
	db 0xBC
	db 0x0A
	db 0x00
__str_9:
	db 0x1B
	db '[%d;%dH'
	db 0x00
__str_10:
	db '%d'
	db 0x00
__str_11:
	db '%s'
	db 0x00
__str_12:
	db 'CW '
	db 0x00
__str_13:
	db 'CCW'
	db 0x00
__str_14:
	db 'spd: %d%% %s                                     '
	db 0x00
__str_15:
	db '|   '
	db 0x00
	db 0x00
__str_16:
	db 'Hi'
	db 0x00
__str_17:
	db 'New Speed:'
	db 0x00
__str_18:
	db '(0 for CCW, 1 for CW)'
	db 0x00
__str_19:
	db 'New Dir:'
	db 0x00

	CSEG

end
