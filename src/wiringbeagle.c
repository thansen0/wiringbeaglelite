//#include <stdio.h>
//#include <stdlib.h> // malloc
//#include <string.h> // strcat and strcpy
//
//#define OUTPUT 1
//#define INPUT 2
//#define P____INPUT 3 // NOT IMPLENTED
//#define UNEXPORT 4
//
//#define HIGH 1
//#define LOW 0

#include "wiringbeagle.h"

char* itostr(int n) {
    // assumes value is smaller than 1000
    // also *str isn't free'd
    char *str = (char *) malloc(4*sizeof(char));
    snprintf(str, 4, "%i", n);
    return str;
}

short verifyPin(int pin) {
    return pin < 118;
}

int pinMode(int pin, short mode) {
    
    if (!verifyPin(pin)) {
        printf("Invalid pin (%i)\n", pin);
        return -1;
    }
    
    switch(mode) {
        case OUTPUT: {
            FILE* fexport, *fdirection;
//            char* path = "/sys/class/gpio";
            char* direction_path = (char *) malloc(30*sizeof(char));
            char* export_path = "/sys/class/gpio/export";
            
            strcpy(direction_path, "/sys/class/gpio/gpio");
            strcat(direction_path, itostr(pin));
            strcat(direction_path, "/direction");
            
            // creates folder structure for pin
            fexport = fopen(export_path, "w");
            if (fexport == NULL) {
                printf("Unable to open path %s\n", export_path);
                return -1;
            } else {
                fputs(itostr(pin), fexport);
            }
            fclose(fexport);
	    
            // waits for OS to export folder
            sleep(1);
            
            // sets pin to output
            fdirection = fopen(direction_path, "w");
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
            
            // creates folder structure for pin
            fexport = fopen(export_path, "w");
            if (fexport == NULL) {
                printf("Unable to open path %s\n", export_path);
                return -1;
            } else {
                fputs(itostr(pin), fexport);
            }
            fclose(fexport);
            
            // sets pin to be an input
            fdirection = fopen(direction_path, "w");
            if (fdirection == NULL) {
                printf("Unable to open path %s\n", direction_path);
                return -1;
            } else {
                fputs("in", fdirection);
            }
            fclose(fdirection);
            free(direction_path);
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
    
    FILE *fvalue;
    char* value_path = (char*) malloc(30*sizeof(char));
    char *value = (char*) malloc(sizeof(char));
    *value = type + '0';
    
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
    
    printf("Writing value %s\n", value);
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
    
    if (pin < 118) {
        printf("FUNCTION NOT FINISHED\n");
        return -1;
    }
    
    FILE *fvalue;
    char* value_path = (char*) malloc(30*sizeof(char));
    char *value = (char*) malloc(sizeof(char));
    
    if (!verifyPin(pin)) {
        printf("Invalid pin (%i)\n", pin);
        return -1;
    }
    
    // build file path
    strcpy(value_path, "/sys/class/gpio/gpio");
    strcat(value_path, itostr(pin));
    strcat(value_path, "/value");
    
    fvalue = fopen(value_path, "w");
    
    if (fvalue != NULL) {
        // Read value from file, return HIGH or LOW
        
        
    } else {
        printf("Unable to open vale file at %s; are you sure gpio pin was initialized?\n", value_path);
        return -1;
    }
    
    free(value_path);
    free(value);
    free(fvalue);
    return -1; // shouldn't have gotten this far
}

// int main() {
    
   // printf("Starting digitalWrite\n");
    
//    pinMode(67, OUTPUT);
//    digitalWrite(67, LOW);
    
    //printf("Completed digitalWrite()\n");
    
    //return 0;
//}
