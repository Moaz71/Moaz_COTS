#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


void ADC_voidInit(void);

uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result);  /*return Error state*/

uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result, void(*Copy_pvNotificationFunc)(void));

/*Configure the ADC Analog channel and gain selection*/
#define ADC_u8SINGLE_ENDEND_ADC0				0u
#define ADC_u8SINGLE_ENDEND_ADC1				1u
#define ADC_u8SINGLE_ENDEND_ADC2				2u
#define ADC_u8SINGLE_ENDEND_ADC3				3u
#define ADC_u8SINGLE_ENDEND_ADC4				4u
#define ADC_u8SINGLE_ENDEND_ADC5				5u
#define ADC_u8SINGLE_ENDEND_ADC6				6u
#define ADC_u8SINGLE_ENDEND_ADC7				7u



#endif
