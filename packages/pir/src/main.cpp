#include "pirlib2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void printUsage()
{
    printf("PIR-1 / PIR-4 Library Example.\n");
    printf("Copyright (c) 2014 Promixis, LLC\n\n");
    printf("pir usage:\n");
    printf("pir send PIR_SERIAL_OR_ALL CCF BITMASK REPEATS\n");
    printf("pir blink PIR_SERIAL_OR_ALL\n");
    printf("pir list\n");
    printf("pir learn PIR_SERIAL\n");
    printf("\nExample send from any attached PIR-1 or PIR-4:\n");
    printf("./pir_example send all \"0000 006E 0000 0022 0156 00A9 0014 0014 0014 0040 0014 0040 0014 0040 0014 0014 0014 0040 0014 0040 0014 0014 0014 0040 0014 0014 0014 0014 0014 0014 0014 0040 0014 0014 0014 0014 0014 0040 0014 0040 0014 0014 0014 0040 0014 0040 0014 0040 0014 0014 0014 0014 0014 0014 0014 0014 0014 0040 0014 0014 0014 0014 0014 0014 0014 0040 0014 0040 0014 0040 0014 05EF\" 1 2\n\n");
}


void learnCB(const char *serial, unsigned int modulation, const unsigned int *pulses, unsigned int pulseCount, void *userData)
{
    unsigned int i;
    printf("Learned:");
    
    /* 
    printf("0000 %04X 0000 %04X", modulation, pulseCount/2);
    for (i = 0; i < pulseCount; i++)
    {
        printf(" %04X", pulses[i]);
    }
    */
    
    printf("0000 %04X 0000 %04X", (int)(modulation * 2.1), pulseCount / 2);
    for (i = 1; i < pulseCount; i++)
    {
        printf(" %04X", (int)(pulses[i] * 0.15));
    }
    printf(" %04X", (int)(pulses[0] * 0.15));
    
    printf("\n");

}

void sendCB(const char *serial, unsigned char status, void *userData)
{
    printf("Something has been sent\n");
}

int main(int argc, char ** argv)
{


    if ( argc < 2 )
    {
        printUsage();
        return 0;
    }


    PIR_Settings s;
    memset(&s,0,sizeof(PIR_Settings));
    s.size = sizeof(PIR_Settings);
    s.rawLearnCallback = &learnCB;

    if ( pir_open(&s) != 0 )
    {
        printUsage();
        printf("Error Opening HID layer.");
        return -1;
    }

    bool ok = false;
    int res = -1;

    if ( strcmp(argv[1], "send" ) == 0 && argc == 6 )
    {
        const char * serial = argv[2];
        const char * ccf = argv[3];
        int bitmask = atoi( argv[4]);
        int repeats = atoi( argv[5]);

        if ( strcmp(serial, "all") == 0 )
        {
            serial = "";
        }

        res = pir_sendCCF(serial, ccf, bitmask, repeats);
        ok = true;
    }

    if ( strcmp(argv[1], "blink") == 0 && argc == 3 )
    {
        const char * serial = argv[2];
        if ( strcmp(serial, "all") == 0 )
        {
            printf("blink does not support \"all\"\n");
        }
        else
        {
            res = pir_blink(serial,5);
            ok = true;
        }
    }

    if ( strcmp(argv[1], "list") == 0 && argc == 2 )
    {
        char buffer[1024];
        pir_list1(buffer, 1024);
        printf("PIR-1: %s\n", buffer);
        pir_list4(buffer, 1024);
        printf("PIR-4: %s\n", buffer);
        ok = true;
        res = 0;
    }

    if ( strcmp(argv[1], "learn") == 0 && argc == 3 )
    {
        const char * serial = argv[2];
        if ( strcmp(serial, "all") == 0 )
        {
            printf("blink does not support \"all\"\n");
        }
        else
        {
            ok = true;

            printf("Serial: %s\n",serial);

            if ( pir_learn(serial) == 0)
            {
                printf("LEARNING...\n");
                printf("Type enter to exit:\n");
                getchar();
                res = pir_cancelLearn(serial);
            }
            else
            {
                printf("Could not enter learn mode\n");
            }
        }
    }

	pir_close();
	
    if ( !ok )
    {
        printUsage();
    }

    return res;
}
