#ifndef ADC_PRV_H
#define ADC_PRV_H


#define AREF                  1u
#define AVCC          		  2u
#define INTERNAL2_56V 		  3u


#define  EIGHT_BIT            1u
#define  TEN_BIT              2u

#define DIVISION_BY_2         1u
#define DIVISION_BY_4         2u
#define DIVISION_BY_8         3u
#define DIVISION_BY_16        4u
#define DIVISION_BY_32        5u
#define DIVISION_BY_64        6u
#define DIVISION_BY_128 	  7u

#define PRESCALER_BIT_MASK    0b11111000
#define PRESCALER_BIT_POS     0u

#define CHANNEL_BIT_MASK      0b11100000


#define IDLE           		  0u
#define BUSY				  1u






#endif
