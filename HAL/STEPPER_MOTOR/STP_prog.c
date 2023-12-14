#include "STD_TYPES.h"
#include "ErrType.h"
#include <util/delay.h>
#include "DIO_interface.h"

#include "STP_interface.h"



uint8 STP_u8Rotate(const STP_Config_t* STP_obj, STP_Direction STP_DIR,uint16 Copy_u16Angle)
{
	uint8 Local_u8ErrorState=OK;
	uint16 Local_u16FS;   /*number of full steps*/
	uint16 Local_u16FullRevolut, Local_u16RestAngle, Local_u8FullRevolutionCounter, Local_u8StepCounter;

	/*Number of full steps for full revolution*/
	Local_u16FullRevolut=512*(Copy_u16Angle/360);

	/*Number of full steps for Less than 360 deg revolution*/
	Local_u16RestAngle=Copy_u16Angle%360;;
	Local_u16FS=(uint16)(((uint32)Local_u16RestAngle*2048UL)/360UL);

	for(Local_u8FullRevolutionCounter=0;Local_u8FullRevolutionCounter<Local_u16FullRevolut;Local_u8FullRevolutionCounter++)
	{
		if(STP_DIR==STP_CCW)
		{
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_LOW);

			_delay_ms(5);

		}
		else if(STP_DIR==STP_CW)
		{
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_LOW);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

			_delay_ms(5);

		}

	}
	for(Local_u8StepCounter=0;Local_u8StepCounter<Local_u16FS;Local_u8StepCounter++)
	{
		if(STP_DIR==STP_CCW)
		{
			if(Local_u8StepCounter%4==0)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);
			}

			else if(Local_u8StepCounter%4==1)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);
			}

			else if(Local_u8StepCounter%4==2)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);
			}

			else if(Local_u8StepCounter%4==3)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_LOW);

				_delay_ms(5);
			}


		}
		else if(STP_DIR==STP_CW)
		{
			if(Local_u8StepCounter%4==0)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_LOW);

				_delay_ms(5);

			}

			else if(Local_u8StepCounter%4==1)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);
			}

			else if(Local_u8StepCounter%4==2)
			{

				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);
			}

			else if(Local_u8StepCounter%4==3)
			{
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Blue_PIN, DIO_u8PIN_LOW);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Pink_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Yellow_PIN, DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(STP_obj->Conection_PORT, STP_obj->Orange_PIN, DIO_u8PIN_HIGH);

				_delay_ms(5);

			}



		}
	}

	return Local_u8ErrorState;
}
