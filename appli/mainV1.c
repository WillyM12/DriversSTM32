#include "stm32f4xx.h"
#include "chenillard.h"
#include "bp_user.h"
 
int main(void)
{
    int sens = 0;
    volatile int i;
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
     
    //Config LEDs 
    GPIOD->MODER |= (1 << 24) | (1<<26) | (1<<28) | (1<<30); 
    //Config BP -> A0 input with pull-up
    GPIOA->MODER &= ~(0x1);
    GPIOA->PUPDR |= 2; 

    while(1)
    {
    	if(detection_bp(rising, 1)) 
    	{
    	    sens = !sens;
    	}
    	chenillard(sens);
    	for(i = 0; i<5000000; i++);
    }
}

    
    
