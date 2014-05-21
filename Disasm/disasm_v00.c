#include "disasm_v00.h"
#include "disasm_fo_lib.h"
#include "disasm_analyzer_lib.h"
#include "disasm_print_lib.h"

int main(int argc, const char * const argv[])
{
    // Get text size and data size from read file
    FileData filedata = {0, 0, NULL};
    if ( fo_get_filedata(argv[1], &filedata) != OK )
    {
        return 1;
    }

    // Create Analyzer object from file data.
    // filedata.p_data will point NULL in this function.
    analy_new(&filedata);

    int textdata = 0x0;
    DivideData divided_data;
    // Start disassemble
    while ( (textdata = analy_get_textdata()) != EOF )
    {
        print_reset_strs();

        // Set print address
        print_set_address(analy_get_regval(PC) - 2);
        print_set_binary(textdata);

        // divide textdata into each region.
        analy_divide_2byte_textdata(textdata, &divided_data);

        switch ( divided_data.first_6bit )
        {
            case F6_MOV:
                analy_process_mov(&divided_data);
                break;
            case F6_TRAP:
                //
                analy_process_trap(&divided_data);
                break;
            default:
                //
                break;
        }
    }

    return 0;
}


