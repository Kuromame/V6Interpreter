#ifndef _DISASM_V00
#define _DISASM_V00

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

//#define INTRP_MODE

// bool
#define OK (1)
#define NG (0)

// Opecode (first 6bit)
#define F6_MOV  (001)
#define F6_TRAP (010)

#endif
