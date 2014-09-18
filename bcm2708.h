/**
 * header file needed to access the register of the RasPi
 * will be needed by the all the rest
 * this is based on the work of Pietjan VDM
 * see : http://www.pieter-jan.com/node/15
 * 
 * @author Arno Lambert <arno.lambert@gmail.com>
 */
 
#include <stdio.h>
 
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>

//this is where the register for RasPi begins
#define BCM2708_PERI_BASE       0x20000000
//start of the register for the GPIO pins
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)
 
#define BLOCK_SIZE 		(4*1024)
 
//structure needed to access different sorts of peripherals
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};
 
//I think this is not correct, should not be in header....
struct bcm2835_peripheral gpio = {GPIO_BASE};

//no idea what exactly this does....
extern struct bcm2835_peripheral gpio;  // They have to be found somewhere, but can't be in the header
