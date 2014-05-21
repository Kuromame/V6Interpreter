#include "disasm_v00.h"
#include "disasm_analyzer_lib.h"
#include "disasm_print_lib.h"

static uint16_t regs[REGISTER_NUM] = {};
static ExeData exedata = {0, 0, NULL};

int analy_new(void * data)
{
    // Set exe file data
    exedata = (*(ExeData *)data);
    ((ExeData *)data)->p_data = NULL;

    // Initialize register value
    int counter = 0;
    for ( counter = 0; counter < REGISTER_NUM; counter++ )
    {
        regs[counter] = 0;
    }

    return OK;
}

// Return register value
int analy_get_regval(uint8_t regnum)
{
    return regs[regnum];
}

// Change register value
void analy_chg_regval(uint8_t regnum, int diffval)
{
    regs[regnum] += diffval;
}

// Set register value
void analy_set_regval(uint8_t regnum, int setval)
{
    regs[regnum] = setval;
}

int analy_get_textdata(void)
{
    // If text region is finished, return end flag (-1).
    if ( analy_get_regval(PC) >= exedata.text_size )
    {
        return EOF;
    }

    uint8_t first_byte = exedata.p_data[analy_get_regval(PC)];
    uint8_t second_byte = exedata.p_data[analy_get_regval(PC) + 1];
    analy_chg_regval(PC, 2);

    // Little endian
    return ((second_byte << 8) & 0x0000ff00) | (first_byte & 0x000000ff); 
}

uint8_t * analy_get_textposition(int adr)
{
    return &exedata.p_data[adr];
}

// Override data region by 2byte data
int analy_write_2byte_to_data(uint16_t data_adr, uint16_t new_data)
{
    exedata.p_data[data_adr + 0] = new_data & 0x00ff;
    exedata.p_data[data_adr + 1] = (new_data >> 8) & 0x00ff;

    return OK;
}

int analy_divide_2byte_textdata(int textdata, DivideData * p_data)
{
    uint8_t divide_result[3];
    int ctr = 0;

    for ( ctr = 0; ctr < 3; ctr++ )
    {
        divide_result[ctr] = ( textdata >> (ctr * 6) ) & 0x0000003f;
    }

    p_data->first_6bit = divide_result[2];
    p_data->second_6bit = divide_result[1];
    p_data->third_6bit = divide_result[0];

    return OK;
}

int analy_divide_regdata_pair(DivideData * p_in_regdata, ModeAndRegDataPair * p_outdata)
{
#if 1
    ModeAndRegData ss_data_tmp, dd_data_tmp;
    ModeAndRegData regdata_pair[2] = {ss_data_tmp, dd_data_tmp};
    uint8_t divide_data_pair[2] = {p_in_regdata->second_6bit, p_in_regdata->third_6bit};

    int i = 0;
    for ( i = 0; i < 2; i++ )
    {
        regdata_pair[i].regmode = (divide_data_pair[i] >> 3) & 0x07;
        regdata_pair[i].regnum = divide_data_pair[i] & 0x07;

        // Set regdata_pair[i] to p_outdata
        *((ModeAndRegData *)p_outdata + i) = regdata_pair[i];
    }

#else
    // Set ss data
    p_outdata->ss_region.regmode = (p_in_regdata->second_6bit >> 3) & 0x07;
    p_outdata->ss_region.regnum = p_in_regdata->second_6bit & 0x07;

    // Seg dd data
    p_outdata->dd_region.regmode = (p_in_regdata->third_6bit >> 3) & 0x07;
    p_outdata->dd_region.regnum = p_in_regdata->third_6bit & 0x07;
#endif

    return OK;
}

