#ifndef _DISASM_FO_LIB
#define _DISASM_FO_LIB

#define HEADER_SIZE (0x10)
#define HEADER_WSIZE (8)
#define TEXTSIZE_POS (2)
#define DATASIZE_POS (3)

// File info struct (used in library)
typedef struct fileinfo
{
    FILE * p_file;
    uint8_t header[HEADER_WSIZE];
} FileInfo;

// File data struct
typedef struct filedata
{
    int text_size;
    int data_size;
    uint8_t * p_data;
} FileData;

extern int fo_get_filedata(const char * const open_filename, FileData * filedata);

#endif
