#define _CATCH(info) { printf("outch: %u\n", info); exit(1); }
#define _TRY(GrB_method) { GrB_Info info = GrB_method ;              \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))         \
            _CATCH (info) ; }                                        \
        
#define DEFKWARGS(N, ...) typedef struct {__VA_ARGS__;} _glaph_ ## N ## _kwargs
#define _KWARG(T, m, d) T m = kwargs.m ? kwargs.m : d

#define INIT() { printf("glaph 0.1\n"); GrB_init(GrB_NONBLOCKING); }
#define FINALIZE() {printf("Byee\n"); GrB_finalize();}
#define FOR(i, s, e) for(GrB_Index i = s; i < e; i++)

#define FREE(...)

#define GLF_(p, prefix, T, func)                                 \
        const bool       p : prefix ## _ ## T ## _ ## func ## _BOOL   ,   \
              bool       p : prefix ## _ ## T ## _ ## func ## _BOOL   ,   \
        const int8_t     p : prefix ## _ ## T ## _ ## func ## _INT8   ,   \
              int8_t     p : prefix ## _ ## T ## _ ## func ## _INT8   ,   \
        const int16_t    p : prefix ## _ ## T ## _ ## func ## _INT16  ,   \
              int16_t    p : prefix ## _ ## T ## _ ## func ## _INT16  ,   \
        const int32_t    p : prefix ## _ ## T ## _ ## func ## _INT32  ,   \
              int32_t    p : prefix ## _ ## T ## _ ## func ## _INT32  ,   \
        const int64_t    p : prefix ## _ ## T ## _ ## func ## _INT64  ,   \
              int64_t    p : prefix ## _ ## T ## _ ## func ## _INT64  ,   \
        const uint8_t    p : prefix ## _ ## T ## _ ## func ## _UINT8  ,   \
              uint8_t    p : prefix ## _ ## T ## _ ## func ## _UINT8  ,   \
        const uint16_t   p : prefix ## _ ## T ## _ ## func ## _UINT16 ,   \
              uint16_t   p : prefix ## _ ## T ## _ ## func ## _UINT16 ,   \
        const uint32_t   p : prefix ## _ ## T ## _ ## func ## _UINT32 ,   \
              uint32_t   p : prefix ## _ ## T ## _ ## func ## _UINT32 ,   \
        const uint64_t   p : prefix ## _ ## T ## _ ## func ## _UINT64 ,   \
              uint64_t   p : prefix ## _ ## T ## _ ## func ## _UINT64 ,   \
        const float      p : prefix ## _ ## T ## _ ## func ## _FP32   ,   \
              float      p : prefix ## _ ## T ## _ ## func ## _FP32   ,   \
        const double     p : prefix ## _ ## T ## _ ## func ## _FP64   ,   \
              double     p : prefix ## _ ## T ## _ ## func ## _FP64   ,   \
        const GxB_FC32_t p : GxB    ## _ ## T ## _ ## func ## _FC32   ,   \
              GxB_FC32_t p : GxB    ## _ ## T ## _ ## func ## _FC32   ,   \
        const GxB_FC64_t p : GxB    ## _ ## T ## _ ## func ## _FC64   ,   \
              GxB_FC64_t p : GxB    ## _ ## T ## _ ## func ## _FC64   ,   \
        const void       * : prefix ## _ ## T ## _ ## func ## _UDT    ,   \
              void       * : prefix ## _ ## T ## _ ## func ## _UDT

#include "matrix.h"
#include "vector.h"
#include "scalar.h"
#include "generic.h"
