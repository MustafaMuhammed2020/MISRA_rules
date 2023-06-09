/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                              **/
/* Date    : 5 , April 2023                                      **/
/* Version : V01                                                 **/
/* Hint    : APIs of application layer                           **/
/******************************************************************/
 
#ifndef APP_H_
#define APP_H_

#define MAX_LED_MODES         8
#define INITIAL_VALUE         0
#define MAX_BLINK_MODE        5

#define BLINK_MODE_1          0
#define BLINK_MODE_2          1
#define BLINK_MODE_3          2
#define BLINK_MODE_4          3
#define BLINK_MODE_5          4

#define LED_MODE_1            0
#define LED_MODE_2            1
#define LED_MODE_3            2
#define LED_MODE_4            3
#define LED_MODE_5            4
#define LED_MODE_6            5
#define LED_MODE_7            6
#define LED_MODE_8            7


/** TYPE DEFINITION FOR APPLICATION LAYER ERROR STATUS  **/
typedef enum { APP_SUCCEED = 0  , APP_FAILURE } enu_app_error_status_t ;

/******************************************************/
/** FUNCTION TO INITIALIZE MODULES                   **/
/** ARGUMENTS  : VOID                                **/
/** RETURNS    : enu_app_error_status_t              **/
/******************************************************/
enu_app_error_status_t APP_init(void);

/******************************************************/
/** APPLICATION MAIN LOGIC                           **/
/** ARGUMENTS  : VOID                                **/
/** RETURNS    : VOID                                **/
/******************************************************/
void APP_start(void);

#endif /* INCFILE1_H_ */