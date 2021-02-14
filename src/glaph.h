#include <GraphBLAS.h>

#define _CATCH(info) { printf("outch: %u\n", info); exit(1); }
#define _TRY(GrB_method) { GrB_Info info = GrB_method ;              \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))         \
            _CATCH (info) ; }                                        \
        
#define _KWARG(T, m, d) T m = kwargs.m ? kwargs.m : d

#define INIT() { printf("glaph 0.1\n"); GrB_init(GrB_NONBLOCKING); }
#define FINALIZE() {printf("Byee glaph about it\n"); GrB_finalize();}

// Print --------------------------------------------------------------------

typedef struct {
    int level;
} _glaph_print_kwargs;

void _print_(GrB_Matrix A, _glaph_print_kwargs kwargs)  {
    _KWARG(int, level, 2);
    _TRY(GxB_print(A, level));
}

#define PRINT(C, ...) _print_(C, (_glaph_print_kwargs){__VA_ARGS__});

#include "matrix.h"
#include "vector.h"
#include "generic.h"
