/*
 * ===========================================================================
 * Name        : ble_cus.h
 * Author      : Marc David Jensen Blunsdon
 * Version     : 1.0
 * Created on  : 31 Oct 2020
 * Copyright   : Open for all
 * Description : header file
 * =========================================================================== 
 */

#ifndef BLE_CUS_H
#define BLE_CUS_H

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

// UUID generated from a Random UUID generator (www.uuidtools.com)
// SGI Service UUID: 8fbf01f8-d0cf-413b-8c2e-4a81554e1377
#define CUSTOM_SERVICE_UUID_BASE         {0x77, 0x13, 0x4E, 0x55, 0x81, 0x4A,\
                                          0x2E, 0x8C,\
                                          0x3B, 0x41,\
                                          0xCF, 0xD0,\
                                          0xf8, 0x01, 0xBF, 0x8F}
#define CUSTOM_SERVICE_UUID               0x4200
// empty characteristic uuid
#define EMPTY_VALUE_CHAR_UUID             0x4201  
// load characteristic uuid
#define LOAD_VALUE_CHAR_UUID              0x4202 
// get weight characteristic uuid
#define GET_VALUE_CHAR_UUID               0x4203 
// calibration characteristic uuid
#define CALI_VALUE_CHAR_UUID              0x4204 
// define value for load
static uint32_t current_load = 0x00000000;

// Forward declaration of the ble_cus_t type.
typedef struct ble_cus_s ble_cus_t;

/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_CUS_DEF(_name)                         \
static ble_cus_t _name;                            \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                \
                     BLE_HRS_BLE_OBSERVER_PRIO,    \
                     ble_cus_on_ble_evt, &_name)

/**@brief Custom Service init structure. 
 *        This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    //Initial custom value
    uint8_t                       initial_custom_value;
    //Initial security level for save calibration attribute
    ble_srv_cccd_security_mode_t  cali_value_char_attr_md;
    //Initial security level for get weight attribute
    ble_srv_cccd_security_mode_t  get_value_char_attr_md;
    //Initial security level for load attribute
    ble_srv_cccd_security_mode_t  load_value_char_attr_md;
    //Initial security level for empty attribute
    ble_srv_cccd_security_mode_t  empty_value_char_attr_md;
} ble_cus_init_t;

/**@brief Custom Service structure. 
 * This contains various status information for the service. */
struct ble_cus_s
{
    // Handle of Custom Service (as provided by the BLE stack).
    uint16_t                      service_handle;
    // Handles save calibration characteristic.
    ble_gatts_char_handles_t      cali_value_handles;
    // Handles get weight characteristic.
    ble_gatts_char_handles_t      get_value_handles;
    //Handles load characteristic.
    ble_gatts_char_handles_t      load_value_handles;
    //Handles empty characteristic.
    ble_gatts_char_handles_t      empty_value_handles; 
    // Handle of the current connection as provided by the BLE stack,
    // is BLE_CONN_HANDLE_INVALID if not in a connection
    uint16_t                      conn_handle; 
    uint8_t                       uuid_type; 
};

/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_cus       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_cus_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);

#endif //BLE_CUS_H