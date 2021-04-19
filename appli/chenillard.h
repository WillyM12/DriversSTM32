#ifndef CHENILLARD_H
#define CHENILLARD_H

#define MASK_LED1 (1 << 12)
#define MASK_LED2 (1 << 13)
#define MASK_LED3 (1 << 14)
#define MASK_LED4 (1 << 15)

typedef enum{
    TIME250,
    TIME500,
    TIME1000,
    TIME2000
}alarme_e;

int chenillard(uint8_t sens, alarme_e alarme);

#endif
