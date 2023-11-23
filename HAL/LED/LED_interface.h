#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef struct 
{
	uint8 LED_PORT;
	uint8 LED_PIN;
	uint8 LED_Ative_t;
	
}LED_Cnfig_t;


#define ACTIVE_LOW              0
#define ACTIVE_HIGH				1

uint8 LED_u8SetON(const LED_Cnfig_t* LED_Obj);

uint8 LED_u8SetOFF(const LED_Cnfig_t* LED_Obj);

uint8 LED_u8Toggle(const LED_Cnfig_t* LED_Obj);





#endif