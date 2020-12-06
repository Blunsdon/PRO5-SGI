/*
 * ===========================================================================
 * Name        : ble.h
 * Author      : Marc David Jensen Blunsdon
 * Version     : 1.0
 * Created on  : 23 Nov 2020
 * Copyright   : Open for all
 * Description : header file
 * =========================================================================== 
 */

#ifndef BLE_TEMP_H
#define BLE_TEMP_H

#include "ble_advertising.h"
#include "bsp_btn_ble.h"
#include "ble_conn_params.h"

void gap_params_init(void);

void gatt_init(void);

void nrf_qwr_error_handler(uint32_t nrf_error);

void conn_params_init(void);

void on_conn_params_evt(ble_conn_params_evt_t * p_evt);

void services_init(void);

void conn_params_error_handler(uint32_t nrf_error);

void on_adv_evt(ble_adv_evt_t ble_adv_evt);

void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context);

void ble_stack_init(void);

void advertising_init(void);

void advertising_start(bool erase_bonds);

void delete_bonds(void);

#endif //BLE_TEMP_H
