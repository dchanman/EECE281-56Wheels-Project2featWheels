#include "General.h"
#include "LCD.h"
//#include "LCD.c"



unsigned char _c51_external_startup(void)
{
	General_Init();		
	printf("hi\n");	
	LCD_Init();	
	printf("ho\n");
    
    return 0;
}

void main(){
	int k = 0;
	int count = 0;
	unsigned char buffer[56];
	unsigned char *row;
	
	while(1){
		LCD_Clear();
		row = &buffer[LCD_ROW1];
		sprintf(row , "%d                                       ", count);
		row = &buffer[LCD_ROW2];
		sprintf(row, "0123456789ABCDEF");
		
		LCD_WriteString(buffer);
		//LCD_WriteString("12345678901234567890ABCDEFGHIJKLMNOPqrstuvwxyz1234");
		for(k = 0; k < 1000; k++){
			LCD_LongDelay();
			
		}
		count++;
	}
}