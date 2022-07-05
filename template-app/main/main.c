#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/gpio.h"

#define temp 4
#define fan 5

long long int Ctime, Ptime, Etime = 0;

float Kp = 0.1;
float Ki = 0.1;
float Kd = 0.1;

float setPoint = 10;
float output = 0;

double Cerror, Lerror, intError, derError = 0;

double PID (float input){
    
    Ctime = esp_timer_get_time();
    Etime = Ctime - Ptime;

    Cerror = setPoint - input;
    intError += Cerror * Etime;
    derError = (Cerror - Lerror)/Etime;

    output = Kp * Cerror + Ki * intError + Kd * derError;

    Lerror = Cerror;
    Ptime = Ctime;

    printf("SP: %f, Input: %f | Error: %lf | Ki, Kp, Kd: %f, %f, %f | Output: %f | Elapsed time: %lld\n", setPoint, input, Cerror, Ki, Kp, Kd, output, Etime);
    return output;
}

void app_main(void){

    gpio_reset_pin(fan);
    //gpio_set_direction(temp, GPIO_MODE_INPUT);
    gpio_set_direction(fan, GPIO_MODE_INPUT);

    while(1){
        gpio_set_level(fan, 1);
    }   
    
}