#include "disasm_v00.h"
#include "disasm_print_lib.h"

static char address_str[10] = {};
static char binary_str[50] = {};
static char mnemonic_str[50] = {};

int print_reset_strs(void)
{
    memset(address_str, 0, sizeof(address_str));
    memset(binary_str, 0, sizeof(binary_str));
    memset(mnemonic_str, 0, sizeof(mnemonic_str));

    return OK;
}

int print_set_address(uint16_t address)
{
    snprintf(address_str, sizeof(address_str), "%04x", address);
    return OK;
}

char * print_get_address()
{
    return address_str;
}

int print_set_binary(uint16_t binary)
{
    char tmp_str[10] = {};

    snprintf(tmp_str, sizeof(tmp_str), "%04x ", binary);
    strncat(binary_str, tmp_str, sizeof(tmp_str));
    return OK;
}

char * print_get_binary()
{
    return binary_str;
}

int print_set_mnemonic_str(char * mnemonic)
{
    strncat(mnemonic_str, mnemonic, 10);
    strncat(mnemonic_str, " ", 2);
    return OK;
}

//SET_MNEMONIC_FUNC(uint8_t)
//SET_MNEMONIC_FUNC(uint16_t)

//SET_MNEMONIC_FUNC_2(uint16_t)

    int print_set_mnemonic(char * format, int data_num, ...)
    {                                                               
        char tmp_str[10] = {};                                     
        va_list ap;                                                
                                                                    
        va_start(ap, data_num);                                     
                                                                    
        if ( data_num == 1 )                                        
        {                                                           
            snprintf(tmp_str, sizeof(tmp_str), format,              
                     va_arg(ap, int));                              
        }                                                           
        else if ( data_num == 2 )                                   
        {                                                           
            int arg1 = va_arg(ap, int);                             
            int arg2 = va_arg(ap, int);                             
            snprintf(tmp_str, sizeof(tmp_str), format,              
                    arg1, arg2);                                    
        }                                                           
        else                                                        
        {                                                           
            return NG;                                              
        }                                                           
        strncat(mnemonic_str, tmp_str, sizeof(tmp_str));            
        strncat(mnemonic_str, " ", 2);                              
                                                                    
        va_end(ap);                                                 
        return OK;                                                  
    }                                                               


char * print_get_mnemonic()
{
    return mnemonic_str;
}


