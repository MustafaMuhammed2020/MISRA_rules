/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                              **/
/* Date    : 5 , April 2023                                      **/
/* Version : V01                                                 **/
/* Hint    : APIs of application layer                           **/
/******************************************************************/

/** INCLUDE LIBRARIES **/
#include <avr/interrupt.h>

/** INCLUDE LOWER DRIVERS **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

#include "../MCAL/dio/DIO_interface.h"
#include "../HAL/led/LED_interface.h"
#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/extint/INT_interface.h"
#include "../HAL/led/LED_config.h"

/** INCLUDE DRIVER FILES **/
#include "APP.h"


static uint8_t u8_gs_blinking_mode = 0 ;  /** GLOBAL STATIC VARIABLE TO CHANGE LEDs BLINKING MODE  **/
static uint8_t u8_gs_LED_mode  =  0 ;     /** GLOBAL VARIABLE TO CHANGE NUMBER OF BLINKING LEDs    **/


/*******************************************************/
/** FUNCTION TO INITIALIZE LEDS                       **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : enu_app_error_status_t               **/
/*******************************************************/
enu_app_error_status_t LEDs_init(void)
{
	enu_led_error_status_t enu_l_led_error_status = LED_SUCCEED ;  /** LOCAL VARIABLE TO RETURN EACH LED ERROR STATUS **/
	
	enu_app_error_status_t enu_l_ledsinit_error_status = APP_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION ERROR STATUS **/
	
	/** INITIALIZE THE 4 LEDS **/
	
	enu_l_led_error_status = LED_init(LED1_PORT , LED1_PIN); 
	
	if ( enu_l_led_error_status == LED_SUCCEED ) /** LED1 INITIALIZATION SUCCEEDED **/
	{
		enu_l_led_error_status = LED_init(LED2_PORT , LED2_PIN);
		
		if ( enu_l_led_error_status == LED_SUCCEED ) /** LED2 INITIALIZATION SUCCEEDED **/
		{
			enu_l_led_error_status = LED_init(LED3_PORT , LED3_PIN);
			
			if( enu_l_led_error_status == LED_SUCCEED ) /** LED3 INITIALIZATION SUCCEEDED **/
			{
				enu_l_led_error_status = LED_init(LED4_PORT , LED4_PIN); 
				
				if ( enu_l_led_error_status == LED_SUCCEED ) /** LED4 INITIALIZATION SUCCEEDED **/
				{
					/** DO NOTHING **/
				}
				else /** LED4 INITIALIZATION FAILUED **/
				{
					enu_l_ledsinit_error_status = APP_FAILURE ;  /** RETURN FAILURE **/
				}
			}
			else /** LED3 INITIALIZATION FAILUED **/
			{
				enu_l_ledsinit_error_status = APP_FAILURE ;  /** RETURN FAILURE **/
			}
		}
		else /** LED2 INITIALIZATION FAILUED **/
		{
			enu_l_ledsinit_error_status = APP_FAILURE ;  /** RETURN FAILURE **/
		}
	}
	else /** LED1 INITIALIZATION FAILUED **/
	{
		enu_l_ledsinit_error_status = APP_FAILURE ;  /** RETURN FAILURE **/
	}
	
	return enu_l_ledsinit_error_status ;  /** RETURN THE FUNCATION FINAL STATUS **/
}


