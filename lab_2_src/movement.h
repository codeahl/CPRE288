/*
 * lcd.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nbergman
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//#define IS_STEPPER_BOARD
//#define IS_STEPPER_BOARD

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <Lab2 Code Files/Timer.h>
#include <Lab2 Code Files/open_interface.h>


double move_forward(oi_t *sensor_data, double distance_mm);

double move_backwards(oi_t *sensor_data, double distance_mm);

double turn_left(oi_t *sensor_data, double degrees);

double turn_right(oi_t *sensor_data, double degrees);

double move_forward_obstacle(oi_t *sensor_data, double distance_mm);








/// Extra function for the stepper motor board
uint8_t lcd_reverseNibble(uint8_t x);

/// Initialize PORTB0:6 to Communicate with LCD
void lcd_init(void);

///Send Char to LCD
void lcd_putc(char data);

///Send Character array to LCD
void lcd_puts(char data[]);

///Clear LCD Screen
void inline lcd_clear(void);

///Return Cursor to 0,0
void inline lcd_home(void);

///Goto Line on LCD - 0 Indexed
void lcd_gotoLine(uint8_t lineNum);

///Set cursor position - top left is 0,0
void lcd_setCursorPos(uint8_t x, uint8_t y);

void lcd_printf(const char *format, ...);

///Send command to LCD - Position, Clear, Etc.
void lcd_sendCommand(uint8_t data);

///Send 4bit nibble to lcd, then clear port
void lcd_sendNibble(uint8_t theNibble);


#endif /* LCD_H_ */
