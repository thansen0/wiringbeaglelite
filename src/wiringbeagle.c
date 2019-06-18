/*
 * Wiringbeaglelite, 2019
 * Created By Thomas Hansen
 *
 */
#include "string.h"
#include "wiringbeagle.h"

struct PWM_pin {
	int pin_number;
	int export_number;
	int exported;
	char* path;
};

// Define in a function
struct PWM_pin pwm_meta[6];

char* itostr(int n) {
    // assumes value is smaller than 1000
    // also *str isn't free'd
    char *str = (char *) malloc(4*sizeof(char));
    snprintf(str, 4, "%i", n);
    return str;
}

short verifyPin(int pin) {
	int GPIO_pin_numbers[] = {
        30, 31, 48, 4, 3, 49, 117, 125, 121, 120,
		20, 60, 40, 51, 5, 2, 15, 14, 123, 122,
		7, 38, 34, 66, 69, 45, 23, 47, 27, 22,
		62, 36, 32, 86, 87, 10, 9, 8, 78, 76,
		74, 72, 70, 39, 35, 67, 68, 44, 26, 46,
		65, 63, 37, 33, 61, 88, 89, 11, 81, 80, 
		79, 77, 75, 73, 71
	};
    
	int len = sizeof(GPIO_pin_numbers)/sizeof(int);

	for (int i = 0; i < len; ++i) {
		if (GPIO_pin_numbers[i] == pin) {
			// valud GPIO pin, return true 
			return 0;
		}
	}

	// found no valid pins, return false
	return -1;
}

short verifyPWMPin(int pin) {
	// disregarding P8 and P9 since they don't overlap
	int PWM_pin_numbers[] = {14, 16, 21, 22, 13, 19};
	int len = sizeof(PWM_pin_numbers)/sizeof(int);

	for (int i = 0; i < len; ++i) {
		if (PWM_pin_numbers[i] == pin) {
			// valud PWM pin, return true 
			return 0;
		}
	}

	// found no valid pins, return false
	return -1;
}

int getPWMIndex(int pin) {
	int len = sizeof(pwm_meta)/sizeof(struct PWM_pin);

	for (int i = 0; i < len; i++) {
		if (pwm_meta[i].pin_number == pin) {
			return i;
		}
	}
	// not found, returning false
	return -1;
}

