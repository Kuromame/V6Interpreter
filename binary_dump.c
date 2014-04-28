#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * const argv[])
{
    FILE * pReadFile = NULL;
    unsigned char * pStoreBuf = NULL;
    int    readChar = 0;
    int    dataCtr = 0;

    pReadFile = fopen(argv[1], "rb"); 
    pStoreBuf = (unsigned char * )malloc(sizeof(char));

    /* store all data into the buffer */
    while ( (readChar = fgetc(pReadFile)) != EOF )
    {
        dataCtr++;
        pStoreBuf = (unsigned char * )realloc(pStoreBuf, dataCtr);
        pStoreBuf[dataCtr - 1] = readChar;
    }

    /* dump all data */
    for ( int ctr = 0; ctr < dataCtr; ctr += 16 )
    {
        /* write the address */
        //printf();

        /* dump a line */
        /* hex dump */
        for ( int ctr2 = 0; ctr2 < 16; ctr2++ )
        {
            /* upper index of pStoreBuf is dataCtr - 1 */
            if ( (ctr + ctr2) <= (dataCtr - 1) )
            {
                printf("%02x ", pStoreBuf[ctr + ctr2]); 
            }
            else
            {
                printf("   ");
            }
        }

        /* char dump */
        for ( int ctr2 = 0; ctr2 < 16; ctr2++ )
        {
            /* upper index of pStoreBuf is dataCtr - 1 */
            if ( (ctr + ctr2) <= (dataCtr - 1) )
            {
                if ( pStoreBuf[ctr + ctr2] >= 0x21 && pStoreBuf[ctr + ctr2] <= 0x7e )
                {
                    printf("%c ", pStoreBuf[ctr + ctr2]); 
                }
                else
                {
                    printf(". ");
                }
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }

    free(pStoreBuf);

    printf("\n");
    fclose(pReadFile);

    return 0;
}
