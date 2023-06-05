/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : implementation of APP APIs           */
/**************************************************/

#include <util/delay.h>  /** TO CALL _delay_ms()  **/

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INTERFACE FILES OF LOWER LAYERS **/
#include "../MCAL/dio/DIO_interface.h"
#include "../HAL/button/button_interface.h"
#include "../HAL/button/button_config.h"

#include "../HAL/led/LED_interface.h"
#include "../HAL/led/LED_config.h"

/** INCLUDE LAYER FILES **/
#include "APP.h"


/** VARIABLE TO HOLD BUTTON STATUS , COUNTER FOR PRESSING TIMES **/
static uint8_t u8_gl_button1_status  , u8_gl_button1_counter  ;


/** LEDs INITIALIZATION FUNCTION **/
enu_app_error_status_t LEDs_init(void)
{
	enu_led_error_status_t enu_ledstatus      = LED_SUCCEED    ;    /** LOCAL VARIABLE TO RETURN LEDs FUNCTION ERROR STATUS **/
	enu_app_error_status_t enu_ledinit_status = APP_SUCCEED    ;    /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS        **/
	
	
	enu_ledstatus = LED_init(LED1_PORT , LED1_PIN);           /** LED 1  INITIALIZATION **/
	
	if ( enu_ledstatus == LED_SUCCEED )  /** LED1 INIT SUCCEEDED  **/
	{
		enu_ledstatus = LED_init(LED2_PORT , LED2_PIN);       /** LED 2  INITIALIZATION **/
		
		if ( enu_ledstatus == LED_SUCCEED )  /** LED2 INIT SUCCEEDED  **/
		{
			enu_ledstatus = LED_init(LED3_PORT , LED3_PIN);   /** LED 3 INITIALIZATION **/
			
			if ( enu_ledstatus == LED_SUCCEED )  /** LED3 INIT SUCCEEDED  **/
			{
				enu_ledstatus = LED_init(LED4_PORT , LED4_PIN);  /** LED 4 INITIALIZATION **/
				
				if ( enu_ledstatus == LED_SUCCEED )  /** LED4 INIT SUCCEEDED  **/
				{
					/** DO NOTHING **/
				}
				
				else  /** LED4 INIT FAILED **/
				{
					enu_ledinit_status = APP_FAILURE ; /** RETURN APP FAILURE **/
				}
			}
			
			else   /** LED3 INIT FAILED **/
			{
				enu_ledinit_status = APP_FAILURE ; /** RETURN APP FAILURE **/
			}
			
		}
		
		else   /** LED2 INIT FAILED **/
		{
			enu_ledinit_status = APP_FAILURE ; /** RETURN APP FAILURE **/
		}
	}
	
	else   /** LED1 INIT FAILED **/
	{
		enu_ledinit_status = APP_FAILURE ; /** RETURN APP FAILURE **/
	}
	
	return enu_ledinit_status ;  /** RETURN THE FINAL STATUS **/
	
}


/** BUTTONS INITIALIZATION FUNCTION **/
enu_app_error_status_t BTNs_init(void)
{
	enu_button_error_status_t enu_btnstatus   = BUTTON_SUCCEED ;    /** LOCAL VARIABLE TO RETURN LEDs FUNCTION ERROR STATUS **/
	enu_app_error_status_t enu_btninit_status = APP_SUCCEED    ;    /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS        **/
	
	/** BUTTON INITIALIZATION **/
	enu_btnstatus = BTN_init(BUTTON1_PORT , BUTTON1_PIN);
	
	if ( enu_btnstatus == BUTTON_SUCCEED) /** BUTTON INITIALIZATION SUCCEEDED **/
	{
		/** DO NOTHING **/
	}
	
	else  /** BUTTON INITIALIZATION FAILED **/
	{
		enu_btninit_status = APP_FAILURE ; /** RETURN FAILURE **/
	}
	
	return enu_btninit_status ; /** RETURN THE FINAL STATUS **/
}


