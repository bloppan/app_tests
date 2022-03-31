/*
 * main.c
 *
 *  Created on: Jul 30, 2021
 *      Author: bernardo
 */

#include "../../app_shared_libraries/libPCA9532/PCA9532_export.h"

#include <dlfcn.h>
#include <getopt.h>


uint8_t blink_led = 0;

void set_led(uint8_t led, char * color)
{

	 if(!strcmp(color, "GREEN")){
		 setLED_Color_Blink(led, GREEN, blink_led);
	 }else if(!strcmp(color, "RED")){
		 setLED_Color_Blink(led, RED, blink_led);
	 }else if(!strcmp(color, "BLUE")){
		 setLED_Color_Blink(led, BLUE, blink_led);
	 }else if(!strcmp(color, "YELLOW")){
		 setLED_Color_Blink(led, YELLOW, blink_led);
	 }else if(!strcmp(color, "PURPLE")){
		 setLED_Color_Blink(led, PURPLE, blink_led);
	 }else if(!strcmp(color, "CYAN")){
		 setLED_Color_Blink(led, CYAN, blink_led);
	 }else if(!strcmp(color, "WHITE")){
		 setLED_Color_Blink(led, WHITE, blink_led);
	 }else if(!strcmp(color, "OFF")){
		 setLED_Color_Blink(led, LED_OFF, blink_led);
	 }else{
		printf("[ERROR][PCA9532]\t\tInvalid color \n");
	 }

}

int main(int argc, char *argv[])
{

	void *libHandlerPCA9532 = NULL;
	char route[256] = {0};

	int c;
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
        {"BLINK",	required_argument,       0, 'f'},
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
		setLED_Color_Blink = (error_type ( *)(uint8_t, uint8_t, uint8_t)) dlsym(libHandlerPCA9532, "setLED_Color_Blink");
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
	             case 'f':
	            	 blink_led = atoi(optarg);
	            	 break;
	        }
	    }

	    if (argc <= 1){

	    	printf("\n\n\nExample usage: \n\n");
	    	printf("\tPCA9532_test -LED1 GREEN \n");
	    	printf("\tPCA9532_test -LED1 OFF -LED3 RED -LED4 YELLOW \n");
	    	printf("\tPCA9532_test -ALL WHITE \n");
	    	printf("\tPCA9532_test -LED1 GREEN -BLINK 1 -LED2 BLUE -LED3 RED\n");
	    	printf("\tPCA9532_test -LED1 GREEN -BLINK 1 -LED2 BLUE -BLINK 2 -LED3 RED\n\n\n");
			// Test general
			printf("TEST GENERAL \n\n");

			for(int i = 0; i < 4; i ++){

				for(int j = 0; j < 3; j++){

					setLED_Color_Blink(i, j, 0);
					sleep(1);
				}
			}

			setLED_Color_Blink(LED0, PURPLE, 0);
			sleep(1);
			setLED_Color_Blink(LED1, CYAN, 0);
			sleep(1);
			setLED_Color_Blink(LED2, YELLOW, 0);
			sleep(1);
			setLED_Color_Blink(LED3, WHITE, 0);
			sleep(1);

			for(int i = 0; i < 4; i ++){

				setLED_Color_Blink(i, LED_OFF, 0);
				sleep(1);
			}
	    }
	}

	return 0;

}

