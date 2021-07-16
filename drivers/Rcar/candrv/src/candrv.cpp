/*
 * candrv.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
#include "cxcan_types.h"
#include "candrv.h"


#ifndef _DEBUG_

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

    // create variables
    int socket0;
	struct sockaddr_can addr;
	struct ifreq ifr;
    struct timeval tv;
    int nbytes;
    socklen_t len = sizeof(addr);
    int u8end;
    // declare msgs
    struct can_frame frame;

    // declare filter variable
    struct can_filter rfilter[CAN_DP_MAX];

#endif


void can_init(void)
{
  	// init any hw code here, sockets, etc.
	#ifndef _DEBUG_

		setsockopt(socket0, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

		// create socket
		if ((socket0 = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
			perror("Socket");
			return 1;
		}

		// set can0 as channel
		strcpy(ifr.ifr_name, "can0" );
		ioctl(socket0, SIOCGIFINDEX, &ifr);

		// address
		memset(&addr, 0, sizeof(addr));
		addr.can_family = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;

		// bind socket
		if (bind(socket0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("Bind");
			return 1;
		}
	#endif

}

void can_filter_init(uint16_t ids_tbl[]) {

	int x;
	// initialze can filter
	#ifndef _DEBUG_

	for(x = CAN_DP_MAX; x > 0; x--) {
		rfilter[x].can_id   = can_msg_tbl[x].id;
		rfilter[x].can_mask = 0xFFF;
	}
	#endif

}

/**
 * Send CAN messages
 * to HW
 */
Std_ReturnType candrvSendMsg(cxcan_msg_t *msg) {
	//mrs driver implementation
	Std_ReturnType res = E_NOT_OK;

	#ifndef _DEBUG_
		frame.can_dlc = msg->dlc;
		frame.can_id = msg->id;

		for (int i=8; i>0; i--) {
			frame.data[i-1] = msg->data[i-1];
		}

		if(msg->hw_channel == 0) {
			// send to channel 0
			if (sendto(socket0, &frame, sizeof(struct can_frame), 0, (struct sockaddr*)&addr, sizeof(addr)) != sizeof(struct can_frame)) {
				res = E_OK;
			}
			else {
				res = E_NOT_OK;
			}
		}

	#else

		// check if response was positive or negative
		if(res == 1) {
			res = E_OK;
		}
		else {
			res = E_NOT_OK;
		}

	#endif

	return res;
}


/**
 * Receive CAN messages
 * from HW
 */
void receive_can_msg(cxcan_msg_t *msg) {

	if(msg->hw_channel == CAN0) {
		//ecucanRxHandler(&msg);
	}
}



void receive_can(void) {

	#ifndef _DEBUG_
		int nbytes;
		 can_msg_t msg;
		 struct can_frame framein;

		 nbytes = recvfrom(socket0, &framein, sizeof(struct can_frame), 0, (struct sockaddr*)&addr, &len);

		 msg.dlc = framein.can_dlc;
		 msg.id = framein.can_id;
		 msg.hw_channel = Veh_CAN_Channel;

		 for (int i=8; i>0; i--) {
			 msg.data[i-1] = framein.data[i-1];
		 }
		 receive_can_msg(&msg);
	#endif

}
