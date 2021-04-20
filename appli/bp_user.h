#ifndef BP_USER_H
#define BP_USER_H

#define LONG_PRESS_DURATION	1000 //1s

typedef enum {none, rising, falling, both} front_e;

typedef enum
{
	BUTTON_EVENT_NONE,
	BUTTON_EVENT_SHORT_PRESS,
	BUTTON_EVENT_LONG_PRESS
}button_event_e;  

volatile uint8_t flag_10ms[10];

int detection_bp_front(front_e front, uint8_t filtre);
button_event_e BUTTON_state_machine(void);
void process_ms(void);

#endif