int pinMode(int pin, short mode) {
    
    if (!verifyPin(pin)) {
        printf("Invalid pin %i\n", pin);
        return -1;
    }
    
    switch(mode) {
        case OUTPUT: {
            FILE *fexport, *fdirection;
            char *direction_path = (char *) malloc(30*sizeof(char));
            char *export_path = "/sys/class/gpio/export";
            
            strcpy(direction_path, "/sys/class/gpio/gpio");
            strcat(direction_path, itostr(pin));
            strcat(direction_path, "/direction");
           
            fdirection = fopen(direction_path, "w");

            // export pin if it doesn't exist
            if (fdirection == NULL) {

            	// creates folder structure for pin
            	fexport = fopen(export_path, "w");
            	if (fexport == NULL) {
                	printf("Unable to open path %s\n", export_path);
                	return -1;
            	} else {
                	fputs(itostr(pin), fexport);
                    fclose(fexport);
            	}
	   
                sleep(1);
            	fdirection = fopen(direction_path, "w");
            }
            
            // sets pin to output
            if (fdirection == NULL) {
                printf("Unable to open path %s\n", direction_path);
                return -1;
            } else {
                fputs("out", fdirection);
            }
            fclose(fdirection);
            free(direction_path);
            break;
            
        } case INPUT: {
            FILE* fexport, *fdirection;
            char* export_path = "/sys/class/gpio/export";
            char* direction_path = (char *)malloc(30*sizeof(char));
            
            strcpy(direction_path, "/sys/class/gpio/gpio");
            strcat(direction_path, itostr(pin));
            strcat(direction_path, "/direction");
            
            // ensure pin isn't already exported
            fdirection = fopen(direction_path, "w");

            if (fdirection == NULL) {
                    // creates folder structure for pin
                fexport = fopen(export_path, "w");
                if (fexport == NULL) {
                printf("Unable to open path %s\n", export_path);
                    return -1;
                } else {
                    fputs(itostr(pin), fexport);
                    fclose(fexport);
                }
                sleep(1);
                fdirection = fopen(direction_path, "w");
                
            }

            // sets pin to be an input
            // fdirection = fopen(direction_path, "w");
            if (fdirection == NULL) {
                printf("Unable to open path %s\n", direction_path);
                return -1;
            } else {
                fputs("in", fdirection);
            }
            fclose(fdirection);
            free(direction_path);
            break;

        } case PWMOUTPUT: {
            if (pwm_meta[0].path == NULL) {
                pwm_meta[0].path = "/sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip2/pwm-2:0";
                pwm_meta[0].pin_number = 14;
                pwm_meta[0].export_number = 0;
                pwm_meta[0].exported = -1; // false
            
                pwm_meta[1].path = "/sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip2/pwm-2:1";
                pwm_meta[1].pin_number = 16;
                pwm_meta[1].export_number = 1;
                pwm_meta[1].exported = -1;
            
                pwm_meta[2].path = "/sys/devices/platform/ocp/48300000.epwmss/48300200.pwm/pwm/pwmchip0/pwm-0:1";
                pwm_meta[2].pin_number = 21;
                pwm_meta[2].export_number = 1;
                pwm_meta[2].exported = -1;
            
                pwm_meta[3].path = "/sys/devices/platform/ocp/48300000.epwmss/48300200.pwm/pwm/pwmchip0/pwm-0:0";
                pwm_meta[3].pin_number = 22;
                pwm_meta[3].export_number = 0;
                pwm_meta[3].exported = -1;
            
                pwm_meta[4].path = "/sys/devices/platform/ocp/48304000.epwmss/48304200.pwm/pwm/pwmchip4/pwm-4:1";
                pwm_meta[4].pin_number = 13;
                pwm_meta[4].export_number = 1;
                pwm_meta[4].exported = -1;
            
                pwm_meta[5].path = "/sys/devices/platform/ocp/48304000.epwmss/48304200.pwm/pwm/pwmchip4/pwm-4:0";
                pwm_meta[5].pin_number = 19;
                pwm_meta[5].export_number = 0;
                pwm_meta[5].exported = -1;
            }

            // get index, check if folder exists
            int index = getPWMIndex(pin);
            char tmp_str[100];
			strcpy(tmp_str, pwm_meta[index].path);
			strcat(tmp_str, "/period");
			
			FILE* tmp = fopen(tmp_str, "r");

            if (!tmp) {
                // file does not exist
                printf("Folder must be exported, but I haven't implemented this yet because I'm a moron\n");
                printf("I should push it in the next few days, otherwise feel free to export it manually\n");
                return -1;
			}

            pwm_meta[index].exported = 0;
			fclose(tmp);
            break;

        } case UNEXPORT: {
            FILE* f_unexport;
            char* unexport_path = (char *)malloc(30*sizeof(char));
            
            strcpy(unexport_path, "/sys/class/gpio/unexport");
            
            f_unexport = fopen(unexport_path, "w");
            
            if (f_unexport != NULL) {
                fputs(itostr(pin), f_unexport);
            } else {
                printf("Unable to open unexport file at %s\n", unexport_path);
                return -1;
            }
            
            fclose(f_unexport);
            free(unexport_path);
            break;
            
        } default: {
            printf("Invalid mode selected\n");
            break;
        }
    }
    return 0;
}

int digitalWrite(int pin, short type) {
    
    FILE* fvalue;
    char* value_path = (char*) malloc(30*sizeof(char));
    //char *value = (char*) malloc(sizeof(char));
    //*value = type + '0';
    char* value = itostr((int)type);

    if (!verifyPin(pin)) {
        printf("Invalid pin (%i)\n", pin);
        return -1;
    }
    
    if (type > HIGH || type < LOW) {
        printf("Must write either a HIGH or LOW value to pin\n");
        return -1;
    }
    
    // build file path
    strcpy(value_path, "/sys/class/gpio/gpio");
    strcat(value_path, itostr(pin));
    strcat(value_path, "/value");
    
    fvalue = fopen(value_path, "w");
    
    if (fvalue != NULL) {
    	printf("Writing value %s\n", value);
    	fputs(value, fvalue);
    } else {
        printf("Unable to open vale file at %s; are you sure gpio pin was initialized?\n", value_path);
        return -1;
    }
   
    fclose(fvalue);
    free(value_path);
    free(value);
    
    return 0; // success
}

