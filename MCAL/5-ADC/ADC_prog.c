#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"


#include "ADC_cfg.h"
#include "ADC_prv.h"
#include "ADC_reg.h"
#include "ADC_interface.h"

static uint16* ADC_pu16Result = NULL;

static void (*ADC_CallBackNotificationFunc)(void) = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

static ADC_Chain_t* ADC_pChainData = NULL;

static uint8 ADC_u8ISRSource;

void ADC_voidInit(void)
{

#if ADC_u8REFVOLT == AREF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_u8REFVOLT == AVCC
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_u8REFVOLT == INTERNAL2_56V
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);

#else
#error "Wrong reference volt configuration option "

#endif

	/***************SET ADC resolution***************/
#if ADC_u8RESOLUTION == EIGHT_BIT
	SET_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_u8RESOLUTION == TEN_BIT
	CLR_BIT(ADMUX, ADMUX_ADLAR);

#else
#error "Wrong resolution configuration option "

#endif

	/*Configure the prescaler division factor*/

	/*clear the prescaler bit*/
	ADCSRA&=PRESCALER_BIT_MASK;
	/*Set prescaler value*/
	ADCSRA|=ADC_u8PRESCALER_DIV_FACTOR << PRESCALER_BIT_POS;

	/*Disable auto trigger mode*/
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

	/*Disable Interrupt */
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}

uint8 ADC_u8StartSingleConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pu16Result != NULL)
	{
		/*Check if ADC is IDLE this will make ADC FUNC Reentrant*/
		if(ADC_u8BusyFlag == IDLE)
		{
			uint32 Local_u32Counter =0;

			/*ADC is now BUSY*/
			ADC_u8BusyFlag = BUSY;

			/*Set channel*/
			ADMUX &= CHANNEL_BIT_MASK;
			ADMUX |=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*wait until conversion time ended "polling whit blocking" as well as time out is not passed*/
			while((GET_BIT(ADCSRA, ADCSRA_ADIF))==0 && (Local_u32Counter<ADC_u32TIMEOUT))
			{
				Local_u32Counter++;
			}

			if(Local_u32Counter==ADC_u32TIMEOUT)
			{
				/*Time out has passed whit out the flag being raised*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Flag is raised before Timeout*/
				/*Clear flag Bit By SET it*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				/*Get the conversion result*/
#if ADC_u8RESOLUTION == EIGHT_BIT
				*Copy_pu16Result = ADCH;

#elif ADC_u8RESOLUTION == TEN_BIT
				*Copy_pu16Result = ADC;

#endif
			}

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;

		}
		else
		{
			/*ADC is busy, update Error state*/
			Local_u8ErrorState = BUSY_ERR;
		}


	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}


	return Local_u8ErrorState;

}

uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result, void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{

		/*Check if ADC is IDLE this will make ADC FUNC Reentrant 'protection'*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is busy now*/
			ADC_u8BusyFlag = BUSY;
			/*Convert the local ADC result into Global*/
			ADC_pu16Result=Copy_pu16Result;

			/*convert the local ADC call back into global*/
			ADC_CallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Set channel*/
			ADMUX &= CHANNEL_BIT_MASK;
			ADMUX |=Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC Conversion complete Interrupt  */
			SET_BIT(ADCSRA, ADCSRA_ADIE);

			/*ISR source is single conversion Asynch*/
			ADC_u8ISRSource = SINGLE_ASYNCH;
		}
		else
		{
			/*ADC is busy, update Error state*/
			Local_u8ErrorState = BUSY_ERR;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 ADC_u8StartChainConversionAsynch(const ADC_Chain_t* Copy_Object)
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_Object!=NULL)&&(Copy_Object->ChannelArr !=NULL)&&(Copy_Object->ResultArr !=NULL)&&(Copy_Object->NotificationFunc !=NULL))
	{
		/*Check if ADC is IDLE this will make ADC FUNC Reentrant 'protection'*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8BusyFlag = BUSY;

			/*Define the input chain data globally*/
			ADC_pChainData = Copy_Object;

			/*Set channel*/
			ADMUX &= CHANNEL_BIT_MASK;
			ADMUX |=ADC_pChainData->ChannelArr[0];

			/*Start Conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC Conversion complete Interrupt  */
			SET_BIT(ADCSRA, ADCSRA_ADIE);


			/*ISR source is chain conversion Asynch*/
			ADC_u8ISRSource = CHAIN_ASYNCH;


		}
		else
		{
			Local_u8ErrorState = TIMEOUT_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

static void voidHandleSingleConvAsynch(void)
{
	/*ISR come to complete the work of Start Single conversion Asynch function */

	/*Read the result*/
#if ADC_u8RESOLUTION == EIGHT_BIT
	*ADC_pu16Result = ADCH;

#elif ADC_u8RESOLUTION == TEN_BIT
	*ADC_pu16Result = ADC;

#endif

	/*Disable conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*ADC is now IDLE*/
	ADC_u8BusyFlag = IDLE;

	/*Invoke the call back notification function*/
	if(ADC_CallBackNotificationFunc != NULL)
	{
		ADC_CallBackNotificationFunc();
	}
	else
	{
		/*Do nothing*/
	}


}


/*make this function to improve code quality inside ISR not exceed i.e: 50 line inside ISR*/
static void voidHandleChainConvAsynch(void)
{
	/*ISR come to complete the work of Start chain conversion Asynch function */
	volatile static uint8 Local_u8ChannelIndex=0;

	/*read result complete the chain */
#if ADC_u8RESOLUTION == EIGHT_BIT
	ADC_pChainData->ResultArr[Local_u8ChannelIndex] = ADCH;

#elif ADC_u8RESOLUTION == TEN_BIT
	ADC_pChainData->ResultArr[Local_u8ChannelIndex] = ADC;

#endif

	/* Increment the channel counter*/
	Local_u8ChannelIndex++;

	if(Local_u8ChannelIndex == ADC_pChainData->ChainSize)
	{
		/*chain is completed*/

		/*Reset the channel index to be prepared for next chain*/
		Local_u8ChannelIndex = 0;

		/*Disable conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the call back notification function*/
		if(ADC_pChainData->NotificationFunc != NULL)
		{
			ADC_pChainData->NotificationFunc();
		}
		else
		{
			/*Do nothing*/
		}

	}
	else
	{
		/*chain not finish yet start the next conversion*/

		/*Set the input channel*/
		ADMUX &= CHANNEL_BIT_MASK;
		ADMUX |=ADC_pChainData->ChannelArr[Local_u8ChannelIndex];

		/*Start Conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);


	}


}



/*ADC conversion complete ISR*/
__attribute__((signal)) void __vector_16(void);
void __vector_16(void)
{
	if(ADC_u8ISRSource == SINGLE_ASYNCH)
	{
		voidHandleSingleConvAsynch();
	}
	else if(ADC_u8ISRSource == CHAIN_ASYNCH)
	{
		voidHandleChainConvAsynch();
	}

}
