/*
 * ===========================================================================
 * Name        : main.c
 * Author      : Marc David Jensen Blunsdon
 * Version     : 1.0
 * Created on  : 05 Nov 2020
 * Copyright   : Open for all
 * Description : This file is an application for a strain gauge interface.
 *               Which uses Nordic Semiconductors Softdevice for BLE.
 *               The file is customize from Nordic example template for BLE.
 *               There are one profile with one service and 4 characteristic.
 *               Where the Get weight uses the SAADC (14 bit) to messure the 
 *               strain gauge value and stores it on a characteristic value.
 *               
 *               
 * =========================================================================== 
 */

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "app_error.h"
#include "app_timer.h"

#include "ble_cus.h"
#include "saadc.h"
#include "ble_temp.h"

// Declare functions
void timers_init(void);
void log_init(void);

/**@brief Function for main.
 */
int main(void)
{
    bool erase_bonds;
    // Initialize.
    log_init();
    timers_init();
    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    advertising_init();
    saadc_init();
    conn_params_init();
    //NRF_LOG_INFO("Advertising will begin!");
    advertising_start(erase_bonds);
    //NRF_LOG_INFO("INIT complet");

    //main loop forever
    while (true)
    {
        // wait for RTC interrupt
        __WFI();
    }
}







/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. 
 *          This creates and starts application timers.
*/
void timers_init(void)
{
    // Initialize timer module.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}  


/**@brief Function for initializing the nrf log module.
 */
void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}