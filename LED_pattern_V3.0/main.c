/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 5 , April 2023                                       */
/* Version : V01                                                  */
/* Hint    : Application layer                                    */
/******************************************************************/

#include <avr/interrupt.h>  /** FOR INTERRUPTS **/

#include "SERVICE/common_macros.h"
#include "SERVICE/standard_types.h"

#include "MCAL/dio/DIO_interface.h"
#include "HAL/led/LED_interface.h"
#include "MCAL/timer0/TMR0_interface.h"
#include "MCAL/extint/INT_interface.h"


#include "HAL/led/LED_config.h"


uint8_t blinking_mode = 0 ;  /** VARIABLE TO DECIDE WHICH BLINKING MODE IS APPLIED **/

uint8_t LED_mode  =  0 ;     /** VARIABLE TO DECIDE THE MODE OF LEDs **/



int main(void)
{
	/** INITIALIZE THE LEDS **/
	LED_init(LED1_PORT , LED1_PIN);
	LED_init(LED2_PORT , LED2_PIN);
	LED_init(LED3_PORT , LED3_PIN);
	LED_init(LED4_PORT , LED4_PIN);
	
	/** LEDs ARE OFF AS INITIAL STATE **/
	LED_off(LED1_PORT , LED1_PIN);
	LED_off(LED2_PORT , LED2_PIN);
	LED_off(LED3_PORT , LED3_PIN);
	LED_off(LED4_PORT , LED4_PIN);
	
	
	TMR0_init(); /** INITIALIZE TMR0 **/
	
	EXTINT0_init(); /** INITIALIZE INT0 **/
	
	EXTINT1_init(); /** INITIALIZE INT  **/
	
	while (1)
	{
		
		if (LED_mode >= 8)  /** RETURN TO LED MODE 0 AGAIN **/
		{
			LED_mode =  0;
		}
		
		if (blinking_mode >= 5) /** RETURN TO BLINKING MODE 0 AGAIN **/
		{
			blinking_mode = 0 ;
		}
		
		
		switch (blinking_mode)  /** SWICH CASE ON BLINKING MODE **/
		{
			case 0 :
			
			if (LED_mode == 0) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if(LED_mode == 1) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 2) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 3) /** LED 1 , 2 , 3  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 4) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 5) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(100);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 6) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(100);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(900);
			}
			
			else if(LED_mode == 7) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(100);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(900);
			}
			
			break ;
			
			case 1 :
			
			if (LED_mode == 0) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if(LED_mode == 1) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 2) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 3) /** LED 1 , 2 , 3  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 4) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 5) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 6) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
			}
			
			else if(LED_mode == 7) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
			}
			break ;
			
			case 2 :
			
			if (LED_mode == 0) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if(LED_mode == 1) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 2) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 3) /** LED 1 , 2 , 3  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 4) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 5) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(300);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 6) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(300);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(700);
			}
			
			else if(LED_mode == 7) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(300);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(700);
			}
			break ;
			
			case 3 :
			
			if (LED_mode == 0) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if(LED_mode == 1) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 2) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 3) /** LED 1 , 2 , 3  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 4) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 5) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 6) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
			}
			
			else if(LED_mode == 7) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
			}
			break;
			
			case 4 :
			
			if (LED_mode == 0) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if(LED_mode == 1) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 2) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 3) /** LED 1 , 2 , 3  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 4) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 5) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				
				LED_on(LED2_PORT , LED2_PIN);
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 6) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				
				LED_on(LED3_PORT , LED3_PIN);
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
			}
			
			else if(LED_mode == 7) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
			}
			break;
			
			default:
			/** DO NOTHING **/
			break;
		}
		
	}
}


/** ISR OF INT0  **/
ISR(INT0_vect)
{
	blinking_mode++ ; /** CHANGE THE BLINKING MODE **/
}

/** ISR OF INT1 **/
ISR(INT1_vect)
{
	LED_mode++ ;  /** CHANGE THE LEDs **/
}