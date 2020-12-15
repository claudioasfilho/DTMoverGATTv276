/***************************************************************************//**
 * @file app.c
 * @brief Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

#include "app.h"

/* Print boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt);

/* Flag for indicating DFU Reset must be performed */
static uint8_t boot_to_dfu = 0;


enum signal{
  signal_testmode_command_ready = 1,
};


typedef struct dtmtest {

	uint8_t OnFlag;
	uint8_t TxPower;
	uint8_t Channel;
	uint8_t PHY;
	uint8_t PacketType;
	uint8_t PacketSize;
	union {
			uint8_t  Data[4];
			uint32_t Value;
			}Result;

	union {
			uint8_t  Data[2];
			uint16_t Value;
			}TestTime;

} DTMTEST;


/**
 * @brief  Main function
 */
//It creates the structure that holds the DTM test Parameters
DTMTEST DTM;

void appMain(gecko_configuration_t *pconfig)
{


	//Initializes the DTM Test Parameters

	DTM.Channel = 0; 		//2402Mhz
	DTM.PacketType = 0;			// PRBS9 (GFSK)
	DTM.PHY = 1; 			//1M PHY
	DTM.TxPower = 0;		//0dBM
	DTM.PacketSize = 37; 	//37 Packets
	DTM.TestTime.Value = 10;		//10 Seconds

	DTM.Result.Value = 0;
	DTM.OnFlag = 0;

	uint8_t TimerCounter = 0;
	uint8_t TimerFlag = 0;


  /* Initialize debug prints. Note: debug prints are off by default. See DEBUG_LEVEL in app.h */
  initLog();

  /* Initialize stack */
  gecko_init(pconfig);

  while (1) {
    // Event pointer for handling events
    struct gecko_cmd_packet* evt;

    // Check for stack event.
    evt = gecko_wait_event();


    switch (BGLIB_MSG_ID(evt->header)) {

	case gecko_evt_system_boot_id:



		gecko_cmd_system_set_tx_power(0);   // set TX power to 0 dBm

		/* Set advertising parameters. 100ms advertisement interval.
		* The first two parameters are minimum and maximum advertising interval, both in
		* units of (milliseconds * 1.6). */
		gecko_cmd_le_gap_set_advertise_timing(0, 160, 160, 0, 0);

		/* Start general advertising and enable connections. */
		gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);


	break;

	case gecko_evt_le_connection_closed_id:


		/* Restart advertising after client has disconnected */
		gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);

	break;

	case gecko_evt_gatt_server_user_read_request_id:

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_On )
	          {
	              gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_On,0,1, &DTM.OnFlag);
	          }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_TestTime )
			  {
				  gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_TestTime,0,2, &DTM.TestTime.Data);
			  }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_Modulation )
	          {
	              gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_Modulation,0,1, &DTM.PacketType);
	          }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_PHY )
			  {
				  gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_PHY,0,1, &DTM.PHY);
			  }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_PacketSize )
			  {
				  gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_PacketSize,0,1, &DTM.PacketSize);
			  }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_Power )
			  {
				  gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_Power,0,1, &DTM.TxPower);
				  gecko_cmd_system_set_tx_power(DTM.TxPower);
			  }

	          if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_dtm_Result )
			  {
				  gecko_cmd_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,gattdb_dtm_Result,0,4, &DTM.Result.Data);
			  }


	break;

	case gecko_evt_gatt_server_user_write_request_id:

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_On)
			{
				DTM.OnFlag = evt->data.evt_gatt_server_attribute_value.value.data[0];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_On,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_TestTime)
			{
				DTM.TestTime.Data[0] = evt->data.evt_gatt_server_attribute_value.value.data[0];
				DTM.TestTime.Data[1] = evt->data.evt_gatt_server_attribute_value.value.data[1];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_TestTime,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_Modulation)
			{
				DTM.PacketType = evt->data.evt_gatt_server_attribute_value.value.data[0];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_Modulation,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_PHY)
			{
				DTM.PHY = evt->data.evt_gatt_server_attribute_value.value.data[0];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_PHY,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_PacketSize)
			{
				DTM.PacketSize = evt->data.evt_gatt_server_attribute_value.value.data[0];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_PacketSize,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_Power)
			{
				DTM.TxPower = evt->data.evt_gatt_server_attribute_value.value.data[0];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_Power,bg_err_success);
			}

			if (evt->data.evt_gatt_server_attribute_value.attribute==gattdb_dtm_Result)
			{
				DTM.Result.Data[0] = evt->data.evt_gatt_server_attribute_value.value.data[0];
				DTM.Result.Data[1] = evt->data.evt_gatt_server_attribute_value.value.data[1];
				DTM.Result.Data[2] = evt->data.evt_gatt_server_attribute_value.value.data[2];
				DTM.Result.Data[3] = evt->data.evt_gatt_server_attribute_value.value.data[3];
				//Response Back to the BLE client saying the data was received
				//gecko_cmd_gatt_server_send_user_write_response( evt->data.evt_gatt_server_user_write_request.connection,gattdb_dtm_Result,bg_err_success);
			}

	break;

	  case gecko_evt_hardware_soft_timer_id:
			  {
				  if (TimerCounter++==DTM.TestTime.Value)
				  {
					  gecko_cmd_hardware_set_soft_timer(0, 0, 0);
					  TimerCounter =0;
					  gecko_cmd_test_dtm_end();
					  TimerFlag = 1;

				  }
			  }
	        break;


	case gecko_evt_test_dtm_completed_id:
			{
				if ( TimerFlag == 1)

				{
					DTM.Result.Value = evt->data.evt_test_dtm_completed.number_of_packets;
					DTM.OnFlag = 0;
					 TimerFlag = 0;
					//gecko_cmd_system_reset(0);

					// gecko_cmd_le_gap_start_advertising(0,2,2);
					 gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);

				}

			}
	break;

	case gecko_evt_system_error_id:


		break;

    }

    if (DTM.OnFlag==1) //If test mode is set then it triggers the test
    {
    	//gecko_cmd_le_gap_stop_advertising(0);

    	DTM.Result.Value = 0;

    	gecko_cmd_hardware_set_soft_timer(32768, 0, 0);

    	gecko_cmd_test_dtm_tx(DTM.PacketType,DTM.PacketSize,DTM.Channel,DTM.PHY);


    }
  }
}

/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
