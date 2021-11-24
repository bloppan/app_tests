/*
 * main.c
 *
 *  Created on: Jun 30, 2021
 *      Author: bernardo
 */


#include "../../app_shared_libraries/libHTS221/HTS221_export.h"

int main (void)
{

	void *libHandlerHTS221 = NULL;
	float Temperatura, Humedad;

	char route[256] = {0};

	// Carga la libreria libPAC1932
	strcat(route, HTS221_LIBRARY_DIRECTORY);
	strcat(route, HTS221_LIBRARY_NAME);

	libHandlerHTS221 = dlopen(route, RTLD_LAZY);

	if(libHandlerHTS221 == NULL) {

		printf("[ERROR] al cargar la libreria HTS221 \n");
	}

	else {

		printf("[OK] Libreria sensor HTS221 cargada \n");

		HTS221_Initialize		= (error_type ( *)(void)) dlsym(libHandlerHTS221, "HTS221_Initialize");
		HTS221_getHumidity 		= (error_type ( *)(float *)) dlsym(libHandlerHTS221, "HTS221_getHumidity");
		HTS221_getTemperature 	= (error_type ( *)(float *)) dlsym(libHandlerHTS221, "HTS221_getTemperature");

		HTS221_Initialize();

		while(1){

			if(HTS221_getHumidity(&Humedad) != NO_ERROR){
				printf("[ERROR] Leyendo Humedad \n");
			}
			if(HTS221_getTemperature(&Temperatura) != NO_ERROR){
				printf("[ERROR] Leyendo Temperatura \n");
			}
			printf("Temperatura: %.2f, Humedad: %.2f \n", Temperatura, Humedad);
			sleep(1);
		}
	}

	return 0;
}



