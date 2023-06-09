/***************************************************/
/* Author  : Mustafa Mohammed Abdou                */
/* Date    : 4 April, 2023                         */
/* Version : V01                                   */
/* Hint    : Interface file of external interrupt  */
/***************************************************/


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#define NULL_PTR     ( void * ) 0 

#define GLOBAL_INTERRUPT_STATE_ENABLE    1
#define GLOBAL_INTERRUPT_STATE_DISABLE   0

#define INT_TRIGGER_RISING_EDGE          0
#define INT_TRIGGER_FALLING_EDGE         1
#define INT_TRIGGER_ANY_CHANGE           2
#define INT_TRIGGER_LOW_LEVEL            3


/** TYPE DEFINITION FOR EXTINT ERROR STATUS **/
typedef enum { EXT_INT_SUCCEED = 0 , EXT_INT_FAILURE } enu_extint_error_status_t ;
	
	
/********************************************************/
/** FUNCTION TO SET THE GLOBAL INTERRUPT ENABLE FLAG    */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void EXTINT_setglobalinterrupt(void);

/********************************************************/
/** FUNCTION TO INITIALIZE INT0                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
enu_extint_error_status_t EXTINT0_init(void);

/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT0            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
enu_extint_error_status_t EXTINT0_setcallback( void (*ptr_func)(void) );

/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT1            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
enu_extint_error_status_t EXTINT1_setcallback( void (*ptr_func)(void) );

/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT2            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
enu_extint_error_status_t EXTINT2_setcallback( void (*ptr_func)(void) );

/********************************************************/
/** FUNCTION TO INITIALIZE INT1                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
enu_extint_error_status_t EXTINT1_init(void);

/********************************************************/
/** FUNCTION TO INITIALIZE INT2                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
enu_extint_error_status_t EXTINT2_init(void);


#endif /* EXTERNAL_INTERRUPT_H_ */