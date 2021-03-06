/*
 * main.c
 *
 *  Created on: Jul 26, 2021
 *      Author: bernardo
 */

#include "../../app_shared_libraries/libGPIO/GPIO_export.h"


int main(void){

	void *libHandler = NULL;
	char route[256] = {0};

	// Carga la libreria libGPIO
	strcat(route, GPIO_LIBRARY_DIRECTORY);
	strcat(route, GPIO_LIBRARY_NAME);

	libHandler = dlopen(route, RTLD_LAZY);

	if(libHandler == NULL) {

		printf("[ERROR]\t[GPIO]\tLoading %s library \n", route);

	}else {

		printf("[OK]\t[GPIO]\tLibrary %s loaded successfully \n", route);

		configGPIO = (error_type ( *)(uint8_t, char*)) dlsym(libHandler, "configGPIO");
		freeGPIO = (error_type ( *)(uint8_t)) dlsym(libHandler, "freeGPIO");
		getGPIO_Value = (error_type ( *)(uint8_t, uint8_t*)) dlsym(libHandler, "getGPIO_Value");
		getGPIO_Direction = (error_type ( *)(uint8_t, char*)) dlsym(libHandler, "getGPIO_Direction");
		setGPIO_Value = (error_type ( *)(uint8_t, uint8_t)) dlsym(libHandler, "setGPIO_Value");


		configGPIO(EN_4V2, "out");
		configGPIO(EN_5V_USB_MOB, "out");

		setGPIO_Value(EN_4V2, 0);
		setGPIO_Value(EN_5V_USB_MOB, 0);

		printf("Pulsa enter \n");

		getchar();

		setGPIO_Value(EN_4V2, 1);
		setGPIO_Value(EN_5V_USB_MOB, 1);

		printf("Fin del programa \n");

		freeGPIO(EN_4V2);
		freeGPIO(EN_5V_USB_MOB);
	}

	return 0;
}
