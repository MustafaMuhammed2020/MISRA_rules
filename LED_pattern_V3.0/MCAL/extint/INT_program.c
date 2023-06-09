/***************************************************/
/* Author  : Mustafa Mohammed Abdou                */
/* Date    : 4 April, 2023                         */
/* Version : V01                                   */
/* Hint    : implementation of external interrupts */
/***************************************************/

/** INCLUDE LIBRARIES **/
#include <avr/interrupt.h>

#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/common_macros.h"

/** INCLUDE DRIVER FILES **/
#include "INT_interface.h"
#include "INT_private.h"
#include "INT_config.h"


void ( * ptr_func_exint0_callback ) ( void );  /** GLOBAL POINTER TO FUNCTION FOR EXTINT0 CALL BACK **/

void ( * ptr_func_exint1_callback ) ( void );  /** GLOBAL POINTER TO FUNCTION FOR EXTINT1 CALL BACK **/

void ( * ptr_func_exint2_callback ) ( void );  /** GLOBAL POINTER TO FUNCTION FOR EXTINT2 CALL BACK **/

/********************************************************/
/** FUNCTION TO SET THE GLOBAL INTERRUPT ENABLE FLAG    */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void EXTINT_setglobalinterrupt(void)
{
	#if GLOBAL_INTERRUPT_STATE  ==  GLOBAL_INTERRUPT_STATE_ENABLE /** ENABLE GLOBAL INTERRUPTS **/
		set_bit(SREG , 7);
	  
	#elif GLOBAL_INTERRUPT_STATE == GLOBAL_INTERRUPT_STATE_DISABLE /** DISABLE GLOBAL INTERRUPTS **/
		clear_bit(SREG , 7);
	  
	#endif
}


/********************************************************/
/** FUNCTION TO INITIALIZE INT0                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : enu_extint_error_status_t              */
/********************************************************/
enu_extint_error_status_t EXTINT0_init(void)
{
	enu_extint_error_status_t enu_l_extint0_init_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	EXTINT_setglobalinterrupt(); /** ENABLE GLOBAL INTERRUPTS */

	/** CONFIGURE THE INT0 TRIGGER EVENT **/
	#if  EXTERNAL_INT0_TRIGGER   ==  INT_TRIGGER_RISING_EDGE 
		set_bit(MCUCR , 0);
		set_bit(MCUCR , 1);
	  
	#elif  EXTERNAL_INT0_TRIGGER  == INT_TRIGGER_FALLING_EDGE
		set_bit(MCUCR , 1);
		clear_bit(MCUCR  , 0);
	  
	#elif EXTERNAL_INT0_TRIGGER  ==  INT_TRIGGER_LOW_LEVEL
		clear_bit(MCUCR , 0);
		clear_bit(MCUCR , 1);
	  
	#elif EXTERNAL_INT0_TRIGGER  == INT_TRIGGER_ANY_CHANGE
		set_bit(MCUCR , 0);
		clear_bit(MCUCR ,1);
		
	#else
		enu_l_extint0_init_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/	
	  
	#endif
	
	
	/** Enable INT0 **/
	set_bit(GICR , 6);	
	
	return enu_l_extint0_init_error_status ;  /** RETURN THE FUNCTION FINAL STATUS **/
}


/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT0            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
enu_extint_error_status_t EXTINT0_setcallback( void (* ptr_func) (void) )
{
	enu_extint_error_status_t enu_l_extint0_setcallback_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	if ( ptr_func == NULL_PTR ) /** THE PASSED POINTER IS INVALID **/
	{
		enu_l_extint0_setcallback_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/
	}
	else
	{
		ptr_func_exint0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
	}
	
	return enu_l_extint0_setcallback_error_status ; /** RETURN THE FUNCTION FINAL STATUS **/
	
}

