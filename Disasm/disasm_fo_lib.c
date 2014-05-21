#include "disasm_v00.h"
#include "disasm_fo_lib.h"

static FileInfo read_fileinfo = {NULL, {"\0"}};

static uint16_t s_read_word(void)
{
    uint8_t bytedata1 = fgetc(read_fileinfo.p_file);
    uint8_t bytedata2 = fgetc(read_fileinfo.p_file);

    return ((bytedata2 << 8) & 0xff00) | (bytedata1 & 0x00ff); 
}

static int s_extract_headerdata(void)
{
    int pc = 0x0;

    // Read header part
    for ( pc = 0x0; pc < 0x10; pc += 2 )
    {
        read_fileinfo.header[pc/2] = s_read_word();
    }

    return OK;
}

// Open the read file
static int s_fileopen(const char * const open_filename)
{
    read_fileinfo.p_file = fopen(open_filename, "rb");
    if ( read_fileinfo.p_file == NULL )
    {
        printf("Error: failed to open read file.\n");
        return NG;
    } 
    return OK;
}

// Close the read file
static int s_fileclose(void)
{
    if ( fclose(read_fileinfo.p_file) == EOF )
    {
        printf("Error: failed to close the read file\n");
        return NG;
    }
    return OK;
}


// Get file data (text size, data size, data pointer)
int fo_get_filedata(const char * const open_filename, FileData * p_filedata)
{
    int filedata_size = 0;

    if ( s_fileopen(open_filename) != OK)
    {
        return NG;
    }

    // extract header data
    s_extract_headerdata();

    // To fit array num, add -1
    p_filedata->text_size = read_fileinfo.header[TEXTSIZE_POS - 1];
    p_filedata->data_size = read_fileinfo.header[DATASIZE_POS - 1];
    
    // Read data area
    filedata_size = p_filedata->text_size + p_filedata->data_size;
    p_filedata->p_data = (uint8_t *)malloc(filedata_size);
    if ( p_filedata->p_data == NULL )
    {
        printf("Error: failed to malloc memory.\n");
        return NG;
    }

    // get text + data area. file data is read from next to header.
    // TODO: file shizishi no ichi wo ishiki shinakute sumu youni syuusei suru.
    // TODO: ima ha, header made saki ni yondeiru node tamatama header no ato kara yometeiru.
    if ( fread(p_filedata->p_data, sizeof(uint8_t), filedata_size, read_fileinfo.p_file) < 0 )
    {
        printf("Error: failed to read file data.\n");
        return NG;
    }

    if ( s_fileclose() != OK )
    {
        return NG;
    }

    return OK;
}


