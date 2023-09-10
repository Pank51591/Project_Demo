/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016, 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HOST_MSD_FATFS_H_
#define _HOST_MSD_FATFS_H_

#include "usb_host.h"
#include "usb_host_msd.h"
#include "Boot.h"
/*******************************************************************************
 * IAP Definitions
 ******************************************************************************/

extern uint8_t Temp_read_buff[WRITE_BUFF_SIZE];
extern uint8_t Temp_write_buff[WRITE_BUFF_SIZE];
extern uint32_t Calculation_Read_checksum;
extern uint32_t Calculation_Write_checksum;
extern uint32_t Packet_Total_lenth;
extern uint16_t Updatepacketsize;
extern uint32_t Remaining_size;
extern uint16_t Temp_count;
extern uint16_t Loop_count;
extern uint32_t Operation_address;
extern uint32_t Temp_write_HalfWord;
extern uint8_t Version_buff[3]; // Head  Checksum  Version


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief 0 - execute normal fatfs test code; 1 - execute throughput test code */
#define MSD_FATFS_THROUGHPUT_TEST_ENABLE (0U)

/*! @brief host app run status */
typedef enum _usb_host_msd_run_state
{
    kUSB_HostMsdRunIdle = 0,         /*!< idle */
    kUSB_HostMsdRunSetInterface,     /*!< execute set interface code */
    kUSB_HostMsdRunWaitSetInterface, /*!< wait set interface done */
    kUSB_HostMsdRunMassStorageTest   /*!< execute mass storage test code */
} usb_host_msd_run_state_t;

/*! @brief USB host msd fatfs instance structure */
typedef struct _usb_host_msd_fatfs_instance
{
    usb_host_configuration_handle configHandle; /*!< configuration handle */
    usb_device_handle deviceHandle;             /*!< device handle */
    usb_host_class_handle classHandle;          /*!< class handle */
    usb_host_interface_handle interfaceHandle;  /*!< interface handle */
    uint8_t prevDeviceState;                    /*!< device attach/detach previous status */
    uint8_t deviceState;                        /*!< device attach/detach status */
    uint8_t runWaitState;                       /*!< application wait status, go to next run status when the wait status success */
    uint8_t runState;                           /*!< application run status */
} usb_host_msd_fatfs_instance_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief host msd callback function.
 *
 * This function should be called in the host callback function.
 *
 * @param deviceHandle           device handle.
 * @param configurationHandle attached device's configuration descriptor information.
 * @param eventCode           callback event code, please reference to enumeration host_event_t.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_NotSupported         The configuration don't contain msd interface.
 * @retval kStatus_USB_Error                There is no idle msd instance.
 */
extern usb_status_t USB_HostMsdEvent(usb_device_handle deviceHandle,
                                     usb_host_configuration_handle configurationHandle,
                                     uint32_t eventCode);

/*!
 * @brief host msd fatfs task function.
 *
 * This function implements the host msd fatfs action, it is used to create task.
 *
 * @param arg   the host msd fatfs instance pointer.
 */
extern void USB_HostMsdTask(void *arg,uint8_t param);

#endif /* _HOST_MSD_FATFS_H_ */