int digitalRead(int pin) {
    
    if (!verifyPin(pin)) {
        printf("Invalid pin %i\n", pin);
        return -1;
    }
    
    FILE *fvalue;
    char *value_path =	(char*) malloc(30*sizeof(char));
    char *value =		(char*) malloc(sizeof(char));
    
    // build file path
    strcpy(value_path, "/sys/class/gpio/gpio");
    strcat(value_path, itostr(pin));
    strcat(value_path, "/value");
    
    fvalue = fopen(value_path, "r");
    
    if (fvalue != NULL) {
        // Read value from file, return HIGH or LOW
        int readValue;
	fscanf(fvalue, "%d", &readValue);

	if (readValue == 0) {
		free(value_path);
		free(value);
		fclose(fvalue);
		return LOW;
	} else if(readValue > 0) {
		free(value_path);
		free(value);
		fclose(fvalue);
		return HIGH;
	}

    } else {
	free(value_path);
	free(value);
	fclose(fvalue);
        printf("Unable to open vale file at %s; are you sure gpio pin was initialized?\n", value_path);
        return -1;
    }
    
    free(value_path);
    free(value);
    fclose(fvalue);
    return -1; // shouldn't have gotten this far
}

int analogWrite2(int pin, int period, int duty_cycle) {
	// verify pin
	if(verifyPWMPin(pin) != 0) {
		printf("Invalid PWM pin\n");
		return -1;
	}

	// translate pin to array position
	int array_pos = getPWMIndex(pin);
	if (array_pos == -1) {
		printf("Unable to find pin %i metadata, perhapse you haven't exported?\n", pin);
		return -1;
	}

	// initialize filepath variabiles
	FILE *fperiod, *fduty_cycle, *fenable;
	char *period_path =		(char*) malloc(90*sizeof(char));
	char *duty_cycle_path = (char*) malloc(90*sizeof(char));
	char *enable_path =		(char*) malloc(90*sizeof(char));

	// build file path
	strcpy(period_path, pwm_meta[array_pos].path);
	strcat(period_path, "/period");

	strcpy(duty_cycle_path, pwm_meta[array_pos].path);
	strcat(duty_cycle_path, "/duty_cycle");
	
	strcpy(enable_path, pwm_meta[array_pos].path);
	strcat(enable_path, "/enable");
	
	// ensure files exist by opening them
	if (fopen(pwm_meta[array_pos].path, "r") == NULL) {
		// file not exported
		printf("Pin %i not exported\n", pin);
		return -1;
	}
	
	fperiod = fopen(period_path, "w");
	fduty_cycle = fopen(duty_cycle_path, "w");
	fenable = fopen(enable_path, "w");

	// write period and duty_cycle
	if (fperiod != NULL) {
		fputs(itostr(period), fperiod);
	} else {
		printf("Period is unreachable at addr %s\n", period_path);
	}

	if (fduty_cycle != NULL) {
		fputs(itostr(duty_cycle), fduty_cycle);
	} else {
		printf("Duty cycle at pin %i is unreachable at addr %s\n", pin, duty_cycle_path);
	}
	
	if (fenable != NULL) {
		fputs("1", fenable);
	} else {
		printf("Unable to enable pin %i at path %s\n", pin, enable_path);
	}

	// close files and free memory
	fclose(fperiod);
	fclose(fduty_cycle);
	fclose(fenable);

	free(period_path);
	free(duty_cycle_path);
	free(enable_path);
}

int analogWrite(int pin, int duty_cycle) {
	// calls full analogWrite function
	return analogWrite2(pin, 255, duty_cycle);
}

