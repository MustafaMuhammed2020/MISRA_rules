/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : interface file of led                */
/**************************************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/** TYPEDEFINITION FOR LED MODULE ERROR STATUS  **/
typedef enum { LED_SUCCEED = 0 , LED_FAILURE } enu_led_error_status_t ;
	
/***************************************************/
/** FUNCTION TO INITIALIZE A PIN                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : enu_led_error_status_t              **/
/***************************************************/
enu_led_error_status_t LED_init(uint8_t u8_a_ledport , uint8_t u8_a_ledpin);


/***************************************************/
/** FUNCTION TO SET A LED AS ON                   **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : enu_led_error_status_t              **/
/***************************************************/
enu_led_error_status_t LED_on(uint8_t u8_a_ledport , uint8_t u8_a_ledpin);

/***************************************************/
/** FUNCTION TO SET A LED AS OFF                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : enu_led_error_status_t              **/
/***************************************************/
enu_led_error_status_t LED_off(uint8_t u8_a_ledport , uint8_t u8_a_ledpin);

/** PATTERNS TO BE DISPLAYED */
void LED_pattern1(void);
void LED_pattern2(void);
void LED_pattern3(void);
void LED_pattern4(void);
void LED_pattern5(void);
void LED_pattern6(void);
void LED_pattern7(void);
void LED_pattern8(void);


#endif