#include "stm32f4xx.h"
#include "chenillard.h"
#include "gpio.h"


int chenillard(uint8_t sens, alarme_e alarme)
{
    int time = 0; 
    static int led = 14;
    static int cpt10ms = 0;

    if(TIM2->SR & TIM_SR_UIF) cpt10ms++;
    TIM2->SR = 0x0;
    
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
    
    if(cpt10ms == time){
        if(sens){
            led ++;
            if(led == 15) led = 12;
             digitalToggle(GPIOD, led);
             digitalToggle(GPIOD, led-1);
        }
        else{
            led--;
            if(led == 11) led = 14;
            digitalToggle(GPIOD, led);
            digitalToggle(GPIOD, led+1);
        }
        cpt10ms = 0;
    }
    return 0;
}
