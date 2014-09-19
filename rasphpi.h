/**
 * header file needed to access the register of the RasPi
 * will be needed by the all the rest
 * this is based on the work of Pietjan VDM
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

