#ifndef ADC_REG_H
#define ADC_REG_H

#define  ADMUX        				*((volatile uint8*)0x27)  /*ADC multiplexer selection register*/
#define  ADMUX_REFS1  				7u      
#define  ADMUX_REFS0  				6u      
#define  ADMUX_ADLAR  				5u   /* ADC Left Adjust Result*/
					
				
				
#define  ADCSRA       				*((volatile uint8*)0x26) /* ADC Control and Status Register A – ADCSRA*/
#define  ADCSRA_ADEN  				7u
#define  ADCSRA_ADSC  				6u     /*ADC start conversion*/
#define  ADCSRA_ADATE 				5u
#define  ADCSRA_ADIF  				4u
#define  ADCSRA_ADIE  				3u
				
				
				
#define  ADCH         				*((volatile uint8*)0x25) 
#define  ADCL         				*((volatile uint8*)0x24)
#define ADC 						*((volatile uint16*)0x24)   /* Pointer to uint16 if we want to Access all 10 bit "Right Adjust"*/
				
#define SFIOR			  			*((volatile uint16*)0x50) /*Special FunctionIO Register –SFIOR*/
#define SFIOR_ADTS2                7u
#define SFIOR_ADTS1                6u
#define SFIOR_ADTS0                5u


						 						 						 


#endif
