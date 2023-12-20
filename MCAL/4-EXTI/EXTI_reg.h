#ifndef EXTI_REG_H
#define EXTI_REG_H

#define  GICR         *((volatile uint8*)0x5B) /*General interrupt control reg*/ 
#define  GICR_INT1    7u					   /*INT1 bit*/							 
#define  GICR_INT0    6u					   /*INT0 bit*/	 
#define  GICR_INT2    5u					   /*INT2 bit*/	


#define  MCUCR         *((volatile uint8*)0x55)  /*MCU Control register*/
#define  MCUCR_ISC00    0u						 /*INT0 sense control Bit0*/
#define  MCUCR_ISC01    1u						 /*INT0 sense control Bit0*/
#define  MCUCR_ISC10    2u						 /*INT1 sense control Bit0*/						 
#define  MCUCR_ISC11    3u						 /*INT1 sense control Bit0*/		

#define  MCUCSR         *((volatile uint8*)0x54)  
#define  MCUCSR_ISC2    6u
						 						 						 


#endif