/*******************************************************/
/** FUNCTION TO TURN OFF ALL LEDS                     **/
/** ARGUMENTS  : VOID                                 **/
/** RETURN     : enu_app_error_status_t               **/
/*******************************************************/
static enu_app_error_status_t LEDs_off(void)
{
	enu_led_error_status_t enu_l_ledstatus = LED_SUCCEED ;       /** LOCAL VARIABLE TO HOLD EACH LED ERROR STATUS **/
	
	enu_app_error_status_t enu_l_ledsoff_status = APP_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION ERROR STATUS **/
	
	/** TURN ALL LEDs OFF **/
	
	enu_l_ledstatus = LED_off(LED1_PORT , LED1_PIN);
	
	if ( enu_l_ledstatus == LED_SUCCEED )
	{
		enu_l_ledstatus = LED_off(LED2_PORT , LED2_PIN);
		
		if ( enu_l_ledstatus == LED_SUCCEED )
		{
			enu_l_ledstatus = LED_off(LED3_PORT , LED3_PIN);
			
			if ( enu_l_ledstatus == LED_SUCCEED)
			{
				enu_l_ledstatus = LED_off(LED4_PORT , LED4_PIN);
				
				if ( enu_l_ledstatus == LED_SUCCEED)
				{
					/** DO NOTHING **/
				}
				else   /** LED4 FAILED **/
				{
					enu_l_ledsoff_status = APP_FAILURE ;  /** RETURN FAILURE **/
				}
			}
			else  /** LED3 FAILED **/
			{
				enu_l_ledsoff_status = APP_FAILURE ;  /** RETURN FAILURE **/
			}
		}
		else  /** LED2 FAILED **/
		{
			enu_l_ledsoff_status = APP_FAILURE ;  /** RETURN FAILURE **/
		}
	}
	else /** LED1 FAILED **/
	{
		enu_l_ledsoff_status = APP_FAILURE ;  /** RETURN FAILURE **/
	}
	
	return enu_l_ledsoff_status ;  /** RETURN THE FUNCTION FINAL STATUS **/
}


/******************************************************/
/** FUNCTION TO INITIALIZE MODULES                   **/
/** ARGUMENTS  : VOID                                **/
/** RETURNS    : enu_app_error_status_t              **/
/******************************************************/
enu_app_error_status_t APP_init(void)
{
	enu_app_error_status_t enu_l_appinit_error_status = APP_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION ERROR STATUS **/
	
	enu_timer0_error_status_t enu_timer0init_status = TIMER0_SUCCEED ;  /** LOCAL VARIABLE TO HOLD TIMER FUNCTIONS ERROR STATUS **/
	
	enu_extint_error_status_t enu_extintinit_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO HOLD EXTINT FUNCTIONS ERROR STATUS **/
	
    enu_l_appinit_error_status = LEDs_init(); /** INITIALIZE ALL LEDS **/
	
	if ( enu_l_appinit_error_status == APP_SUCCEED )
	{
		enu_l_appinit_error_status = LEDs_off();  /** TURN OFF ALL LEDs **/
		
		if( enu_l_appinit_error_status == APP_SUCCEED )
		{
			enu_timer0init_status = TMR0_init(); /** INITIALIZE TMR0 **/
			
			if ( enu_timer0init_status == TIMER0_SUCCEED )
			{
				enu_extintinit_error_status = EXTINT0_init(); /** INITIALIZE INT0 **/
				
				if ( enu_extintinit_error_status == EXT_INT_SUCCEED )
				{
					enu_extintinit_error_status = EXTINT1_init(); /** INITIALIZE INT  **/
					
					if ( enu_extintinit_error_status == EXT_INT_SUCCEED )
					{
						/** DO NOTHING **/
					}
					else  /** EXTINT1 INITIALIZATION FAILED **/
					{
						enu_l_appinit_error_status = APP_FAILURE ; /** RETURN FAILURE **/
					}
				}
				else /** EXTINT0 INITIALIZATION FAILED **/
				{
					enu_l_appinit_error_status = APP_FAILURE ; /** RETURN FAILURE **/
				}
			}
			else /** TIMER0 INITIALIZATION FAILED **/
			{
				enu_l_appinit_error_status = APP_FAILURE ; /** RETURN FAILURE **/
			}
		}
		else  /** TURN OFF LEDs FAILED **/
		{
			enu_l_appinit_error_status = APP_FAILURE ; /** RETURN FAILURE **/
		}
	}
	else /** LEDs INITIALIZATION FAILED **/
	{
		enu_l_appinit_error_status = APP_FAILURE ; /** RETURN FAILURE **/
	}
	
	return enu_l_appinit_error_status ; /** RETURN THE FUNCTION FINAL STATUS **/
}

