#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"


#include "ADC_cfg.h"
#include "ADC_prv.h"
#include "ADC_reg.h"
#include "ADC_interface.h"



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

uint16 ADC_u8GetChannelReading(uint8 Copy_u8Channel)
{
	/*Set channel*/
	ADMUX &= CHANNEL_BIT_MASK;
	ADMUX |=Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*wait until conversion time ended "polling whit blocking"*/
	while((GET_BIT(ADCSRA, ADCSRA_ADIF))==0);

	/*Clear flag Bit By SET it*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);

	/*Get the conversion result*/
#if ADC_u8RESOLUTION == EIGHT_BIT
	return ADCH;

#elif ADC_u8RESOLUTION == TEN_BIT
	return ADC;

#endif

}
