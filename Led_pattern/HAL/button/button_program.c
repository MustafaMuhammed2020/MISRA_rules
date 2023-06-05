/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Implementation of button APIs        */
/**************************************************/

/** INCLUDE THE LIBRARIES */
#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/common_macros.h"

/** INCLUDE INTERFACE OF LOWER LAYERS **/
#include "../../MCAL/dio/DIO_interface.h"


/** INCLUDE THE DRIVER FILES */
#include "button_interface.h"
#include "button_config.h"


/*****************************************************************/
/* FUNCTION TO INITIALIZE THE BUTTON                             */
/* ARGUMENTS : TAKES THE BUTTON PORT AND PIN                     */
/* RETURN    : enu_buttonerrorstatus_t                           */
/*****************************************************************/
enu_button_error_status_t BTN_init(uint8_t u8_a_button_port , uint8_t u8_a_button_pin)
{
	enu_dio_error_status_t   enu_l_btnpin_state  = DIO_SUCCEED ;      /** LOCAL VARIABLE TO RETURN THE BUTTON PIN STATUS  **/ 
	
	enu_button_error_status_t  enu_l_btninit_state = BUTTON_SUCCEED ;  /** LOCAL VARIABLE TO RETURN THE FUNCTION ERROR STATE **/
	
	
	/** SET THE DIRECTION OF BUTTON AS INPUT **/
	enu_l_btnpin_state = DIO_setpindir(u8_a_button_port , u8_a_button_pin , DIO_PIN_INPUT);
	
	if ( enu_l_btnpin_state == DIO_SUCCEED )  /** BUTTON PIN INITIALIZED SUCCESSFULLY  **/
	{
		/** DO NOTHING **/
	}
	
	else
	{
		enu_l_btninit_state = BUTTON_FAILURE ;  /** RETURN BUTTON FAILURE  **/
	}
	
	return enu_l_btninit_state ;  /** RETURN THE FUNCTION FINAL STATE  **/
}


/*****************************************************************/
/* FUNCTION TO CHECK THE BUTTON STATUS PRESSED OR NOT            */
/* ARGUMENTS : TAKES THE BUTTON PORT AND PIN                     */
/* RETURN    : enu_buttonerrorstatus_t                           */
/*****************************************************************/
enu_button_error_status_t BTN_ispressed(uint8_t u8_a_button_port , uint8_t u8_a_button_pin , uint8_t * u8_a_buttonstate)
{
	enu_button_error_status_t enu_l_btnispressed_state = BUTTON_SUCCEED ;   /** LOCAL VARIABLE TO RETURN THE FINCTION ERROR STATE **/
	
	enu_dio_error_status_t enu_l_btndiostate = DIO_SUCCEED ;              /** LOCAL VARIABLE TO RETURN THE BUTTON DIO STATE  **/
	
	uint8_t u8_l_buttonvalue = 0 ;     /** LOCAL VARIABLE TO GET THE BUTTON VALUE (0 / 1) **/
	
	enu_l_btndiostate = DIO_readpin(u8_a_button_port , u8_a_button_pin , &u8_l_buttonvalue);  /** READ THE VALUE OF BUTTON'S PIN */
	
	if ( enu_l_btndiostate == DIO_SUCCEED ) 
	{
		*u8_a_buttonstate = u8_l_buttonvalue ;   /** STORE THE VALUE OF PIN IN THE PASSED ARGUMENT **/
	}
	
	else
	{
		enu_l_btnispressed_state = BUTTON_FAILURE ;  /** RETURN FAILURE **/
	}
	
	return enu_l_btnispressed_state ;   /** RETURN THE STATUS OF BTN_ispressed FUNCTION **/
}
