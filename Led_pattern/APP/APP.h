/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Application layer of led pattern     */
/**************************************************/


#ifndef APP_H_
#define APP_H_

/** MACROS FOR LED PATTERNS **/
#define PATTERN_1    1
#define PATTERN_2    2
#define PATTERN_3    3
#define PATTERN_4    4
#define PATTERN_5    5
#define PATTERN_6    6
#define PATTERN_7    7
#define PATTERN_8    8

/** TYPE DEFINITION FOR APP LAYER ERROR STATUS **/
typedef enum { APP_SUCCEED = 0 , APP_FAILURE } enu_app_error_status_t ;


/** LEDs INITIALIZATION FUNCTION **/
enu_app_error_status_t LEDs_init(void);


/** BUTTONS INITIALIZATION FUNCTION **/
enu_app_error_status_t BTNs_init(void);


/** FUNCTION TO SET ALL LEDs OFF **/
enu_app_error_status_t LEDs_off(void);


/** INITIALIZATION FUNCTION **/
enu_app_error_status_t APP_init(void);


/** MAIN LOGIC **/
void APP_start(void);




#endif /* APP_H_ */