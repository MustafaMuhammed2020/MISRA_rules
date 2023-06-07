/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Implementation of Timer 0 APIs                       */
/******************************************************************/ 

/** INCLUDE LIBRARIES **/
#include <avr/interrupt.h>

#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYER FILES **/
#include "../dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "TMR0_interface.h"
#include "TMR0_private.h"
#include "TMR0_config.h"

void ( * ptr_func_tmr0_callback ) ( void );  /** GLOBAL VARIABLE FOR TIMER0 CALL BACK **/


static uint8_t u8_gs_delay_ovs = 0 ;  /** GLOBAL VARIABLE TO HOLD NUMBER OF OVER FLOWS NEEDED FOR SPECIFIC DELAY **/


static uint32_t u32_gs_overflowcounter = 0 ;  /** LOCAL VARIABLE TO COUNT OVER FLOW **/

/****************************************************************/
/** FUNCTION TO INITIALIZE TMR0 WITH SOME CONFIGURATIONS        */
/** ARGUMENTS  : VOID                                           */
/** RETURNS    : enu_timer0_error_status_t                      */
/****************************************************************/
enu_timer0_error_status_t TMR0_init(void)
{
	enu_timer0_error_status_t  enu_l_timer0init_retval = TIMER0_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE STATUS OF INITIALIZATION **/
	
	/** COUNTER MODE OF TMR0 **/
	#if TIMER0_CLK_SRC == EXTERNAL_CLK_SRC
	
		  /* EXTERNAL PIN AS CLOCK SOURCE */
		  DIO_setpindir(DIO_PORTB , DIO_PIN0 , DIO_PIN_INPUT);
	  
	      #if CNT0_EXTERNAL_EDGE_MODE == FALLING_EDGE_CNT  /** COUNTING IN FALLING EDGE **/
	  
		    	clear_bit(TCCR0 , 0);
			    set_bit(TCCR0 , 1);
				set_bit(TCCR0 , 2);
	  
		#elif CNT0_EXTERNAL_EDGE_MODE == RISING_EDGE_CNT  /** COUNTING IN RISING EDGE **/
	  
				set_bit(TCCR0 , 0);
				set_bit(TCCR0 , 1);
				set_bit(TCCR0 , 2);
			
		#else
			enu_l_timer0init_retval = TIMER0_FAILURE ;  /** RETURN FAILURE **/
		
		  #endif
	 
	 /** TIMER MODE OF TMR0 **/
	#elif TIMER0_CLK_SRC == INTERNAL_CLK_SRC
	
		 #if TIMER0_MODE == TMR0_NORMAL_MODE
	 
			 clear_bit(TCCR0 , 7);
			 clear_bit(TCCR0 , 6);
			 clear_bit(TCCR0 , 3);
			 clear_bit(TCCR0 , 4);
			 clear_bit(TCCR0 , 5);
	 	 
 			/* ENABLE INTERRUPT */
 			set_bit(SREG , 7);
 			set_bit(TIMSK , 0);
	 
		 #elif TIMER0_MODE == TMR0_FASTPWM_NON_INVERTED_MODE
	 
			set_bit(TCCR0 , 7);
			set_bit(TCCR0 , 6);
			set_bit(TCCR0 , 3);
			clear_bit(TCCR0 , 4);
			set_bit(TCCR0 , 5);
	 
	 
		 #elif TIMER0_MODE == TMR0_FASTPWM_INVERTED_MODE
	 
			set_bit(TCCR0 , 7);
			set_bit(TCCR0 , 6);
			set_bit(TCCR0 , 3);
			set_bit(TCCR0 , 4);
			set_bit(TCCR0 , 5);
	 
		#elif TIMER0_MODE == TMR_PHASE_CORRECT_NON_INVERTED_MODE
	 
			set_bit(TCCR0 , 7);
			set_bit(TCCR0 , 6);
			clear_bit(TCCR0 , 3);
			clear_bit(TCCR0 , 4);
			set_bit(TCCR0 , 5);
	 
		#elif TIMER0_MODE == TMR_PHASE_CORRECT_INVERTED_MODE
	 
			set_bit(TCCR0 , 7);
			set_bit(TCCR0 , 6);
			clear_bit(TCCR0 , 3);
			set_bit(TCCR0 , 4);
			set_bit(TCCR0 , 5);
	 
		#elif TIMER0_MODE == TMR0_CTC_MODE
	 
			DIO_setpindir(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT); /** SET CTC BIT AS OUTPUT PIN **/
	 
			clear_bit(TCCR0 , 7);
			clear_bit(TCCR0 , 6);
			set_bit(TCCR0 , 3);
	 
			/** ENABLE INTERRUPT **/
			set_bit(SREG , 7);
			set_bit(TIMSK , 1);
	 	 
			#if COMPARE_ACTION == SET_ON_COMPARE
	   
				set_bit(TCCR0 , 4);
				set_bit(TCCR0 , 5);
	   
			#elif COMPARE_ACTION == CLEAR_ON_COMPARE
	   
				clear_bit(TCCR0 , 4);
				set_bit(TCCR0 , 5);
	   
			#elif COMPARE_ACTION == TOOGLE_ON_COMPARE
	   
				set_bit(TCCR0 , 4);
				clear_bit(TCCR0 , 5);
			
			#else
				enu_l_timer0init_retval = TIMER0_FAILURE ; /** RETURN FAILURE **/
			
			#endif
		 
		 #else  /** INTERNAL CLK SOURCE MODE IS NOT VALID **/
		 
				enu_l_timer0init_retval = TIMER0_FAILURE ; /** RETURN FAILURE **/
		 #endif
	
	#else /** NOT EXTERNAL CLK SOURCE OR INTERNAL CLK SOURCE **/
	
		enu_l_timer0init_retval = TIMER0_FAILURE ; /** RETURN FAILURE **/
	#endif
	
	
	return enu_l_timer0init_retval ; /** RETURN THE STATUS OF INITIALIZATION **/
}


