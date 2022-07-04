#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

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

void app_main(void)
{
    //printf("\n");
    //printf("Timer: %lld microsseconds\n", esp_timer_get_time());
    while(1){
        PID(9);
    }   
    
}


