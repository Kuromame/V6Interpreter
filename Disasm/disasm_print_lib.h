#ifndef _DISASM_PRINT_LIB
#define _DISASM_PRINT_LIB

// create function name
//#define print_set_mnemonic(type) print_set_mnemonic_##type

#if 0
// define function
#define SET_MNEMONIC_FUNC(type)                                     \
    int print_set_mnemonic(type)(char * format, type data)          \
    {                                                               \
        char tmp_str[10] = {};                                      \
                                                                    \
        snprintf(tmp_str, sizeof(tmp_str), format, data);           \
        strncat(mnemonic_str, tmp_str, sizeof(tmp_str));            \
        strncat(mnemonic_str, " ", 2);                              \
        return OK;                                                  \
    }                                                               

// define function
#define SET_MNEMONIC_FUNC_2(type)                                   \
    int print_set_mnemonic(char * format, int data_num, ...)        \
    {                                                               \
        char tmp_str[10] = {};                                      \
        va_list ap;                                                 \
                                                                    \
        va_start(ap, data_num);                                     \
                                                                    \
        if ( data_num == 1 )                                        \
        {                                                           \
            snprintf(tmp_str, sizeof(tmp_str), format,              \
                     va_arg(ap, int));                              \
        }                                                           \
        else if ( data_num == 2 )                                   \
        {                                                           \
            int arg1 = va_arg(ap, int);                             \
            int arg2 = va_arg(ap, int);                             \
            snprintf(tmp_str, sizeof(tmp_str), format,              \
                    arg1, arg2);                                    \
        }                                                           \
        else                                                        \
        {                                                           \
            return NG;                                              \
        }                                                           \
        strncat(mnemonic_str, tmp_str, sizeof(tmp_str));            \
        strncat(mnemonic_str, " ", 2);                              \
                                                                    \
        va_end(ap);                                                 \
        return OK;                                                  \
    }                                                               
#endif

extern int print_reset_strs(void);
extern int print_set_address(uint16_t address);
extern char * print_get_address();
extern int print_set_binary(uint16_t binary);
extern char * print_get_binary();
extern int print_set_mnemonic_str(char * mnemonic);
//extern int print_set_mnemonic_uint8_t(char * format, uint8_t data);
//extern int print_set_mnemonic_uint16_t(char * format, uint16_t data);
extern int print_set_mnemonic(char * format, int data_num, ...);
extern char * print_get_mnemonic();


#endif

