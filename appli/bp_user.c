#include "stm32f4xx.h"
#include "bp_user.h"
#include "gpio.h"

static volatile uint32_t t = 0;

int detection_bp_front(front_e front, uint8_t filtre)
{
    int res = 0;
    uint8_t val = 0;
    static int val_pre =0;
    volatile int i;
    
    int errorInA1 = digitalRead(GPIOA, 0, &val);
    if(errorInA1 != 0) error(errorInA1);
    
    switch (front)
    {
      case none :
      	  res = val;
          break;
      case rising :
      	  if((val_pre != val)&&(val)) res=1;
      	  else res=0;
          break;
      case falling :
          if((val_pre != val)&&(!val)) res=1;
      	  else res=0;
          break;
      case both :
          if(val_pre != val) res=1;
          else res = 0;
          break; 
    } 
   
    if(filtre && (val_pre != val)) for(i = 0; i<1000000; i++);
    val_pre = val;
    return res;
}

button_event_e BUTTON_state_machine(void){
    typedef enum
    {
        INIT = 0,
        WAIT_BUTTON,
        BUTTON_PRESSED,
        WAIT_RELEASE
    }state_e;

    static state_e state = INIT;

    button_event_e ret = BUTTON_EVENT_NONE;
    uint8_t current_button;

    if(flag_10ms[0]){
        flag_10ms[0] = 0;
        digitalRead(GPIOA, 0, &current_button);
        switch (state)
        {
            case INIT:
                state = WAIT_BUTTON;
                break;

            case WAIT_BUTTON:
				if(current_button)
				{
					t=LONG_PRESS_DURATION;	//Action réalisée sur la transition.
					state = BUTTON_PRESSED;	//Changement d'état conditionné à "if(current_button)"
				}
				break;
                
			case BUTTON_PRESSED:
				if(t==0)
				{
					ret = BUTTON_EVENT_LONG_PRESS;
					state = WAIT_RELEASE;		//le temps est écoulé, c'était un appui long !
				}
				else if(!current_button)
				{
					ret = BUTTON_EVENT_SHORT_PRESS;
					state = WAIT_BUTTON;	//le bouton a été relâché avant l'écoulement du temps, c'était un appui court !
				}
				break;

			case WAIT_RELEASE:
				if(!current_button)
				{
					state = WAIT_BUTTON;
				}
				break;

            default:
                break;
        }
    }
    return ret;
}

void TIM2_IRQHandler(void)
{
	static uint32_t t10ms = 0;
    if (TIM2->SR & TIM_SR_UIF){
        t10ms = (t10ms + 1)%10;		//incrémentation de la variable t10ms (modulo 10 !)
        if(!t10ms){
            flag_10ms[0] = 1; //toutes les 10ms, on lève ce flag.
            flag_10ms[1] = 1; //toutes les 10ms, on lève ce flag.
        }
            
        if(t)
            t--;
    }
    TIM2->SR = 0x0;
}

