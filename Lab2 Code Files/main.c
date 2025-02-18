/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include <Lab2 Code Files/lcd.h>
#include <Lab2 Code Files/open_interface.h>
#include <Lab2 Code Files/movement.h>
#include <Lab2 Code Files/Timer.h>
#include <string.h>
#include "Timer.h"
#include "lcd.h"



int main (void) {

    //Need at start of program for all labs
    oi_t *sensor_data = oi_alloc(); //Allocate and clear all memory for OI Struct

    oi_init(sensor_data);
    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
    //                // and enables time functions (e.g. timer_waitMillis)
    //
    lcd_init();   // Initialize the LCD screen.  This also clears the screen.



    /* Initialize open interface communication with IRobot.
     *
     * This function needs to be called to setup UART and other
     * OI peripherals
     */



    //Start Program
    //Move forward
    //for testing:
    double distance_moved = move_forward(sensor_data, 2000);


//    double angle_turned = turn_left(sensor_data, 90);

//    double angle_turned = turn_right(sensor_data, 90);


        //square
//        move_forward(sensor_data, 500);
//        turn_right(sensor_data, 90);
//        move_forward(sensor_data, 500);
//        turn_right(sensor_data, 90);
//        move_forward(sensor_data, 500);
//        turn_right(sensor_data, 90);
//        move_forward(sensor_data, 500);
//        turn_right(sensor_data, 90);


    //move back test
//    move_backwards(sensor_data, 500);






    //Need at end of program for all labs
//    oi_setWheels(0,0); //stops wheels

    /*
     * Free memory from pointer to Open Interface Struct
     * Required for CyBot to charge
    */
    oi_free(sensor_data);

	return 0;
}
