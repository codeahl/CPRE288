/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <Lab3 Code Files/lcd.h>
#include <Lab3 Code Files/open_interface.h>
#include <Lab3 Code Files/Timer.h>
#include <string.h>
#include "Timer.h"
#include "lcd.h"
#include "movement.h"

typedef struct{
    int radial_width;
    float obj_distance;
    int midpoint;
} scanned_object;


void sendStringToPutty(char* data) {
    int size = strlen(data);
    int i;
    for (i = 0; i < size; i++) {
        cyBot_sendByte(data[i]);
    }
}

int main (void) {


    //Need at start of program for all labs
    oi_t *sensor_data = oi_alloc();
    cyBOT_Scan_t scan_data;
    oi_init(sensor_data);
    timer_init();
    lcd_init();
//    double distance_moved = move_forward(sensor_data, 2000);
//    turn_right(sensor_data, 90);
    cyBot_uart_init();

   // Input: feature, int where each feature is associated with a bit as follows
   //  Bit 0: 1 enable servo
   //  Bit 1: 1 enable PING
   //  Bit 2: 1 enable IR
   //  Bit 3 - 31: reserved (0's)
   // Example: cyBOT_init_Scan(0b0111); // Enables servo, PING, but NOT IR
   cyBOT_init_Scan(0b0111);
   //change based on bot
   left_calibration_value = 1193500;
   right_calibration_value = 238000;

//       get calibration values
//       cyBOT_SERVRO_cal_t calibrated_struct = cyBOT_SERVO_cal();













//
//
////    cyBOT_Scan(90, &scan_data);
//
   int start_obj = 0;
   int end_obj = 0;
   bool scanning_obj = false;
   scanned_object obj_arr[6];
   float current_dist = 200;
   float prev_dist = 200;
   float prev_prev_dist = 200;
   int obj_index = 0;
   scanned_object min;
   float data_arr[92];


   sendStringToPutty("\rDegrees\tPing Distance(cm)\n\r");
    while(1) {
        char recieved_byte = cyBot_getByte();
        if(recieved_byte == 'm') {
            cyBOT_Scan(0, &scan_data);
            timer_waitMillis(1000);
            int i;
                    for (i = 0; i <= 180; i+= 2) {
                    cyBOT_Scan(i, &scan_data);
                    data_arr[i/2] = scan_data.sound_dist;


                    //print data
                    char buffer[30];
                    sprintf(buffer, "%d\t%0.2f------%0.2f\n\r", i,scan_data.sound_dist, data_arr[i/2]);
                    sendStringToPutty(buffer);


                    //set current and previous distances (i, i-1, i-2)
                    prev_prev_dist = prev_dist;
                    prev_dist = current_dist;
                    current_dist = scan_data.sound_dist;


                    if(!scanning_obj) {
                        if(current_dist < 100) {
                            start_obj = i;
                            char buffer3[30];
                            sprintf(buffer3,"START ANGLE %d\n\r", start_obj);
                            sendStringToPutty(buffer3);
                            scanning_obj = true;
                        }
                    }
                    else {
                        if(current_dist > 100 && prev_dist > 100 && prev_prev_dist > 100) {
                            end_obj = i - 6;
                            char buffer2[30];
                            sprintf(buffer2,"END ANGLE %d\n\r", end_obj);
                            sendStringToPutty(buffer2);
                            //no longer scanning an object
                            scanning_obj = false;
                            //initialize dist and width attributes of appropriate index
                            obj_arr[obj_index].obj_distance = data_arr[end_obj/2];
                            obj_arr[obj_index].radial_width = end_obj - start_obj;
                            obj_arr[obj_index].midpoint = (start_obj + end_obj) / 2;
                            //increment object_index


                            char obj_message[100];
                            sprintf(obj_message, "Object %d: width = %d, distance = %0.2f, midpoint = %d.\n\r", obj_index + 1, obj_arr[obj_index].radial_width, obj_arr[obj_index].obj_distance, obj_arr[obj_index].midpoint);
                            sendStringToPutty(obj_message);

                            obj_index++;
                        }
                    }


                    }


                    min = obj_arr[0];
                    for (i = 0; i < obj_index; i++) {
                        if(obj_arr[i].radial_width < min.radial_width) {
                            min = obj_arr[i];

                        }
                    }
                    char obj_message2[100];
                    sprintf(obj_message2, "obj_index: %d\n\r", obj_index);
                    sendStringToPutty(obj_message2);
                    if(obj_index != 0) {
                        int angle_adjustment = 20; //temporary until we clean data

                        if(min.midpoint >= 90) {
                            sprintf(obj_message2, "min_midpoint: %d\n\r", min.midpoint);
                            sendStringToPutty(obj_message2);
                            turn_left(sensor_data, min.midpoint - (90 + angle_adjustment));
                            sendStringToPutty("left");
                        }
                        else {
                            sprintf(obj_message2, "min_midpoint: %d\n\r", min.midpoint);
                            sendStringToPutty(obj_message2);
                            turn_right(sensor_data, 90 - angle_adjustment - min.midpoint);
                            sendStringToPutty("right");
                        }
                        move_forward(sensor_data, (min.obj_distance * 10) - 200);
                    }

            }
        else if (recieved_byte == 'q') {
            break;
        }
    }



















//   sendStringToPutty("\rDegrees\tPing Distance(cm)\n\r");
//    while(1) {
//        if(cyBot_getByte() == 'm') {
//                int i;
//                    for (i = 45; i <= 135; i+= 2) {
//                    cyBOT_Scan(i, &scan_data);
//                    char buffer[30];
//                    sprintf(buffer, "%d\t%0.2f\n\r", i,scan_data.sound_dist);
//                    sendStringToPutty(buffer);
//                    }
//            }
//    }


////    lcd_printf("%f", *scan_data -> sound_dist);
//
//
//
//
////    to test get on LCD screen
////    char sentChar = cyBot_getByte();
////    lcd_printf("%c", sentChar);
//
////    to test send string to putty:
//
//    //create buffer for sprintf
//        char buffer[15];
//
//        //wait for char input and display on lcd
//        char sent = cyBot_getByte();
//        lcd_printf("%c", sent);
//
//        //format buffer to use the sent char
//        sprintf(buffer, "Received an %c", sent);
//        printf("%s", buffer);
//
//        //send buffer string to putty
//        int size = strlen(buffer);
//        sendStringToPutty(buffer, size);

//


    oi_free(sensor_data);


    return 0;
}



