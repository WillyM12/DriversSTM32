#ifndef _GPIO_H_
#define _GPIO_H_

#define OFF 0
#define ON 1

#define _DISABLE 10
#define OUTPUT 11
#define INPUT 12
#define INPUT_PULLUP 13
#define INPUT_PULLDOWN 14

#define PORT_ERROR 20
#define PIN_ERROR 21
#define MODE_ERROR 22
#define VALUE_ERROR 23
#define CONFIG_ERROR 24
#define CHENILL_ERROR 25

int pinMode(GPIO_TypeDef *port, uint8_t numBit, uint8_t mode);
int digitalWrite(GPIO_TypeDef *port, uint8_t numBit, uint8_t value);
int digitalToggle(GPIO_TypeDef *port, uint8_t numBit);
int digitalRead(GPIO_TypeDef *port, uint8_t numBit, uint8_t *value);
void error(int codeError);

#endif