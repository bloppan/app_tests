/*
 * main.c
 *
 *  Created on: Jul 30, 2021
 *      Author: bernardo
 */

#include "../libPCA9532/PCA9532_export.h"

#include <dlfcn.h>


#define	SIZE_BUFFER		4

int main (void)
{
	uint8_t buffer[SIZE_BUFFER];

	void *libHandlerPCA9532 = NULL;
	char route[256] = {0};

	// Carga la libreria PCA9532
	strcat(route, PCA9532_LIBRARY_DIRECTORY);
	strcat(route, PCA9532_LIBRARY_NAME);

	libHandlerPCA9532 = dlopen(route, RTLD_LAZY);

	if(libHandlerPCA9532 == NULL) {

		printf("[ERROR]\t[PCA9532]\tLoading PCA9532 library\n");

	}else {

		printf("[OK]\t[PCA9532]\tPCA9532 library loaded successfully \n");

		// Carga de funciones de la libreria I2C:
		setLED_Value = (error_type ( *)(uint8_t, uint8_t)) dlsym(libHandlerPCA9532, "setLED_Value");
		PCA9532_Initialize = (error_type ( *)(void)) dlsym(libHandlerPCA9532, "PCA9532_Initialize");

		PCA9532_Initialize();

		for(int i = 0; i < 4; i ++){

				for(int j = 0; j < 3; j++){

					setLED_Value(i, j);
					sleep(1);
				}
			}

			setLED_Value(LED0, PURPLE);
			sleep(1);
			setLED_Value(LED1, CYAN);
			sleep(1);
			setLED_Value(LED2, YELLOW);
			sleep(1);
			setLED_Value(LED3, WHITE);
			sleep(1);

			for(int i = 0; i < 4; i ++){

				setLED_Value(i, LED_OFF);
				sleep(1);
			}
	}


	return 0;
}

