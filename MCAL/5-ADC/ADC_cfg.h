#ifndef ADC_CFG_H
#define ADC_CFG_H

/*Configure the reference selection Bits, option:
 * 													1- AREF
 * 													2- AVCC
 * 													3- INTERNAL2_56V
 * 													*/
#define ADC_u8REFVOLT  								AVCC

/*Configure the ADC resolution,            option:
 * 													1- EIGHT_BIT
 * 													2- TEN_BIT
 * 													*/
#define ADC_u8RESOLUTION  							EIGHT_BIT

/*Configure the ADC Prescaler division factor,option:
 * 													1- DIVISION_BY_2
 * 													2- DIVISION_BY_4
 * 													3- DIVISION_BY_8
 * 													4- DIVISION_BY_16
 * 													5- DIVISION_BY_32
 * 													6- DIVISION_BY_64
 * 													7- DIVISION_BY_128
 * 													*/

#define ADC_u8PRESCALER_DIV_FACTOR                  DIVISION_BY_128







#endif
