#include <Lab3 Code Files/movement.h>
#include <Lab3 Code Files/open_interface.h>
#include <Lab3 Code Files/lcd.h>

double move_forward(oi_t *sensor_data, double distance_mm) {
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500,500); //move forward at full speed


    //Values to move after collision detection
    int backwardDist = 150;
    int lateralDist = 250;
    int angle = 90;
    int correction_forward_dist = 250;



    while (sum < distance_mm) {

    oi_update(sensor_data);
    sum += sensor_data -> distance; // use -> notation since pointer


    //Obstacle detect logic
    if(sensor_data -> bumpLeft) {
        lcd_printf("Moved %lf mm", sum);
        move_backwards(sensor_data, backwardDist);
        turn_right(sensor_data, angle);
        move_forward(sensor_data, lateralDist);
        turn_left(sensor_data, angle);

        //testing stuff below
        move_forward(sensor_data, correction_forward_dist);
        turn_left(sensor_data, angle);
        move_forward(sensor_data, lateralDist);
        turn_right(sensor_data, angle);
        sum += correction_forward_dist;

        sum -= backwardDist;
        oi_setWheels(500,500);
    }
    else if(sensor_data -> bumpRight) {
        lcd_printf("Moved %lf mm", sum);
        move_backwards(sensor_data, backwardDist);
        turn_left(sensor_data, angle);
        move_forward(sensor_data, lateralDist);
        turn_right(sensor_data, angle);
        //testing stuff below
        move_forward(sensor_data, correction_forward_dist);
        turn_right(sensor_data, angle);
        move_forward(sensor_data, lateralDist);
        turn_left(sensor_data, angle);
        sum += correction_forward_dist;

        sum -= backwardDist;
        oi_setWheels(500,500);
    }


    }

    lcd_printf("Moved %lf mm", sum);


    oi_setWheels(0,0); //stops wheels


    return sum;

}

double move_backwards(oi_t *sensor_data, double distance_mm) {
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-200,-200); //move forward at full speed

    distance_mm *= -1;

    while (sum > distance_mm) {
    oi_update(sensor_data);
    sum += sensor_data -> distance; // use -> notation since pointer
    }

    lcd_printf("Moved %lf mm", sum);


    oi_setWheels(0,0); //stops wheels


    return sum;

}



double turn_left(oi_t *sensor_data, double degrees) {
    double sum = 0; // distance member in oi_t struct is type double
       oi_setWheels(100,-100); //move forward at full speed


       int errorCorrection = -2;



       while (sum < degrees - errorCorrection) {
       oi_update(sensor_data);
       sum += sensor_data -> angle; // use -> notation since pointer
       }

       lcd_printf("Turned Left %0.2lf degrees", sum);

       oi_setWheels(0,0); //stops wheels


       return sum;
}

double turn_right(oi_t *sensor_data, double degrees) {
    double sum = 0; // distance member in oi_t struct is type double
           oi_setWheels(-100,100); //move forward at full speed

           int errorCorrection = 1;

           degrees *= -1;

           while (sum > degrees + errorCorrection) {
           oi_update(sensor_data);
           sum += sensor_data -> angle; // use -> notation since pointer
           }

           lcd_printf("Turned Right %0.2lf degrees", -1*sum);

           oi_setWheels(0,0); //stops wheels


           return sum;
}

