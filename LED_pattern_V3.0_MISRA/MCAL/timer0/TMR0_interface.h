/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 5 , April 2023                                       */
/* Version : V01                                                  */
/* Hint    : Interface file of Timer 0                            */
/******************************************************************/ 

#ifndef TMR0_INTERFACE_H
#define TMR0_INTERFACE_H


/** MACROS FOR THE CLOCK SOURCE  **/
#define INTERNAL_CLK_SRC                       0
#define EXTERNAL_CLK_SRC                       1
  
  
/** MACROS FOR EXTERNAL SOURCE OUNTING ACTION **/ 
#define FALLING_EDGE_CNT                       0
#define RISING_EDGE_CNT                        1

/** MACROS FOR DIFFERENT OPERATING MODES FOR TMR0 **/
#define TMR0_NORMAL_MODE                       0
#define TMR0_FASTPWM_NON_INVERTED_MODE         1
#define TMR0_FASTPWM_INVERTED_MODE             2
#define TMR_PHASE_CORRECT_NON_INVERTED_MODE    3
#define TMR_PHASE_CORRECT_INVERTED_MODE        4
#define TMR0_CTC_MODE                          5

/** MACROS FOR ACTION ON COMPARE  **/
#define SET_ON_COMPARE                         0
#define CLEAR_ON_COMPARE                       1
#define TOOGLE_ON_COMPARE                      2


/** MACROS TO CONFIGURE TMR0 PRESCALLER **/
#define NO_PRESCALER                           0
#define PRESCALER_8                            1
#define PRESCALER_64                           2
#define PRESCALER_256                          3
#define PRESCALER_1024                         4



/** TYPE DEFINITION FOR TIMER0 ERROR STATUS **/
typedef enum { TIMER0_SUCCEED = 0  , TIMER0_FAILURE } enu_timer0_error_status_t ;
	
	
/****************************************************************/
/** FUNCTION TO INITIALIZE TMR0 WITH SOME CONFIGURATIONS        */
/** ARGUMENTS  : VOID                                           */
/** RETURNS    : enu_timer0_error_status_t                      */
/****************************************************************/
enu_timer0_error_status_t TMR0_init(void);



/*******************************************************************************/
/** FUNCTION TO LET TIMER 0 START WORK BY ASSIGN PRESCALLER OR CLOCK SOURCE    */
/** ARGUMENTS  : VOID                                                          */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
enu_timer0_error_status_t TMR0_start(void);


/*******************************************************************************/
/** FUNCTION TO STOP TIMER 0                                                   */
/** ARGUMENTS  : VOID                                                          */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
void TMR0_stop(void);


/*******************************************************************************/
/** FUNCTION TO SET DELAY USING TIMER 0                                        */
/** ARGUMENTS  : TAKES DELAY IN ms                                             */
/** RETURNS    : enu_timer0_error_status_t                                     */
/*******************************************************************************/
enu_timer0_error_status_t TMR0_delay_ms(uint32_t DELAY_MS);


#endif