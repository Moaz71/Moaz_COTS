#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "SSD_interface.h"



uint8 SSD_u8ON(const SSD_Cnfig_t* SSD_Obj)
{
	uint8 Local_u8ErrorState = OK;
	if(SSD_Obj!=NULL)
	{
		if((SSD_Obj->SSD_TYPE)==COM_CATHODE)
		{
			DIO_u8SetPinValue(SSD_Obj->SSD_ENABLE_PORT,SSD_Obj->SSD_ENABLE_PIN,DIO_u8PIN_LOW);

		}
		else if((SSD_Obj->SSD_TYPE==COM_ANODE)||(SSD_Obj->SSD_TYPE==ETA_KIT))
		{

			DIO_u8SetPinValue(SSD_Obj->SSD_ENABLE_PORT,SSD_Obj->SSD_ENABLE_PIN,DIO_u8PIN_HIGH);

		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 SSD_u8OFF(const SSD_Cnfig_t* SSD_Obj)
{
	uint8 Local_u8ErrorState = OK;
	if(SSD_Obj!=NULL)
	{
		if((SSD_Obj->SSD_TYPE)==COM_CATHODE)
		{
			DIO_u8SetPinValue(SSD_Obj->SSD_ENABLE_PORT,SSD_Obj->SSD_ENABLE_PIN,DIO_u8PIN_HIGH);

		}
		else if((SSD_Obj->SSD_TYPE==COM_ANODE)||(SSD_Obj->SSD_TYPE==ETA_KIT))
		{

			DIO_u8SetPinValue(SSD_Obj->SSD_ENABLE_PORT,SSD_Obj->SSD_ENABLE_PIN,DIO_u8PIN_LOW);

		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 SSD_u8SetNumber(const SSD_Cnfig_t* SSD_Obj,uint8 Copy_u8Number)
{

	/*make array static for reserve space in .data .bss section instade of stack*/
	static uint8 Local_u8SegDisplay[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x7,0x7F,0x6F};
	uint8 Local_u8ErrorState = OK, Local_u8Iteraror;
	if(SSD_Obj!=NULL)
	{
		if((SSD_Obj->SSD_TYPE==COM_CATHODE)||(SSD_Obj->SSD_TYPE==ETA_KIT))
		{
			if(SSD_Obj->SSD_LEDA_PIN==DIO_u8PIN0)
			{
				for(Local_u8Iteraror=0;Local_u8Iteraror<7;Local_u8Iteraror++)
				{
					DIO_u8SetPinValue(SSD_Obj->SSD_LED_PORT,Local_u8Iteraror,GET_BIT(Local_u8SegDisplay[Copy_u8Number],Local_u8Iteraror));

				}
			}
			else if(SSD_Obj->SSD_LEDA_PIN==DIO_u8PIN1)
			{
				for(Local_u8Iteraror=1;Local_u8Iteraror<8;Local_u8Iteraror++)
				{
					DIO_u8SetPinValue(SSD_Obj->SSD_LED_PORT,Local_u8Iteraror,GET_BIT(Local_u8SegDisplay[Copy_u8Number],(Local_u8Iteraror-1)));

				}


			}
		}
		else if((SSD_Obj->SSD_TYPE)==COM_ANODE)
		{
			if(SSD_Obj->SSD_LEDA_PIN==DIO_u8PIN0)
			{
				for(Local_u8Iteraror=0;Local_u8Iteraror<7;Local_u8Iteraror++)
				{
					DIO_u8SetPinValue(SSD_Obj->SSD_LED_PORT,Local_u8Iteraror,~GET_BIT(Local_u8SegDisplay[Copy_u8Number],Local_u8Iteraror));

				}
			}
			else if(SSD_Obj->SSD_LEDA_PIN==DIO_u8PIN1)
			{
				for(Local_u8Iteraror=1;Local_u8Iteraror<8;Local_u8Iteraror++)
				{
					DIO_u8SetPinValue(SSD_Obj->SSD_LED_PORT,Local_u8Iteraror,~GET_BIT(Local_u8SegDisplay[Copy_u8Number],(Local_u8Iteraror-1)));

				}


			}
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
