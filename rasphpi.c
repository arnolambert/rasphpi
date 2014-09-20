/**
* main file to access the register of the RasPi
* this is based on the work of Pietjan VDM
* see :
* http://www.pieter-jan.com/node/15
* https://github.com/Pieter-Jan/PJ_RPI
*
* @author Arno Lambert <arno.lambert@gmail.com>
*/

#include "rasphpi.h"

struct bcm2835_peripheral gpio = {GPIO_BASE};


#ifdef COMPILE_DL_RASPHPI
ZEND_GET_MODULE(rasphpi)
#endif
 
int main()
{
    if(map_peripheral(&gpio) == -1) {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return(-1);
    }
 
    // Define pin 7 as output
    INP_GPIO(4);
    OUT_GPIO(4);
 
    while(1) {
        // Toggle pin 7 (blink a led!)
        GPIO_SET = 1 << 4;
        sleep(1);
 
        GPIO_CLR = 1 << 4;
        sleep(1);
    }
 
    return(0); 
}

/*
 * my first php function
 * will be replaced by the ones needed for the Raspberry
 */
static PHP_FUNCTION(rasphpi_hello)
{
    php_printf("hello raspberry\n");
}

static zend_function_entry rasphpi_functions[] = {
    PHP_FE(rasphpi_hello, NULL) {
        NULL,
        NULL,
        NULL
    }
};

//rasphpi_functions must be declared and defined first
//else you cannot use it here
zend_module_entry rasphpi_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_RASPHPI_EXTNAME,
    rasphpi_functions, // functions
    NULL, // MINIT
    NULL, // MSHUTDOWN
    NULL, // RINIT
    NULL, // RSHUTDOWN
    NULL, // MINFO
    PHP_RASPHPI_EXTVER,
    STANDARD_MODULE_PROPERTIES
};

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
   // Open /dev/mem
   if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }
 
   p->map = mmap(
      NULL,
      BLOCK_SIZE,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      p->mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p       // Address in physical map that we want this memory block to expose
   );
 
   if (p->map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }
 
   p->addr = (volatile unsigned int *)p->map;
 
   return 0;
}
 
void unmap_peripheral(struct bcm2835_peripheral *p) {
 
    munmap(p->map, BLOCK_SIZE);
    close(p->mem_fd);
}



