#ifndef AUTKO_CONFIG_H
#define AUTKO_CONFIG_H

/*
* functionality configuration
*/

#define RECEIVE_NEC true
#define RECEIVE_PULSE_DISTANCE true
#define RECEIVE_SERIAL true

/*
 * constants
 */

#define MAX_TIME_BETWEEN_SIGNALS 150

/*
* pin values
* pins 9, 10 or 11, 12 could experience problems with I2C
*/

#define IR_RECEIVE_PIN 2
#define BEEPER 13

#define RIGHT_WHEEL_FORWARD_PIN 3   // green
#define RIGHT_WHEEL_BACKWARD_PIN 4  // blue
#define RIGHT_WHEEL_SPEED_PIN 6     // yellow
#define LEFT_WHEEL_FORWARD_PIN 7    // grey
#define LEFT_WHEEL_BACKWARD_PIN 8   // pink
#define LEFT_WHEEL_SPEED_PIN 5     // white

/*
* remote buttons
*/

#define IR_REMOTE_1 69
#define IR_REMOTE_2 70
#define IR_REMOTE_3 71
#define IR_REMOTE_UP 24
#define IR_REMOTE_DOWN 82
#define IR_REMOTE_RIGHT 90
#define IR_REMOTE_LEFT 8
#define IR_REMOTE_OK 28

#define PD_REMOTE_1 3125149440
#define PD_REMOTE_2 3108437760
#define PD_REMOTE_3 3091726080
#define PD_REMOTE_UP 3877175040
#define PD_REMOTE_DOWN 2907897600
#define PD_REMOTE_RIGHT 2774204160
#define PD_REMOTE_LEFT 4144561920
#define PD_REMOTE_OK 3810328320

#endif