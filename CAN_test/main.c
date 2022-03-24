/*
 * main.c
 *
 *  Created on: 15/12/2021
 *      Author: bernardo
 */

#include <dlfcn.h>
#include <stdio.h>

#include "../../app_shared_libraries/libCAN/CAN_export.h"

int main(void)
{
	void *libHandler = NULL;

	struct can_message can_info;

	char route[256] = {0};

	// Carga la libreria libCAN
	strcat(route, "/usr/lib/libCAN.so.1");

	libHandler = dlopen(route, RTLD_LAZY);

	if(libHandler == NULL) {

		printf("[ERROR] Loading CAN library \n");

	}else {

		printf("[OK] CAN library loaded \n");

		CAN_Initialize		= (error_type ( *)(struct can_message *)) dlsym(libHandler, "CAN_Initialize");
		CAN_Configure		= (error_type ( *)(struct can_message *)) dlsym(libHandler, "CAN_Configure");
		CAN_Send 		= (error_type ( *)(struct can_message *)) dlsym(libHandler, "CAN_Send");
		CAN_SendFile 	= (error_type ( *)(struct can_message *, char *)) dlsym(libHandler, "CAN_SendFile");
		CAN_Receive 		= (error_type ( *)(struct can_message *)) dlsym(libHandler, "CAN_Receive");


		CAN_Initialize(&can_info);
		CAN_Configure(&can_info);

		CAN_SendFile(&can_info, "/home/info.json");

	}

	return 0;
}
