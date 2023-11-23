#include "STD_TYPES.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LED_interface.h"

uint8 LED_u8SetON(const LED_Cnfig_t* LED_Obj)
{
	uint8 Local_u8ErrorState = OK;

	if(LED_Obj!=NULL)
	{
		if(LED_Obj->LED_Ative_t==ACTIVE_LOW)
		{
			DIO_u8SetPinValue(LED_Obj->LED_PORT,LED_Obj->LED_PIN,DIO_u8PIN_LOW);
		}
		else if(LED_Obj->LED_Ative_t==ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(LED_Obj->LED_PORT,LED_Obj->LED_PIN,DIO_u8PIN_HIGH);

		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 LED_u8SetOFF(const LED_Cnfig_t* LED_Obj)
{
	uint8 Local_u8ErrorState = OK;

	if(LED_Obj!=NULL)
	{
		if(LED_Obj->LED_Ative_t==ACTIVE_LOW)
		{
			DIO_u8SetPinValue(LED_Obj->LED_PORT,LED_Obj->LED_PIN,DIO_u8PIN_HIGH);
		}
		else if(LED_Obj->LED_Ative_t==ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(LED_Obj->LED_PORT,LED_Obj->LED_PIN,DIO_u8PIN_LOW);

		}


	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 LED_u8Toggle(const LED_Cnfig_t* LED_Obj)
{
	uint8 Local_u8ErrorState = OK;

	if(LED_Obj!=NULL)
	{
		DIO_u8TogglePinValue(LED_Obj->LED_PORT,LED_Obj->LED_PIN);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
