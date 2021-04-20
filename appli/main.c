#include "stm32f4xx.h"
#include "chenillard.h"
#include "bp_user.h"
#include "gpio.h"

int main(void)
{
    alarme_e alarme = TIME250;
    uint8_t sens = 1;
    int codeError = 0;
    button_event_e button_event;
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable TIM2 clock

    NVIC->ISER[0] |= 1UL << (TIM2_IRQn); // enable the TIM2 IRQ
    
    // Clock TIM2 = 42MHz
    TIM2->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
    TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt
    TIM2->ARR = 41999; // autoreload = (time/(prescaler/clock))-1 here time = 1ms
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM2->EGR = 1; // trigger update event to reload timer registers
     
    //Config LEDs
    codeError = pinMode(GPIOD, 12, OUTPUT);
    if(codeError != 0) error(codeError);
    codeError = pinMode(GPIOD, 13, OUTPUT);
    if(codeError != 0) error(codeError);
    codeError = pinMode(GPIOD, 14, OUTPUT);
    if(codeError != 0) error(codeError);
    codeError = pinMode(GPIOD, 15, OUTPUT);
    if(codeError != 0) error(codeError);

    //Config BP -> A0 input with pull-down
    codeError= pinMode(GPIOA, 0, INPUT_PULLDOWN);
    if(codeError!= 0) error(codeError);
    
    while(1)
    {
	    button_event = BUTTON_state_machine();

        if(button_event == BUTTON_EVENT_SHORT_PRESS) sens = !sens;

        if(button_event == BUTTON_EVENT_LONG_PRESS){
            alarme++;
            if(alarme > TIME2000) alarme = TIME250;
        }

        codeError = chenillard(sens, alarme);
        if(codeError!= 0) error(codeError);
    }
}



    
    
