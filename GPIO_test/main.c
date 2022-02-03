/*
 * main.c
 *
 *  Created on: Jul 26, 2021
 *      Author: bernardo
 */

#include "../../app_shared_libraries/libGPIO/GPIO_export.h"


int main(void){

	uint8_t value;
	char direction[10] = {0};


	void *libHandler = NULL;
	char route[256] = {0};

	// Carga la libreria libPAC1932
	strcat(route, GPIO_LIBRARY_DIRECTORY);
	strcat(route, GPIO_LIBRARY_NAME);

	libHandler = dlopen(route, RTLD_LAZY);

	if(libHandler == NULL) {

		printf("[ERROR] al cargar la libreria libPAC1932 \n");

	}else {

		printf("[OK] Libreria libPAC1932 cargada \n");

		// Carga de funciones de la libreria del sensor PAC1932
		/*
		error_type (*configGPIO)(uint8_t gpio, char* direction);
		error_type (*freeGPIO)(uint8_t gpio);
		error_type (*getGPIO_Value)(uint8_t gpio, uint8_t* value);
		error_type (*getGPIO_Direction)(uint8_t gpio, char* direction);
		error_type (*setGPIO_Value)(uint8_t gpio, uint8_t value);
*/

		configGPIO = (error_type ( *)(uint8_t, char*)) dlsym(libHandler, "configGPIO");
		freeGPIO = (error_type ( *)(uint8_t)) dlsym(libHandler, "freeGPIO");
		getGPIO_Value = (error_type ( *)(uint8_t, uint8_t*)) dlsym(libHandler, "getGPIO_Value");
		getGPIO_Direction = (error_type ( *)(uint8_t, char*)) dlsym(libHandler, "getGPIO_Direction");
		setGPIO_Value = (error_type ( *)(uint8_t, uint8_t)) dlsym(libHandler, "setGPIO_Value");


		uint8_t gpio = EN_4V2;

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

		return 0;

		getGPIO_Value(gpio, &value);
		getGPIO_Direction(gpio, direction);
		getchar();
		setGPIO_Value(gpio, 1);
		getGPIO_Value(gpio, &value);
		getGPIO_Direction(gpio, direction);
		freeGPIO(gpio);
	}



	return 0;
}
