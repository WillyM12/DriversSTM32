#include "stm32f4xx.h"
#include "chenillard.h"
#include "gpio.h"
#include "bp_user.h"

static volatile int ledOn = 14;
static volatile int cpt = 0;

int chenillard(uint8_t sens, alarme_e alarme)
{
    int time; 

    if(flag_10ms[1]){
        cpt++;
        flag_10ms[1] = 0;
    } 
    
    switch (alarme)
    {
        case TIME250:
            time = 25;
            break;
        
        case TIME500:
            time = 50;
            break;
        
        case TIME1000:
            time = 100;
            break;

        case TIME2000:
            time = 200;
            break;

        default:
            return CHENILL_ERROR;
            break;
    }
    
    if(cpt == time){
        digitalWrite(GPIOD, ledOn, OFF);
        if(sens == 1){
            ledOn++;
            if(ledOn == 16) ledOn = 12;       
        }
        else{
            ledOn--;
            if(ledOn == 11) ledOn = 15;   
        }
        digitalWrite(GPIOD, ledOn, ON);
    }
    if(cpt >= time) cpt=0;
    return 0;
}
