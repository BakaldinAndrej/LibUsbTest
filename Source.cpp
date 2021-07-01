#include <stdio.h>    
#include <stdlib.h>    
#include <sys/types.h>    
#include <string.h>    
#include <libusb.h>    


#define BULK_EP_OUT     0x01       

int main(void)    
{   
    // Init libusb 
	libusb_context *ctx = NULL;
    int r = libusb_init(&ctx);    
    if(r < 0)    
    {    
        printf("\nfailed to initialise libusb\n");    
        return 1;    
    }    
    else    
        printf("\nInit Successful!\n");  
    libusb_set_debug(ctx, 6);  

    //Open
    auto handle = libusb_open_device_with_vid_pid(ctx, 0x483, 0x5740);

    if(libusb_kernel_driver_active(handle, 1) == 1)    
    {    
        printf("\nKernel Driver Active");    
        if(libusb_detach_kernel_driver(handle, 1) == 0)    
            printf("\nKernel Driver Detached!");    
        else    
        {    
            printf("\nCouldn't detach kernel driver!\n");  
            libusb_close(handle);    
            return -1;    
        }    
    }    

    auto e = libusb_claim_interface(handle, 1);    
    if(e < 0)    
    {    
        printf("\nCannot Claim Interface");   
        libusb_close(handle);    
        return -1;    
    }    
    else    
        printf("\nClaimed Interface\n");    
 

    //   Communicate     
    unsigned char *my_string;    
    auto transferred = 0;    
    auto received = 0;   
	const int nbytes = 4;  
    auto length = nbytes + 1;  

    my_string = (unsigned char *)malloc(length);  

    memset(my_string,'\0',64); 

    e = libusb_bulk_transfer(handle,BULK_EP_OUT,my_string,64,&received,0);  
    if(e == 0)    
    {    
        printf("\nReceived: ");    
        printf("%s",my_string);
    }    
    else    
    {    
        printf("\nError in read! e = %d and received = %d\n",e,received);    
        return -1;    
    }       


    e = libusb_release_interface(handle, 1);    

    libusb_close(handle);    
    libusb_exit(ctx);    

    printf("\n");    
    return 0;    
}    