/********************************************************/
/** FUNCTION TO INITIALIZE INT1                        **/
/** ARGUMENTS  : VOID                                  **/
/** RETURNS    : VOID                                  **/
/********************************************************/
enu_extint_error_status_t EXTINT1_init(void)
{
	enu_extint_error_status_t enu_l_extint1_init_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	EXTINT_setglobalinterrupt(); /** ENABLE GLOBAL INTERRUPTS **/
	
		/** CONFIGURE THE INT1 TRIGGER EVENT **/
	#if EXTERNAL_INT1_TRIGGER  == INT_TRIGGER_RISING_EDGE 
	
		set_bit(MCUCR , 2);
		set_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_FALLING_EDGE
	 
		clear_bit(MCUCR , 2);
		set_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_LOW_LEVEL
	  
		clear_bit(MCUCR , 2);
		clear_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_ANY_CHANGE
	
		set_bit(MCUCR , 2);
		clear_bit(MCUCR , 3);
		
	#else
		enu_l_extint1_init_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/
	  
	#endif

     /** Enable INT1 **/
	set_bit(GICR , 7);
	
	return enu_l_extint1_init_error_status ;  /** RETURN THE FUNCTION FINAL STATUS **/
}

/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT1            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : enu_extint_error_status_t                             **/
/************************************************************************/
enu_extint_error_status_t EXTINT1_setcallback( void ( * ptr_func) (void) )
{
	enu_extint_error_status_t enu_l_extint1_setcallback_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	if ( ptr_func == NULL_PTR ) /** THE PASSED POINTER IS INVALID **/
	{
		enu_l_extint1_setcallback_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/
	}
	else
	{
		ptr_func_exint0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
	}
	
	return enu_l_extint1_setcallback_error_status ; /** RETURN THE FUNCTION FINAL STATUS **/
	
}

/********************************************************/
/** FUNCTION TO INITIALIZE INT2                        **/
/** ARGUMENTS  : VOID                                  **/
/** RETURNS    : enu_extint_error_status_t             **/
/********************************************************/
enu_extint_error_status_t EXTINT2_init(void)
{
	enu_extint_error_status_t enu_l_extint2_init_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	EXTINT_setglobalinterrupt(); /** ENABLE GLOBAL INTERRUPTS **/
	
	
	/** CONFIGURE THE INT2 TRIGGER EVENT **/
	#if EXTERNAL_INT2_TRIGGER == INT_TRIGGER_FALLING_EDGE
	  
		clear_bit(MCUCSR , 6);
	  
	#elif EXTERNAL_INT2_TRIGGER == INT_TRIGGER_RISING_EDGE
	  
		set_bit(MCUCSR , 6);
	  
	    
	#elif EXTERNAL_INT2_TRIGGER == INT_TRIGGER_LOW_LEVEL
			
		  
	#elif EXTERNAL_INT2_TRIGGER == INT_TRIGGER_ANY_CHANGE
	
	#else
		enu_l_extint2_init_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/
	  
	#endif
	
	/** Enable INT2 **/
	set_bit(GICR , 5);
	
	return enu_l_extint2_init_error_status ;  /** RETURN THE FUNCTION FINAL STATUS **/
}


/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT2            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : enu_extint_error_status_t                             **/
/************************************************************************/
enu_extint_error_status_t EXTINT2_setcallback( void (*ptr_func)(void) )
{
	enu_extint_error_status_t enu_l_extint2_setcallback_error_status = EXT_INT_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	if ( ptr_func == NULL_PTR ) /** THE PASSED POINTER IS INVALID **/
	{
		enu_l_extint2_setcallback_error_status = EXT_INT_FAILURE ;  /** RETURN FAILURE **/
	}
	else
	{
		ptr_func_exint0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
	}
	
	return enu_l_extint2_setcallback_error_status ; /** RETURN THE FUNCTION FINAL STATUS **/
	
}


// /** ISR OF INT0  **/
// ISR(INT0_vect)
// {
// 	ptr_func_exint0_callback() ; 
// }
// 
// /** ISR OF INT1 **/
// ISR(INT1_vect)
// {
// 	ptr_func_exint1_callback() ;
// }

// /** ISR OF INT1 **/
// ISR(INT2_vect)
// {
// 	ptr_func_exint2_callback() ;
// }

