#include "stm32f4xx.h"
#include "gpio.h"

static int configPin(GPIO_TypeDef *port, uint8_t numBit);

int pinMode(GPIO_TypeDef *port, uint8_t numBit, uint8_t mode){
    if(port!=GPIOA && port!=GPIOB && port!=GPIOC && port!=GPIOD && port!=GPIOE) return PORT_ERROR;
    if(numBit<0 && numBit>15) return PIN_ERROR;

    switch (mode)
    {
    case _DISABLE:
        port->MODER |= (1<<(numBit*2));
        port->OTYPER |= (1<<numBit);
        break;

    case INPUT:
        port->MODER &= ~(1<<(numBit*2));
        port->PUPDR &= ~(1<<(numBit*2));
        port->PUPDR &= ~(1<<(numBit*2+1));
        break;

    case OUTPUT:
        port->MODER |= (1<<(numBit*2));
        port->OTYPER &= ~(1<<(numBit));
        break;

    case INPUT_PULLUP:
        port->MODER &= ~(1<<(numBit*2));
        port->PUPDR &= ~(1<<(numBit*2+1));
        port->PUPDR |= (1<<(numBit*2));
        break;

    case INPUT_PULLDOWN:
        port->MODER &= ~(1<<(numBit*2));
        port->PUPDR &= ~(1<<(numBit*2));
        port->PUPDR |= (1<<(numBit*2+1));
        break;
    
    default:
        return MODE_ERROR;
        break;
    }
    return 0;
}

int digitalWrite(GPIO_TypeDef *port, uint8_t numBit, uint8_t value){
    if(port!=GPIOA && port!=GPIOB && port!=GPIOC && port!=GPIOD && port!=GPIOE) return PORT_ERROR;
    if(numBit<0 && numBit>15) return PIN_ERROR;
    if(value!=ON && value!=OFF) return VALUE_ERROR;

    int config = configPin(port, numBit);
    if(config != OUTPUT) return CONFIG_ERROR;

    if(value == ON) port->BSRRL = (1<<numBit);
    else port->BSRRH = (1<<numBit);

    return 0;
}

int digitalToggle(GPIO_TypeDef *port, uint8_t numBit){
    if(port!=GPIOA && port!=GPIOB && port!=GPIOC && port!=GPIOD && port!=GPIOE) return PORT_ERROR;
    if(numBit<0 && numBit>15) return PIN_ERROR;
    if(configPin(port, numBit) != OUTPUT) return CONFIG_ERROR;

    if(port->ODR & (1<<numBit)) port->BSRRH = (1<<numBit);
    else port->BSRRL = (1<<numBit);

    return 0;
}

int digitalRead(GPIO_TypeDef *port, uint8_t numBit, uint8_t *value){
    if(port!=GPIOA && port!=GPIOB && port!=GPIOC && port!=GPIOD && port!=GPIOE) return PORT_ERROR;
    if(numBit<0 && numBit>15) return PIN_ERROR;

    int config = configPin(port, numBit);
    if(config != INPUT && config!= INPUT_PULLUP && config!=INPUT_PULLDOWN) return CONFIG_ERROR;

    *value = port->IDR & (1<<numBit);

    return 0;
}

void error(int codeError){
    switch (codeError)
    {
    case PORT_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;

    case PIN_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;

    case MODE_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;

    case VALUE_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;

    case CONFIG_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;

    case CHENILL_ERROR:
        while(1){
            digitalWrite(GPIOD, 15, ON);
        }
        break;
    
    default:
        break;
    }
}

static int configPin(GPIO_TypeDef *port, uint8_t numBit){
    if(port->MODER & (1<<(numBit*2))){
        if(port->OTYPER & (1<<numBit)) return _DISABLE;
        else return OUTPUT;
    }
    else{
        if(port->PUPDR & (1<<(numBit*2))) return INPUT_PULLUP;
        else if(port->PUPDR & (1<<(numBit*2+1))) return INPUT_PULLDOWN;
        else return INPUT;
    }
}