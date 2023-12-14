#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

typedef struct
{
	uint8 Conection_PORT;
	uint8 Blue_PIN;
	uint8 Pink_PIN;
	uint8 Yellow_PIN;
	uint8 Orange_PIN;

}STP_Config_t;

typedef enum
{
	STP_CW,STP_CCW
}STP_Direction;

uint8 STP_u8Rotate(const STP_Config_t* STP_obj, STP_Direction STP_DIR,uint16 Copy_u16Angle);




#endif


