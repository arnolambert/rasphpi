/**
 * header file needed to access the register of the RasPi
 * will be needed by the all the rest
 * this is based on the work of Pieter-Jan VDM
 * see : 
 * http://www.pieter-jan.com/node/15
 * https://github.com/Pieter-Jan/PJ_RPI
 * 
 * @author Arno Lambert <arno.lambert@gmail.com>
 */
 
#include <stdio.h>
 
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>
#include <fcntl.h>    /* For O_RDWR */

//this is where the register for RasPi begins
#define BCM2708_PERI_BASE       0x20000000
//start of the register for the GPIO pins
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)
 
#define BLOCK_SIZE 		(4*1024)
 
/*
 * define some macros
 * always use INP_GPIO(x) before using OUT_GPIO(x)
 */

//define pin g as input pin
#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))

//define pin g as output pin
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))

//
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
 
//sets bits which are 1 ignores bits which are 0
#define GPIO_SET  *(gpio.addr + 7)  

//clears bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) 

//
#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

/*
 * structure needed to access different sorts of peripherals
 */
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};

/*
 * define some functions
 * these will be implemented in rasphpi.c
 */
int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);

/*
 * some header settings to make this a PHP extension
 * this is taken from the book 'Extending and Embedding PHP' by Sara Golemon
 */

//prevent double inclusion
#ifndef PHP_SAMPLE_H
#define PHP_SAMPLE_H

//define extension properties
#define PHP_RASPHPI_EXTNAME "rasphpi"
#define PHP_RASPHPI_EXTVER "0.1"

//import some configure options if any
//can be handy to build this outside the php source tree
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//php standard header
#include "php.h"

//entry point Zend will use when loading this extension
extern zend_module_entry rasphpi_module_entry;
#define phpext_rasphpi_ptr &raspphpi_module_entry

#endif //PHP_SAMPLE_H