/*******************************************************************************/
/** FUNCTION TO LET TIMER 0 START WORK BY ASSIGN PRESCALLER OR CLOCK SOURCE    */
/** ARGUMENTS  : VOID                                                          */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
enu_timer0_error_status_t TMR0_start(void)
{
	enu_timer0_error_status_t  enu_l_timer0start_retval = TIMER0_SUCCEED ; /** ;OCAL VARIABLE TO RETURN THE STATUS OF INITIALIZATION **/
	
	#if TIMER0_PRESCALER_VAL == PRESCALER_1024
	
		set_bit(TCCR0 , 0);
		clear_bit(TCCR0 , 1);
		set_bit(TCCR0 , 2);

	#elif TIMER0_PRESCALER_VAL == NO_PRESCALER
	
		set_bit(TCCR0 , 0);
		clear_bit(TCCR0 , 1);
		clear_bit(TCCR0 , 2);
		
	#elif TIMER0_PRESCALER_VAL == PRESCALER_8
	
		clear_bit(TCCR0 , 0);
		set_bit(TCCR0 , 1);
		clear_bit(TCCR0 , 2);
		
	#elif TIMER0_PRESCALER_VAL == PRESCALER_64
	
		set_bit(TCCR0 , 0);
		set_bit(TCCR0 , 1);
		clear_bit(TCCR0 , 2);
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_256
	
		clear_bit(TCCR0 , 0);
		clear_bit(TCCR0 , 1);
		set_bit(TCCR0 , 2);
	
	#else /** PRESCALLER VALUE IS NOT VALID **/
		
		enu_l_timer0start_retval = TIMER0_FAILURE ; /** RETURN FAILURE **/
	#endif
	
	return enu_l_timer0start_retval ; /** RETURN THE FINAL STATUS **/
}

/*******************************************************************************/
/** FUNCTION TO STOP TIMER 0                                                   */
/** ARGUMENTS  : VOID                                                          */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
void TMR0_stop(void)
{
	
	/** SET CONFIGURATIONS AS NO CLOCK SOURCE **/
	clear_bit(TCCR0 , 0);
	clear_bit(TCCR0 , 1);
	clear_bit(TCCR0 , 2);
}

/*******************************************************************************/
/** FUNCTION TO SET DELAY USING TIMER 0                                        */
/** ARGUMENTS  : TAKES DELAY IN ms                                             */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
enu_timer0_error_status_t TMR0_delay_ms(uint32_t DELAY_MS)
{
	
	
	enu_timer0_error_status_t  enu_l_timer0delayms_retval = TIMER0_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE STATUS OF INITIALIZATION **/
	
	#if TIMER0_PRESCALER_VAL == PRESCALER_1024  /** CHECK THE PRESCALLER FROM CONFIG FILE **/
	
		u8_gs_delay_ovs = (DELAY_MS / 32.768);   /** CALCULATING NUMBER OF OVERFLOWS ( DESIRED DELAY / TIME OF OVER FLOW ) **/
	
		TCNT0 = 0 ;   /** SET THE INITIAL VALUE IN TCNT0 REGISTER **/
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_256

		u8_gs_delay_ovs = (DELAY_MS / 262.144);   /** CALCULATING NUMBER OF OVERFLOWS ( DESIRED DELAY / TIME OF OVER FLOW ) **/
	
		TCNT0 = 0 ;   /** SET THE INITIAL VALUE IN TCNT0 REGISTER **/
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_64
	
		u8_gs_delay_ovs = (DELAY_MS / 1.024);   /** CALCULATING NUMBER OF OVERFLOWS ( DESIRED DELAY / TIME OF OVER FLOW ) **/
	
		TCNT0 = 0 ;   /** SET THE INITIAL VALUE IN TCNT0 REGISTER **/
	
	#elif TIMER0_PRESCALER_VAL == NO_PRESCALER
	
		u8_gs_delay_ovs = (DELAY_MS / 0.016);   /** CALCULATING NUMBER OF OVERFLOWS ( DESIRED DELAY / TIME OF OVER FLOW ) **/
	
		TCNT0 = 0 ;   /** SET THE INITIAL VALUE IN TCNT0 REGISTER **/
	
	#else /** PRESCALLER VALUE IS NOT VALID **/ 
		
		enu_l_timer0delayms_retval = TIMER0_FAILURE ;  /** RETURN FAILURE **/
	#endif
	
	TMR0_start() ; /** START TMR0 COUNTING **/
	
	while ( u32_gs_overflowcounter < u8_gs_delay_ovs ) /** STUCK IN THIS LOOP UNTILL THIS CONDITION IS FALSE **/
	{
		set_bit(TIFR , 0);        /** CLEAR THE FLAG BY SOFTWARE **/
	}
	
	u32_gs_overflowcounter = 0 ; /** REINTIALIZE THE OVERFLOWS COUNTER TO 0 AGAIN **/

	TMR0_stop() ; /** STOP TMR0 TOSTART FROM 0 WHEN IT CALLED AGAIN **/
	
	return enu_l_timer0delayms_retval ; /** RETURN THE STATUS **/
}


/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF TIMER0             **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
void TMR0_setcallback( void (*ptr_func)(void) )
{
	ptr_func_tmr0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
}

/** TIMER0 INTERRUPT SERVICE ROUTINE **/
ISR(TIMER0_OVF_vect)
{
	u32_gs_overflowcounter++ ; /** INCREASE THE OVERFLOWS BY ONE **/
}