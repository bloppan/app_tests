/*
 * main.c
 *
 *  Created on: Jan 26, 2022
 *      Author: bernar
 */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

#include "../../app_shared_libraries/libWSEN_TIDS/WSEN_TIDS_export.h"

#include "../../app_includes/app_errors.h"
#include "../../app_includes/app_typedef.h"



int main(void)
{

	float Temperature = 0;
	void *libHandlerWSEN = NULL;

	char route[256] = {0};


	strcat(route, "/usr/lib/");
	strcat(route, "libWSEN_TIDS.so.1");

	libHandlerWSEN = dlopen(route, RTLD_LAZY);

	if(libHandlerWSEN == NULL) {

		printf("[ERROR]\t[WSEN-TIDS]\tLoading %s library \n", route);
	}

	else {

		printf("[OK]\t[WSEN-TIDS]\tLibrary %s loaded successfully \n", route);

		WSEN_TIDS_Initialize		= (error_type ( *)(void)) dlsym(libHandlerWSEN, "WSEN_TIDS_Initialize");
		WSEN_TIDS_getTemperature 	= (error_type ( *)(float *)) dlsym(libHandlerWSEN, "WSEN_TIDS_getTemperature");

		WSEN_TIDS_Initialize();

		while(1){

			WSEN_TIDS_getTemperature(&Temperature);
			sleep(1);
		}
	}

	return 0;
}
