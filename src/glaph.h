#define _GF_CATCH(info) { printf("outch: %u\n", info); exit(1); }
#define _GF_TRY(GrB_method) { GrB_Info info = GrB_method ;              \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))         \
            _GF_CATCH (info) ; }                                        \
        
#define _GF_DEFKWARGS(N, ...) typedef struct {__VA_ARGS__;} _GF_ ## N ## _kwargs
#define _GF_KWARG(T, m, d) T m = kwargs.m ? kwargs.m : d

#define GF_INIT() { printf("glaph 0.1\n"); GrB_init(GrB_NONBLOCKING); }
#define GF_FINALIZE() {printf("Byee\n"); GrB_finalize();}
#define GF_FOR(i, s, e) for(GrB_Index i = s; i < e; i++)
#define GF_FREE(...)

#define _GF_(p, prefix, T, func)                                      \
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
