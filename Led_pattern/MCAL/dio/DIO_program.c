/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 3 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Program file of DIO                  */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE DRIVER FILES **/
#include "DIO_interface.h"
#include "DIO_private.h"


/***********************************************************************/
/* DESCRIBTION  : FUNCTION TO SET THE DIRECTION OF SPECIFIC PIN        */
/* INPUT        : PORT , PINID , DIRECTION                             */
/* RETURNS      : enu_dio_error_status_t                               */
/***********************************************************************/
enu_dio_error_status_t DIO_setpindir(uint8_t u8_a_portid , uint8_t u8_a_pinid , uint8_t u8_a_pindir)
{
	enu_dio_error_status_t enu_l_setpindir_state = DIO_SUCCEED ; /** LOCAL VARIABLE TO RETURN THE STATUS OF DIRECTION **/
	
	switch(u8_a_pindir)            /** SWITCH CASE ON THE DIRECTION VALUE **/
	{
		case DIO_PIN_INPUT:        /** INPUT CASE  **/
		{
			switch(u8_a_portid)    /** SWITCH CASE ON THE PORT ID **/
			{
				case DIO_PORTA:
				clear_bit(DDRA , u8_a_pinid);           /** CONFIGURE THIS PIN IN PORTA AS INPUT PIN **/
				break ;
				
				case DIO_PORTB:
				clear_bit(DDRB , u8_a_pinid);           /** CONFIGURE THIS PIN IN PORTB AS INPUT PIN **/
				break ;
				
				case DIO_PORTC:
				clear_bit(DDRC , u8_a_pinid);           /** CONFIGURE THIS PIN IN PORTC AS INPUT PIN **/
				break ;
				
				case DIO_PORTD:
				clear_bit(DDRD , u8_a_pinid);           /** CONFIGURE THIS PIN IN PORTD AS INPUT PIN **/
				break ;
				
				default: 
				enu_l_setpindir_state = DIO_FAILURE ;   /** RETURN AS DIR NOT VALID ERRORS **/
				break ;
			}
			
			break ; /** BREAK OF INPUT CASE **/
		}
		
		
		case DIO_PIN_OUTPUT:              /** OUTPUT CASE  **/
		{
			switch(u8_a_portid)           /** SWITCH CASE ON THE PORT ID */
			{
				case DIO_PORTA:
				set_bit(DDRA , u8_a_pinid);             /** CONFIGURE THIS PIN IN PORTA AS OUTPUT PIN **/
				break ;
				
				case DIO_PORTB:
				set_bit(DDRB , u8_a_pinid);             /** CONFIGURE THIS PIN IN PORTA AS OUTPUT PIN **/
				break ;
				
				case DIO_PORTC:
				set_bit(DDRC , u8_a_pinid);             /** CONFIGURE THIS PIN IN PORTA AS OUTPUT PIN **/
				break ;
				
				case DIO_PORTD:
				set_bit(DDRD , u8_a_pinid);             /** CONFIGURE THIS PIN IN PORTA AS OUTPUT PIN **/
				break ;
				
				default:  
				enu_l_setpindir_state = DIO_FAILURE ; /** RETURN AS DIR NOT VALID ERRORS **/
				break ;
			}
			
			break ; /** BREAK OF OUTPUT CASE **/
		}
		
		 
		default:  /** DIRECTION ISN'T INPUT OR OUTPUT */
		
		enu_l_setpindir_state = DIO_FAILURE ; /** RETURN AS DIR NOT VALID ERRORS **/
		
		break ; 
	} 
	
	return enu_l_setpindir_state ; /** RETURN THE STATE OF FUNCTION **/
}


