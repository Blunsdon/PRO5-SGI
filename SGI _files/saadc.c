/* ===========================================================================
 * Name        : saadc.c
 * Author      : Mevlüt Kahraman
 * Version     : 1.0
 * Created on  : 16 Nov 2020
 * Copyright   : Open for all
 * Description : Source file for the ADC
 *
 * =========================================================================== 
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


// Interrupt handler. But we are not using it now!!!
// Blocking mode : Processer waiting for the signal continuously
// We are using non-blocking mode
void saadc_callback_handler(nrf_drv_saadc_evt_t const * p_event) 
{
  // Empty handler function
}


void saadc_init(void)
{
  ret_code_t err_code;
  // Create a config struct and assign it default values along with the Pin number for ADC Input 
  // Pin Configuration
  // SE  : Single ended is enabled
  // AIN4: P0.18
  nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN4);
  nrf_drv_saadc_config_t saadc_config;
  //Configure SAADC
  // Initializing the saadc
  err_code = nrf_drv_saadc_init(NULL, saadc_callback_handler);
  APP_ERROR_CHECK(err_code);
  // Initializing the Channel which will be connected to that specific pin.
  // Channel 0 is enabled
  err_code = nrfx_saadc_channel_init(0, &channel_config);
  APP_ERROR_CHECK(err_code);
}