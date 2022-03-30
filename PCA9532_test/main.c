/*
 * main.c
 *
 *  Created on: Jul 30, 2021
 *      Author: bernardo
 */

#include "../../app_shared_libraries/libPCA9532/PCA9532_export.h"

#include <dlfcn.h>
#include <getopt.h>


void set_led(uint8_t led, char * color)
{

	 if(!strcmp(optarg, "GREEN")){
		 setLED_Value(led, GREEN);
	 }else if(!strcmp(optarg, "RED")){
		 setLED_Value(led, RED);
	 }else if(!strcmp(optarg, "BLUE")){
		 setLED_Value(led, BLUE);
	 }else if(!strcmp(optarg, "YELLOW")){
		 setLED_Value(led, YELLOW);
	 }else if(!strcmp(optarg, "PURPLE")){
		 setLED_Value(led, PURPLE);
	 }else if(!strcmp(optarg, "CYAN")){
		 setLED_Value(led, CYAN);
	 }else if(!strcmp(optarg, "WHITE")){
		 setLED_Value(led, WHITE);
	 }else if(!strcmp(optarg, "OFF")){
		 setLED_Value(led, LED_OFF);
	 }else{
		printf("[ERROR]\t\t[PCA9532] Invalid color \n");
	 }

}

int main(int argc, char *argv[])
{

	void *libHandlerPCA9532 = NULL;
	char route[256] = {0};

	int c;
	int wakeup = 0;
	int RTC_value = 0;
    int option_index = 0;

    static struct option long_options[] =
      {

        /* These options don’t set a flag.
           We distinguish them by their indices. */
        {"LED1",	required_argument,       0, 'a'},
        {"LED2",	required_argument,       0, 'b'},
        {"LED3",	required_argument,       0, 'c'},
        {"LED4",	required_argument,       0, 'd'},
        {"ALL",		required_argument,       0, 'e'},
        {0, 0, 0, 0}
      };


	// Carga la libreria PCA9532
	strcat(route, PCA9532_LIBRARY_DIRECTORY);
	strcat(route, PCA9532_LIBRARY_NAME);

	libHandlerPCA9532 = dlopen(route, RTLD_LAZY);

	if(libHandlerPCA9532 == NULL) {

		printf("[ERROR]\t[PCA9532]\tLoading %s library \n", route);

	}else {

		printf("[OK]\t[PCA9532]\tLibrary %s loaded successfully \n", route);

		// Carga de funciones de la libreria I2C:
		setLED_Value = (error_type ( *)(uint8_t, uint8_t)) dlsym(libHandlerPCA9532, "setLED_Value");
		PCA9532_Initialize = (error_type ( *)(void)) dlsym(libHandlerPCA9532, "PCA9532_Initialize");

		// Inicializa el controlador de LEDs
		PCA9532_Initialize();

	    /* getopt_long stores the option index here. */
	    while ((c = getopt_long_only(argc, argv, "abcdefghi", long_options, &option_index)) != -1)
	    {
	        // check to see if a single character or long option came through
	        switch (c)
	        {
	             // short option 't'
	             case 'a':
	            	 set_led(LED0, optarg);
	                 break;
	             case 'b':
	            	 set_led(LED1, optarg);
	                 break;
	             case 'c':
	            	 set_led(LED2, optarg);
	                 break;
	             case 'd':
	            	 set_led(LED3, optarg);
	                 break;
	             case 'e':
	            	 for(int i = 0; i < 4; i++){

	            		 set_led(i, optarg);
	            	 }
	                 break;
	        }
	    }

	    if (argc <= 1){

	    	printf("\n\n\nExample usage: \n\n");
	    	printf("\tPCA9532_test -LED1 GREEN \n");
	    	printf("\tPCA9532_test -LED1 OFF -LED3 RED -LED4 YELLOW \n");
	    	printf("\tPCA9532_test -ALL WHITE \n\n\n");

			// Test general
			printf("TEST GENERAL \n\n");

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
	}

	return 0;

}

