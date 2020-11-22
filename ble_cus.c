/*
 * ===========================================================================
 * Name        : ble_cus.c
 * Author      : Marc David Jensen Blunsdon
 * Version     : 1.0
 * Created on  : 31 Oct 2020
 * Copyright   : Open for all
 * Description : Source file with set up for ble service characteristic:
 *                - Calibatration
 *                - Get weight
 *                - Get load
 *                - Load
 *                - Empty
 *               And event handle set up for the characteristic
 *               Some code parts are inspiration from Nodic DevZone
 *               https://devzone.nordicsemi.com/ and from Nodic Semiconductor
 *               example code.
 * =========================================================================== 
 */

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "ble_cus.h"
#include <string.h>
#include <stdio.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

#include "nrf_delay.h"
//#include "saadc.h"
#include "nrf_drv_saadc.h"
//#include "nrf_drv_ppi.h"
//#include "nrf_drv_timer.h"

/**@brief Function for adding the Calibration characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t cali_value_char_add(ble_cus_t * p_cus, 
                                    const ble_cus_init_t * p_cus_init)
{
    // Set metadata variables
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    // Fill out metadata for char_md
    // sets what will be displayed to the central during service discovery
    memset(&char_md, 0, sizeof(char_md));
    // Add read properties
    char_md.char_props.read   = 1;
    // Add write properties
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;
    // Fill out metadata for attr_md
    memset(&attr_md, 0, sizeof(attr_md));
    // Read and write permission added
    attr_md.read_perm  = p_cus_init->cali_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->cali_value_char_attr_md.write_perm;
    // Attribute Value is located in stack memory, no user memory is required
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    // Set UUID for the characteristic and addes it to BLE stack
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CALI_VALUE_CHAR_UUID;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid    = &ble_uuid;
    // Set pointer to the attribute metadata
    attr_char_value.p_attr_md = &attr_md;
    // Sets size of the characteristic
    attr_char_value.init_offs   = 0;
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x39,0x39,0x39,0x39};
    attr_char_value.p_value     = value;
    // Add our characteristic
    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, 
                                               &char_md,
                                               &attr_char_value,
                                               &p_cus->cali_value_handles);
    // Error check
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

/**@brief Function for adding the Get weight characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t get_weight_char_add(ble_cus_t * p_cus,
                                    const ble_cus_init_t * p_cus_init)
{
    // Set metadata variables
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    // Fill out metadata for char_md
    // Sets what will be displayed to the central during service discovery
    memset(&char_md, 0, sizeof(char_md));
    // Add read properties
    char_md.char_props.read   = 1;
    // Add write properties
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;
    // Fill out metadata for attr_md
    memset(&attr_md, 0, sizeof(attr_md));
    // Read and write permission added
    attr_md.read_perm  = p_cus_init->get_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->get_value_char_attr_md.write_perm;
    // Attribute Value is located in stack memory, no user memory is required
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    // Set UUID for the characteristic and addes it to BLE stack
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = GET_VALUE_CHAR_UUID;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid    = &ble_uuid;
    // Set pointer to the attribute metadata
    attr_char_value.p_attr_md = &attr_md;
    // Sets size of the characteristic
    attr_char_value.init_offs   = 0;
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x39,0x39,0x39,0x39};
    attr_char_value.p_value     = value;
    // Add our characteristic
    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, 
                                               &char_md,
                                               &attr_char_value,
                                               &p_cus->get_value_handles);
    // Error check
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return NRF_SUCCESS;
}


/**@brief Function for adding the load characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t load_weight_char_add(ble_cus_t * p_cus, 
                                     const ble_cus_init_t * p_cus_init)
{
    // Set metadata variables
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    // Fill out metadata for char_md
    // Sets what will be displayed to the central during service discovery
    memset(&char_md, 0, sizeof(char_md));
    // Only write permission
    char_md.char_props.read   = 0;
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;
    // Fill out metadata for attr_md
    memset(&attr_md, 0, sizeof(attr_md));
    // Read and write permission added
    attr_md.read_perm  = p_cus_init->load_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->load_value_char_attr_md.write_perm;
    // Attribute Value is located in stack memory, no user memory is required
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    // Set UUID for the characteristic and addes it to BLE stack
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = LOAD_VALUE_CHAR_UUID;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid    = &ble_uuid;
    // Set pointer to the attribute metadata
    attr_char_value.p_attr_md = &attr_md;
    // Sets size of the characteristic
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x39,0x39,0x39,0x39};
    attr_char_value.p_value     = value;
    attr_char_value.init_offs   = 0;
    // Add our characteristic
    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, 
                                               &char_md,
                                               &attr_char_value,
                                               &p_cus->load_value_handles);
    // Error check
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

/**@brief Function for adding the Empty characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t empty_char_add(ble_cus_t * p_cus, 
                               const ble_cus_init_t * p_cus_init)
{
    // Set metadata variables
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    // Fill out metadata for char_md
    // Sets what will be displayed to the central during service discovery
    memset(&char_md, 0, sizeof(char_md));
    // Only write permission
    char_md.char_props.read   = 0;
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;
    // Fill out metadata for attr_md
    memset(&attr_md, 0, sizeof(attr_md));
        // Read and write permission added
    attr_md.read_perm  = p_cus_init->empty_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->empty_value_char_attr_md.write_perm;
    // Attribute Value is located in stack memory, no user memory is required
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    // Set UUID for the characteristic and addes it to BLE stack
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = EMPTY_VALUE_CHAR_UUID;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid    = &ble_uuid;
    // Set pointer to the attribute metadata
    attr_char_value.p_attr_md = &attr_md;
    // Sets size of the characteristic
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x00,0x00,0x00,0x00};
    attr_char_value.p_value     = value;
    attr_char_value.init_offs   = 0;
    // Add our characteristic
    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, 
                                               &char_md,
                                               &attr_char_value,
                                               &p_cus->empty_value_handles);
    // Error check
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

/**@brief Function for initialize service with characteristic
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
    if (p_cus == NULL || p_cus_init == NULL)
    {
        return NRF_ERROR_NULL;
    }
    uint32_t   err_code;
    ble_uuid_t ble_uuid;
    // Initialize service structure
    p_cus->conn_handle               = BLE_CONN_HANDLE_INVALID;
    // Add Custom Service UUID
    ble_uuid128_t base_uuid = {CUSTOM_SERVICE_UUID_BASE};
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
    VERIFY_SUCCESS(err_code);
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_SERVICE_UUID;
    // Add the Custom Service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, 
                                        &ble_uuid, &p_cus->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    // Add empty characteristic
    err_code = empty_char_add(p_cus, p_cus_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    // Add load characteristic
    err_code = load_weight_char_add(p_cus, p_cus_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    // Add get weight characteristic
    err_code = get_weight_char_add(p_cus, p_cus_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    // Add save calibration characteristic
    return cali_value_char_add(p_cus, p_cus_init);
}


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for updating the save calibration value.
 *
 * @details The application calls this function when the  calibration 
 *          value should be updated. When the get save calibration  
 *          characteristic is updated the client must read to get 
 *          the new value.
 *
 * @param[in]   p_cus          Custom Service structure.
 * @param[in]   Custom value   The calibration value.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cus_cali_value_update(ble_cus_t * p_cus, uint32_t custom_value)
{
    if (p_cus == NULL)
    {
        return NRF_ERROR_NULL;
    }
    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;
    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));
    gatts_value.len     = sizeof(uint32_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &custom_value;
    //NRF_LOG_INFO("Update new value for save calibration. \r\n");
    // Update characteristic value for save calibration.
    err_code = sd_ble_gatts_value_set(p_cus->conn_handle,
                                      p_cus->cali_value_handles.value_handle,
                                      &gatts_value);
    return err_code;
}

/**@brief Function for handling the Write event for new calibration.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void save_calibration(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t * p_evt_write = \ 
    &p_ble_evt->evt.gatts_evt.params.write;
    // Check if the handle passed with the event matches.
    if (p_evt_write->handle == p_cus->cali_value_handles.value_handle)
    {
        uint32_t m_custom_value = 0x00000000;
        uint32_t err_code = NRF_SUCCESS;
        //get the new calibration value
        uint32_t *characteristic1_value_adr;
        uint32_t characteristic1_value_val;
        characteristic1_value_adr = (uint32_t*) p_evt_write->data;
        characteristic1_value_val = *characteristic1_value_adr;
        //change to the new calibration value
        m_custom_value = characteristic1_value_val;
        //NRF_LOG_INFO("Changed to %x", m_custom_value);
        // Update the calibration value
        err_code = ble_cus_cali_value_update(p_cus, m_custom_value);
        // error check
        APP_ERROR_CHECK(err_code); 
    }
}


/**@brief Function for updating the get weight value.
 *
 * @details The application calls this function when the get weight value
 *          should be updated. First the circuit is activated and 
 *          the SAADC is turned on. The SAADC returns the new get weight 
 *          value characteristic which is then updated.
 *          The client must read to get the new value. 
 *
 * @param[in]   p_cus          Custom Service structure.
 * @param[in]   Custom value   
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cus_get_value_update(ble_cus_t * p_cus, uint32_t custom_value)
{
    if (p_cus == NULL)
    {
        return NRF_ERROR_NULL;
    }
    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;
    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));
    gatts_value.len     = sizeof(uint32_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &custom_value;
    //NRF_LOG_INFO("Update new value for get weight. \r\n");
    // Update characteristic value for get weight.
    err_code = sd_ble_gatts_value_set(p_cus->conn_handle,
                                      p_cus->get_value_handles.value_handle,
                                      &gatts_value);
    return err_code;
}


/**@brief Function for handling the get weight Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void get_weight(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
  ble_gatts_evt_write_t * p_evt_write = \
  &p_ble_evt->evt.gatts_evt.params.write;
  // Check if the handle passed with the event matches.
  if (p_evt_write->handle == p_cus->get_value_handles.value_handle)
  {
    uint32_t err_code = NRF_SUCCESS;
    // Get the value from app
    uint32_t *characteristic1_value_adr;
    uint32_t characteristic1_value_val;
    characteristic1_value_adr = (uint32_t*) p_evt_write->data;
    characteristic1_value_val = *characteristic1_value_adr;
    // check if protokol OK
    nrf_saadc_value_t adc_val;
    if(characteristic1_value_val == 0x7a65726f)
    {
      // Init value to 0
      uint32_t m_custom_value = 0x00000000;
      //NOTE: turn on the amplifer
      // Wait for Rise time is done 
      nrf_delay_us(100);
      // Converting 
      // Channel 0 is enabled
      // adc_val is saved in Channel 0
      nrfx_saadc_sample_convert(0, &adc_val);
      //NOTE: turn off the amplifer
      // Prompt adc_val to user
      NRF_LOG_INFO("Sample value read:  %d", adc_val);
      NRF_LOG_INFO("Update new value for get weight. \r\n");
      // Update the value
      m_custom_value = adc_val;
      NRF_LOG_INFO("m_custom value set:  %x", m_custom_value);
      err_code = ble_cus_get_value_update(p_cus, m_custom_value);
      // error check
      APP_ERROR_CHECK(err_code);
    }
  }
}

/**@brief Function for updating the current load value.
 *
 * @details The application calls this function when the current load value
 *          should be updated. When the current load value characteristic 
 *          is updated the client must read to get the new value.
 *
 * @param[in]   p_cus          Custom Service structure.
 * @param[in]   Custom value   New load value
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cus_load_value_update(ble_cus_t * p_cus, uint32_t custom_value)
{
    if (p_cus == NULL)
    {
        return NRF_ERROR_NULL;
    }
    //NRF_LOG_INFO("p_cus not NULL. \r\n");
    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;
    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));
    gatts_value.len     = sizeof(uint32_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &custom_value;
    //NRF_LOG_INFO("Update new value for current load. \r\n");
    // Update characteristic value for get weight.
    err_code = sd_ble_gatts_value_set(p_cus->conn_handle,
                                    p_cus->load_value_handles.value_handle,
                                    &gatts_value);
    return err_code;
}

/**@brief Function for handling the load Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void load(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
     ble_gatts_evt_write_t * p_evt_write = \
     &p_ble_evt->evt.gatts_evt.params.write;
    // Check if the handle passed with the event matches.
    if (p_evt_write->handle == p_cus->load_value_handles.value_handle)
    {
        uint32_t err_code = NRF_SUCCESS;
        //get the value from app
        uint32_t *characteristic1_value_adr;
        uint32_t characteristic1_value_val;
        characteristic1_value_adr = (uint32_t*) p_evt_write->data;
        characteristic1_value_val = *characteristic1_value_adr;
        // set new load value
        current_load = characteristic1_value_val;
        // Update load Characteristic
        err_code = ble_cus_load_value_update(p_cus, current_load); 
    }
}

/**@brief Function for handling the empty Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void empty(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
     ble_gatts_evt_write_t * p_evt_write = \
     &p_ble_evt->evt.gatts_evt.params.write;
    // Check if the handle passed with the event matches.
    if (p_evt_write->handle == p_cus->empty_value_handles.value_handle)
    {
        // Get the value from app
        uint32_t *characteristic1_value_adr;
        uint32_t characteristic1_value_val;
        characteristic1_value_adr = (uint32_t*) p_evt_write->data;
        characteristic1_value_val = *characteristic1_value_adr;
        uint32_t err_code = NRF_SUCCESS;
        // NRF_LOG_INFO("Empty value %x \r\n", characteristic1_value_val );
        // Check if protokol OK
        if(characteristic1_value_val == 0x4e554c4c)
        {
            // Set load value to 0
            current_load = 0x00000000;
            // Update load Characteristic
            err_code = ble_cus_load_value_update(p_cus, current_load);
        }
    }
}

void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_cus_t * p_cus = (ble_cus_t *) p_context;
    //make sure none of the pointers is NULL
    if (p_cus == NULL || p_ble_evt == NULL)
    {
        return;
    }
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_cus, p_ble_evt);
            break;
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_cus, p_ble_evt);
            break;
        // write event
        case BLE_GATTS_EVT_WRITE:
            save_calibration(p_cus, p_ble_evt);
            get_weight(p_cus, p_ble_evt);
            load(p_cus, p_ble_evt);
            empty(p_cus, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}
