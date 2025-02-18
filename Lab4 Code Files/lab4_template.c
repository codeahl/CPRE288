/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1


void sendStringToPutty(char* data) {
    int size = strlen(data);
    int i;
    for (i = 0; i < size; i++) {
        cyBot_sendByte(data[i]);
    }
}


int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
    cyBot_uart_init();
	            // Don't forget to initialize the cyBot UART before trying to use it

	// YOUR CODE HERE
    sendStringToPutty("Start!\n\r");
	int last_pressed = 0;
	while(1)
	{

      switch(button_getButton()) {
      case 1:
          if(last_pressed != 1) {
          lcd_printf("Button 1 pressed!");
          sendStringToPutty("Button 1 pressed!\n\r");
          last_pressed = 1;
          }
          break;
      case 2:
          if(last_pressed != 2) {
          lcd_printf("Button 2 pressed!");
          sendStringToPutty("Button 2 pressed!\n\r");
          last_pressed = 2;
          }
          break;
      case 3:
          if(last_pressed != 3) {
          lcd_printf("Button 3 pressed!");
          sendStringToPutty("Button 3 pressed!\n\r");
          last_pressed = 3;
          }
          break;
      case 4:
          if(last_pressed != 4) {
          lcd_printf("Button 4 pressed!");
          sendStringToPutty("Button 4 pressed!\n\r");
          last_pressed = 4;
          }
          break;
      default:
          last_pressed = 0;
      }

	}

}