/** FUNCTION TO SET ALL LEDs OFF **/
enu_app_error_status_t LEDs_off(void)
{
	enu_led_error_status_t enu_led_state    = LED_SUCCEED ;  /** LOCAL VARIABLE TO RETURN LED FUNCTION STATUS **/ 
	enu_app_error_status_t enu_ledoff_state = APP_SUCCEED ;  /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	
	enu_led_state = LED_off(LED1_PORT , LED1_PIN);
	
	if( enu_led_state == LED_SUCCEED )
	{
		enu_led_state = LED_off(LED2_PORT , LED2_PIN);
		
		if ( enu_led_state == LED_SUCCEED )
		{
			enu_led_state = LED_off(LED3_PORT , LED3_PIN);
			
			if ( enu_led_state == LED_SUCCEED )
			{
				enu_led_state = LED_off(LED4_PORT , LED4_PIN);
				
				if ( enu_led_state == LED_SUCCEED)
				{
					/** DO NOTHING **/
				}
				
				else  /** LED 4 FAILED **/
				{
					enu_ledoff_state = APP_FAILURE ;/** RETURN APP FAILURE **/
				}
			}
			
			else  /** LED 3 FAILED **/
			{
				enu_ledoff_state = APP_FAILURE ;/** RETURN APP FAILURE **/
			}
		}
		
		else  /** LED 2 FAILED **/
		{
			enu_ledoff_state = APP_FAILURE ;/** RETURN APP FAILURE **/
		}
	}
	
	else /** LED 1 FAILED **/
	{
		enu_ledoff_state = APP_FAILURE ;/** RETURN APP FAILURE **/
	}
	
	
	return enu_ledoff_state ; /** RETURN THE FINAL STATUS **/
}


/** INITIALIZATION FUNCTION **/
enu_app_error_status_t APP_init(void)
{ 
	enu_app_error_status_t enu_l_appinit_status = APP_SUCCEED    ;    /** LOCAL VARIABLE TO RETURN THE FUNCTION ERROR STATUS  **/
	
	/** INITIALIZE THE GLOBAL VARIABLES TO ZERO **/
	u8_gl_button1_status = 0  ;  
	u8_gl_button1_counter = 0 ;
	
	enu_l_appinit_status = LEDs_init();  /** INITIALIZE LEDS **/
	
	if ( enu_l_appinit_status == APP_SUCCEED )
	{
		enu_l_appinit_status = BTNs_init(); /** INITIALIZE BUTTONS **/
		
		if ( enu_l_appinit_status == APP_SUCCEED ) /** BUTTONS INITIALIZED SUCCESSFULLY **/
		{
		
			enu_l_appinit_status = LEDs_off();  /** INITIALIZE LEDS TO BE OFF **/
			
			if ( enu_l_appinit_status == APP_SUCCEED )
			{
				/** DO NOTHING **/
			}
			
			else /** LEDs_off FAILED **/
			{
				enu_l_appinit_status == APP_FAILURE ; /** RETURN FAILURE **/
			}
		}
		
		else  /** BTNs_init FAILED **/
		{
			enu_l_appinit_status = APP_FAILURE ; /** RETURN FAILURE **/
		}
	}
	
	else  /** LEDs_init FAILED **/
	{
		enu_l_appinit_status = APP_FAILURE ; /** RETURN FAILURE **/
	}
	
	return enu_l_appinit_status ; /** RETURN THE FINAL STATUS **/
}

/** MAIN LOGIC **/
void APP_start(void)
{
	BTN_ispressed(BUTTON1_PORT , BUTTON1_PIN , &u8_gl_button1_status);  /** GET THE STATUS OF THE BUTTON **/

	if (u8_gl_button1_status == BUTTON_PRESSED)    /** IF BUTTON IS PRESSED **/
	{
		_delay_ms(30);     /** DELAY FOR 30 ms TO AVOID BOUNCING **/
		
		BTN_ispressed(BUTTON1_PORT , BUTTON1_PIN , &u8_gl_button1_status); /** GET THE STATUS OF THE BUTTON AGAIN **/
		
		if (u8_gl_button1_status == BUTTON_PRESSED)   /** IF STATE IS STILL 1 **/
		{
			u8_gl_button1_counter++ ;      /** UPDATE BUTTON 1 COUNTER **/
			
			/** DISPLAY THE PATTERN ACCORDING TO THE NUMBER OF PRESS TIMES (COUNTER) */
			if (u8_gl_button1_counter == PATTERN_1)
			{
				LED_pattern1();
			}
			
			else if(u8_gl_button1_counter == PATTERN_2)
			{
				LED_pattern2();
			}
			
			else if(u8_gl_button1_counter == PATTERN_3)
			{
				LED_pattern3();
			}
			
			else if(u8_gl_button1_counter == PATTERN_4)
			{
				LED_pattern4();
			}
			
			else if(u8_gl_button1_counter == PATTERN_5)
			{
				LED_pattern5();
			}
			
			else if(u8_gl_button1_counter == PATTERN_6)
			{
				LED_pattern6();
				
			}
			
			else if(u8_gl_button1_counter == PATTERN_7)
			{
				LED_pattern7();
				
			}
			
			else if(u8_gl_button1_counter == PATTERN_8)
			{
				LED_pattern8();
				u8_gl_button1_counter = 0 ; /** REINITIALIZE THE COUNTER TO START FROM PATTERN 1 AGAIN */
			}
			
			while(u8_gl_button1_status)
			{
				BTN_ispressed(BUTTON1_PORT , BUTTON1_PIN , &u8_gl_button1_status);
			}
			
		}
		
	}
	 
}