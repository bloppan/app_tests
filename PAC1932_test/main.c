/*
 * main.c
 *
 *  Created on: Jul 9, 2021
 *      Author: bernardo
 */

#include "../../app_shared_libraries/libPAC1932/PAC1932_export.h"

static PAC1932_struct PAC1932_data = {0};

int main (void)
{

	void *libHandler = NULL;
	char route[256] = {0};

	// Carga la libreria libPAC1932
	strcat(route, PAC1932_LIBRARY_DIRECTORY);
	strcat(route, PAC1932_LIBRARY_NAME);

	libHandler = dlopen(route, RTLD_LAZY);

	if(libHandler == NULL) {

		printf("[ERROR]\t[PAC1932]\tLoading %s library \n", route);

	}else {

		printf("[OK]\t[PAC1932]\tLibrary %s loaded successfully \n", route);

		// Carga de funciones de la libreria del sensor PAC1932
		PAC1932_Initialize			= (error_type ( *)(void)) dlsym(libHandler, "PAC1932_Initialize");
		PAC1932_GetAllValues	 	= (error_type ( *)(PAC1932_struct*)) dlsym(libHandler, "PAC1932_GetAllValues");
	}

	PAC1932_Initialize();

	while(1){

		PAC1932_GetAllValues(&PAC1932_data);
		printf("\n");
		sleep(1);
	}

	return 0;
}
