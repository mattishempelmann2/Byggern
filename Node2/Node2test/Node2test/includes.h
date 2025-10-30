/*
 * includes.h
 *
 * Created: 21.10.2025 14:09:42
 *  Author: mattisjh
 */ 


#ifndef INCLUDES_H_
#define INCLUDES_H_

#define F_CPU 84000000
#define maxduty 4200
#define minduty 1800
#define ADC_MIN 66
#define ADC_MAX 245


#include "uart.h"
#include "can.h"
#include "sam.h"
#include <stdio.h>
#include "PWM.h"
#include "ADC.h"



#endif /* INCLUDES_H_ */