/*
 * ===========================================================================
 * Name        : saadc.h
 * Author      : Mevlüt Kahraman
 * Version     : 1.0
 * Created on  : 16 Nov 2020
 * Copyright   : Open for all
 * Description : header file
 * =========================================================================== 
 */
#include "nrf_drv_saadc.h" 

#ifndef SAADC_H
#define SAADC_H

nrf_saadc_value_t adc_val;


void saadc_init(void);

void saadc_callback_handler(nrf_drv_saadc_evt_t const * p_event) ;



#endif //SAADC_H