/******************************************************/
/** APPLICATION MAIN LOGIC                           **/
/** ARGUMENTS  : VOID                                **/
/** RETURNS    : VOID                                **/
/******************************************************/
void APP_start(void)
{
	
	if ( u8_gs_LED_mode >= MAX_LED_MODES )  /** RETURN TO LED MODE 0 AGAIN **/
	{
		u8_gs_LED_mode =  INITIAL_VALUE ;
	}
	
	if ( u8_gs_blinking_mode >= MAX_BLINK_MODE ) /** RETURN TO BLINKING MODE 0 AGAIN **/
	{
		u8_gs_blinking_mode = INITIAL_VALUE ;
	}
	
	
	switch ( u8_gs_blinking_mode )  /** SWICH CASE ON BLINKING MODE **/
	{
		case BLINK_MODE_1 :
		{
			if ( u8_gs_LED_mode == LED_MODE_1 ) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_2 ) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(900);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_3 ) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(100);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(900);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_4 ) /** LED 1 , 2 , 3  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_5 ) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_6 ) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_7 ) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_8 )  /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(100);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(900);
			}	
		}
		break ;
		
		case BLINK_MODE_2 :
		{
			if ( u8_gs_LED_mode == LED_MODE_1 ) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_2 ) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(800);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_3 ) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(200);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(800);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_4 ) /** LED 1 , 2 , 3  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_5 ) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_6 ) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_7 ) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_8 ) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
			}	
		}
		break ;
		
		case BLINK_MODE_3 :
		{
			if ( u8_gs_LED_mode == LED_MODE_1 ) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_2 ) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(700);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_3 ) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(300);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(700);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_4 ) /** LED 1 , 2 , 3  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_5 ) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_6 ) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_7 ) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_8 ) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(300);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(700);
			}
		}
		break ;
		
		case BLINK_MODE_4 :
		{
			if ( u8_gs_LED_mode == LED_MODE_1 ) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_2 ) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(500);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_3 ) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(500);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(500);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_4 ) /** LED 1 , 2 , 3  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_5 ) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_6 ) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_7 ) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_8 ) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(500);
			}	
		}
		break;
		
		case BLINK_MODE_5 :
		{
			if ( u8_gs_LED_mode == LED_MODE_1 ) /** ALL LEDs ARE OFF **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				LED_off(LED4_PORT , LED4_PIN);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_2 ) /** LED 1 IS BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				TMR0_delay_ms(200);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_3 ) /** LED 1 , 2 ARE BLINKING **/
			{
				LED_on(LED1_PORT , LED1_PIN);
				LED_on(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(800);
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				TMR0_delay_ms(200);
			}
			
			else if( u8_gs_LED_mode == LED_MODE_4 ) /** LED 1 , 2 , 3  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_5 ) /** LED 1 , 2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_6 ) /** LED 1 IS OFF AND  2 , 3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_7 ) /** LED 1 , 2 ARE OFF AND  3 , 4  ARE BLINKING **/
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
			
			else if( u8_gs_LED_mode == LED_MODE_8 ) /** LED 1 , 2 , 3 ARE OFF AND  4  IS BLINKING **/
			{
				LED_off(LED1_PORT , LED1_PIN);
				LED_off(LED2_PORT , LED2_PIN);
				LED_off(LED3_PORT , LED3_PIN);
				
				LED_on(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(800);
				LED_off(LED4_PORT , LED4_PIN);
				TMR0_delay_ms(200);
			}	
		}
		break;
		
		default:
			/** DO NOTHING **/
		break;
	}

}


/** ISR OF INT0  **/
ISR(INT0_vect)
{
	u8_gs_blinking_mode++ ; /** CHANGE THE BLINKING MODE **/
}

/** ISR OF INT1 **/
ISR(INT1_vect)
{
	u8_gs_LED_mode++ ;  /** CHANGE THE LEDs **/
}