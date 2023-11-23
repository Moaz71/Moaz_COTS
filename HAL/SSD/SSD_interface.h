#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H


typedef struct
{
	uint8 SSD_TYPE;
	uint8 SSD_LED_PORT;
	uint8 SSD_LEDA_PIN;
	uint8 SSD_ENABLE_PORT;
	uint8 SSD_ENABLE_PIN;
}SSD_Cnfig_t;


#define COM_ANODE         0
#define COM_CATHODE       1
#define ETA_KIT   		  2



uint8 SSD_u8ON(const SSD_Cnfig_t* SSD_Obj);

uint8 SSD_u8OFF(const SSD_Cnfig_t* SSD_Obj);

uint8 SSD_u8SetNumber(const SSD_Cnfig_t* SSD_Obj,uint8 Copy_u8Number);





#endif
