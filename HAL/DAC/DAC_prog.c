#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DAC_interface.h"
#include "DAC_cfg.h"
#include "DAC_prv.h"





void DAC_voidSetAnalogVolt(uint16 Copy_u16mVolt)
{
	uint8 Local_u8Digital=0;

	/*Analog=Digital * step
	 * step 2^res   8bit
	 * */

	Local_u8Digital=(uint8)(((uint32)Copy_u16mVolt*255ul)/5000ul);

	DIO_u8SetPortValue(DIGITAL_PORT, Local_u8Digital);
}
