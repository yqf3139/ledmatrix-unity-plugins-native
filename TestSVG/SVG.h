#include <windows.h>
#include <mmsystem.h>
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>

#define _DLLExport __declspec (dllexport)

#define MAXPATH 1<<10
#define MAXPOINT 1<<16
#define NANOSVG_IMPLEMENTATION

typedef void(__stdcall *CPPCallback)(int tick);

extern "C" _DLLExport long long dlltest();

extern "C" _DLLExport void construct();

extern "C" _DLLExport void deconstruct();

extern "C" _DLLExport int parse(char *);

extern "C" _DLLExport int *getColorbuf();

extern "C" _DLLExport int *getPathbuf();

extern "C" _DLLExport float *getPointbuf();