int analy_process_mov(DivideData * p_data)
{
    ModeAndRegDataPair regdata_pair;
#ifdef INTRP_MODE
    uint16_t ss_value = 0;
#endif

    // process SS region
    analy_divide_regdata_pair(p_data, &regdata_pair);    

#ifndef INTRP_MODE
    print_set_mnemonic_str("mov");
#endif
    
    // analyze ss region
    if ( regdata_pair.ss_region.regnum == 07 )
    {
        int textdata = analy_get_textdata();
        
        switch ( regdata_pair.ss_region.regmode )
        {
            case 02:
#ifndef INTRP_MODE
                print_set_binary(textdata);
                print_set_mnemonic("$%#x", 1, textdata);
                //print_set_mnemonic_uint16_t("$%#x", textdata);
#else
                ss_value = textdata;        
#endif
                break;
            case 03:
                break;
            case 06:
                break;
            case 07:
                break;
            default:
                break;
        }
    }
    else
    {
        switch ( regdata_pair.ss_region.regmode )
        {
            case 00:
                break;
            case 01:
                break;
            case 02:
                break;
            case 03:
                break;
            case 04:
                break;
            case 05:
                break;
            case 06:
                break;
            case 07:
                break;
            default:
                break;
        }

    }

    // analyze dd region
    if ( regdata_pair.dd_region.regnum == 07 )
    {
        switch ( regdata_pair.dd_region.regmode )
        {
            case 02:
                // DD(destination) can not be a immediate value.
                break;
            case 03:
                break;
            case 06:
                break;
            case 07:
                break;
            default:
                break;
        }
    }
    else
    {
        int textdata = 0;
        switch ( regdata_pair.dd_region.regmode )
        {
            case 00:
#ifndef INTRP_MODE
                //print_set_mnemonic_uint8_t("r%o", regdata_pair.dd_region.regnum);
                print_set_mnemonic("r%o", 1, regdata_pair.dd_region.regnum);
#else
                analy_set_regval(regdata_pair.dd_region.regnum, ss_value);
#endif
                break;
            case 01:
#ifndef INTRP_MODE
                //print_set_mnemonic_uint8_t("(r%o)", regdata_pair.dd_region.regnum);
                print_set_mnemonic("(r%o)", 1, regdata_pair.dd_region.regnum);
#else
                analy_write_2byte_to_data(analy_get_regval(regdata_pair.dd_region.regnum), ss_value);
#endif
                break;
            case 02:
                break;
            case 03:
                break;
            case 04:
                break;
            case 05:
                break;
            case 06:
#ifndef INTRP_MODE
                textdata = analy_get_textdata();
                print_set_mnemonic("%x(r%o)", 2, textdata, regdata_pair.dd_region.regnum);
                //print_set_mnemonic_test("%x(r%o)", 2, regdata_pair.dd_region.regnum, textdata);
                //printf("textdata: %d\n", textdata);
                print_set_binary(textdata);
#else
#endif
                break;
            case 07:
                break;
            default:
                break;
        }

    }

#ifndef INTRP_MODE
    printf("%s: %-15s%s\n", print_get_address(), print_get_binary(), print_get_mnemonic());
#endif
    return OK;
}

int analy_process_trap(DivideData * p_data)
{
    switch ( p_data->second_6bit )
    {
        case 044:
            // sys
#ifndef INTRP_MODE
            print_set_mnemonic_str("sys");
            //print_set_mnemonic_uint8_t("%x", p_data->third_6bit);
            print_set_mnemonic("%x", 1, p_data->third_6bit);
#endif
            switch ( p_data->third_6bit )
            {
                case 01:
                    // exit
#ifndef INTRP_MODE
                    print_set_mnemonic_str("; exit");
#else
                    exit(analy_get_regval(R0));
#endif
                    break;
                case 04:
                    // write
#ifndef INTRP_MODE
                    {
                        uint16_t textdata = 0;

                        print_set_mnemonic_str("; write");
                        printf("%s: %-15s%s\n", print_get_address(), print_get_binary(), print_get_mnemonic());

                        textdata = analy_get_textdata();
                        print_reset_strs();
                        print_set_address(analy_get_regval(PC) - 2);
                        print_set_binary(textdata);

                        print_set_mnemonic_str("; arg");
                        printf("%s: %-15s%s\n", print_get_address(), print_get_binary(), print_get_mnemonic());

                        textdata = analy_get_textdata();
                        print_reset_strs();
                        print_set_address(analy_get_regval(PC) - 2);
                        print_set_binary(textdata);

                        print_set_mnemonic_str("; arg");
                    }
#else
                    {
                        int str_adr = analy_get_textdata();
                        int str_len = analy_get_textdata();

                        write(analy_get_regval(R0), analy_get_textposition(str_adr), str_len);
                    }
#endif
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

#ifndef INTRP_MODE
    printf("%s: %-15s%s\n", print_get_address(), print_get_binary(), print_get_mnemonic());
#endif
    return OK;
}