/***********************************************************************/
/* DESCRIBTION  : FUNCTION TO SET THE VALUE OF SPECIFIC PIN            */
/* INPUT        : PORT , PINID , DIRECTION                             */
/* RETURNS      : enu_dio_error_status_t                               */
/***********************************************************************/
enu_dio_error_status_t DIO_setpinvalue(uint8_t u8_a_portid , uint8_t u8_a_pinid , uint8_t u8_a_pinval)
{
	
	enu_dio_error_status_t enu_l_setpinval_state = DIO_SUCCEED ;  /** LOCAL VARIABLE TO RETURN THE STATUS OF VALUE **/ 
	
	switch(u8_a_pinval)
	{
		case DIO_PIN_LOW:            /** IN CASE PIN VALUE IS LOW  **/
		{
			switch(u8_a_portid)     /** SWITCH CASE ON THE PORT ID **/
			{
				case DIO_PORTA:
				clear_bit(PORTA , u8_a_pinid);       /** SET THIS PIN AS LOW **/
				break ;
				
				case DIO_PORTB:
				clear_bit(PORTB , u8_a_pinid);       /** SET THIS PIN AS LOW **/
				break ;
				
				case DIO_PORTC:
				clear_bit(PORTC , u8_a_pinid);       /** SET THIS PIN AS LOW **/
				break ;
				
				case DIO_PORTD:
				clear_bit(PORTD , u8_a_pinid);       /** SET THIS PIN AS LOW **/
				break ;
				
				default:
				enu_l_setpinval_state = DIO_FAILURE ;  /** RETURN VALUE AS NOT VALID **/
				break;
			}
			
			break ;  /** BREAK OF DIO_PIN_LOW CASE **/
		}
		
		
		case DIO_PIN_HIGH:        /** IN CASE PIN VALUE IS HIGH **/
		{
			switch(u8_a_portid)   /** SWITCH CASE ON THE PORT ID **/
			{
				case DIO_PORTA:
				set_bit(PORTA , u8_a_pinid);         /** SET THIS PIN AS HIGH  **/
				break ;
				
				case DIO_PORTB:
				set_bit(PORTB , u8_a_pinid);         /** SET THIS PIN AS HIGH  **/
				break ;
				
				case DIO_PORTC:
				set_bit(PORTC , u8_a_pinid);         /** SET THIS PIN AS HIGH  **/
				break ;
				
				case DIO_PORTD:
				set_bit(PORTD , u8_a_pinid);         /** SET THIS PIN AS HIGH  **/
				break ;
				
				default:
				enu_l_setpinval_state = DIO_FAILURE ;  /** RETURN VALUE AS NOT VALID **/
				break ;
			}
			
			break ;   /** BREAK OF DIO_PIN_HIGH CASE **/
		}
		
		
		default :
		enu_l_setpinval_state = DIO_FAILURE ;  /** RETURN VALUE AS NOT VALID **/
		break ;
	} 
	
	return enu_l_setpinval_state ;    /** RETURN THE FINAL STATE OF THE FUNCTION **/
}


/******************************************************************/
/* DESCRIBTION  : FUNCTION TO GET THE VALUE OF SPECIFIC PIN       */
/* INPUT   : PORTID , PINID , POINTER TO SET THE VALUE IN IT      */
/* RETURNS : PinRead_t                                            */
/******************************************************************/
enu_dio_error_status_t DIO_readpin(uint8_t u8_a_portid , uint8_t u8_a_pinid , uint8_t* u8_a_retval)
{
	enu_dio_error_status_t enu_l_readpin_state = DIO_SUCCEED ;  /** LOCAL VARIABLE TO HOLD THE FUNCTION ERROR STATE **/
	
	switch(u8_a_portid)      /** SWITCH CASE ON PORT ID **/
	{
		case DIO_PORTA:     
		*u8_a_retval = get_bit(PINA , u8_a_pinid);   /** GET THE VALUE OF THE BIT **/
		break ;
		
		case DIO_PORTB:      
		*u8_a_retval = get_bit(PINB , u8_a_pinid);   /** GET THE VALUE OF THE BIT **/
		break ;
		
		case DIO_PORTC:    
		*u8_a_retval = get_bit(PINC , u8_a_pinid);   /** GET THE VALUE OF THE BIT **/
		break ;
		
		case DIO_PORTD:      
		*u8_a_retval = get_bit(PIND , u8_a_pinid);   /** GET THE VALUE OF THE BIT **/
		break ;
		
		default:
		enu_l_readpin_state = DIO_FAILURE ;         /**      READ IS NOT VALID    **/
		break ;
	} 
	
	return enu_l_readpin_state ;          /** RETURN THE FINAL STATE OF THE FUNCTION **/	
}