/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Interface file of buttons            */
/**************************************************/

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H


/** MACROS FOR BUTTON STATUS **/
#define BUTTON_NOT_PRESSED  0
#define BUTTON_PRESSED      1


/** TYPE DEFINITION BUTTON'S FUNCTIONS  ERROR STATUS  **/
typedef enum { BUTTON_SUCCEED = 0 , BUTTON_FAILURE } enu_button_error_status_t;


/*****************************************************************/
/* FUNCTION TO INITIALIZE THE BUTTON                             */
/* ARGUMENTS : TAKES THE BUTTON PORT AND PIN                     */
/* RETURN    : enu_buttonerrorstatus_t                           */
/*****************************************************************/
enu_button_error_status_t BTN_init(uint8_t u8_a_button_port , uint8_t u8_a_button_pin);


/*****************************************************************/
/* FUNCTION TO CHECK THE BUTTON STATUS PRESSED OR NOT            */
/* ARGUMENTS : TAKES THE BUTTON PORT AND PIN                     */
/* RETURN    : enu_buttonerrorstatus_t                           */
/*****************************************************************/
enu_button_error_status_t BTN_ispressed(uint8_t u8_a_button_port , uint8_t u8_a_button_pin , uint8_t * u8_a_buttonstate);




#endif