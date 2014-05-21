#ifndef _DISASM_ANALYZER_LIB
#define _DISASM_ANALYZER_LIB

#define REGISTER_NUM (8)        // reg0 ~ reg7

#define R0 (0)
#define R1 (1)
#define R2 (2)
#define R3 (3)
#define R4 (4)
#define R5 (5)
#define SP (6)
#define PC (7)

// Exe data
typedef struct exedata
{
    int text_size;
    int data_size;
    uint8_t * p_data;
} ExeData;

// Divided text data
typedef struct dividedata
{
    uint8_t first_6bit;
    uint8_t second_6bit;
    uint8_t third_6bit;
} DivideData;

// Divided reg data
typedef struct mode_and_reg_data
{
    uint8_t regmode;
    uint8_t regnum;
} ModeAndRegData;

// reg data of ss and dd region
typedef struct mode_and_reg_data_pair
{
    ModeAndRegData ss_region;
    ModeAndRegData dd_region;
} ModeAndRegDataPair;


extern int analy_new(void * data);
extern int analy_get_regval(uint8_t regnum);
extern void analy_chg_regval(uint8_t regnum, int diffval);
extern void analy_set_regval(uint8_t regnum, int setval);
extern int analy_get_textdata(void);
extern uint8_t * analy_get_textposition(int adr);
extern int analy_write_2byte_to_data(uint16_t data_adr, uint16_t new_data);
extern int analy_divide_2byte_textdata(int textdata, DivideData * p_data);
extern int analy_process_mov(DivideData * p_data);
extern int analy_process_trap(DivideData * p_data);

#endif
