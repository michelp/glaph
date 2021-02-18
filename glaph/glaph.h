
#define GL_CATCH(info) {                                               \
        printf("Uncaught GraphBLAS error: %u\n", info); exit(1);       \
    }

#define GL_TRY(GrB_method) { GrB_Info info = GrB_method ;              \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))           \
            GL_CATCH (info) ;                                          \
    }

#define _GL_SNAME(T, name)                                             \
    _GL_ ## T ## _ ## name ## _kwargs

#define _GL_STRUCT(T, name, ...)                                       \
    typedef struct {__VA_ARGS__;} _GL_SNAME(T, name)

#define _GL_FNAME(T, name)                                             \
    _GL_ ## T ## _ ## name ## _func

#define _GL_FUNC(T, name, S, sname, ...)                               \
    static inline void _GL_FNAME(T, name)                              \
        (__VA_ARGS__ __VA_OPT__(,) _GL_SNAME(S, sname) kwargs)

#define _GL_KWARG(T, m, d)                      \
    T m = kwargs.m ? kwargs.m : (d)

_GL_STRUCT(GrB, init, GrB_Mode mode);

_GL_FUNC(GrB, init, GrB, init) {
    _GL_KWARG(GrB_Mode, mode, GrB_NONBLOCKING);
    GL_TRY(GrB_init(mode));
}

#define _GL_GENERIC(C, M, V, S)                                         \
    _Generic((C),                                                       \
             GrB_Matrix : M,                                            \
             GrB_Vector : V,                                            \
             GxB_Scalar : S)

#define _GL_GENERIC_OP(x, p, P, T, F)                       			\
	_Generic( (x), _GL_(p, P, T, F))

#define GL_INIT(...)                                                   \
    _GL_FNAME(GrB, init)((_GL_SNAME(GrB, init)){__VA_ARGS__})

#define GL_FINALIZE()                                                  \
    GrB_finalize();

#define GL_FOR(i, s, e)                                                \
    for(GrB_Index (i) = (s); (e); (i)++)

#define GL_FREE(...)

#define GL_FORI(I, A)                                                  \
    GrB_Index kn;                                                      \
    GrB_Index *ks;                                                     \
    GL_TRY (GrB_Matrix_nrows (&kn, A)) ;                               \
    ks = malloc (kn * sizeof (GrB_Index)) ;                            \
    GL_TRY (GrB_Matrix_extractTuples (ks, NULL, NULL, &kn, A)) ;       \
    for (GrB_Index ki_ = 0, I = ks[0]; ki_ < kn; ki_++, I = ks[ki_])

#define _GL_(p, prefix, T, func)                                       \
    const bool       p : prefix ## _ ## T ## _ ## func ## _BOOL   ,    \
          bool       p : prefix ## _ ## T ## _ ## func ## _BOOL   ,    \
    const int8_t     p : prefix ## _ ## T ## _ ## func ## _INT8   ,    \
          int8_t     p : prefix ## _ ## T ## _ ## func ## _INT8   ,    \
    const int16_t    p : prefix ## _ ## T ## _ ## func ## _INT16  ,    \
          int16_t    p : prefix ## _ ## T ## _ ## func ## _INT16  ,    \
    const int32_t    p : prefix ## _ ## T ## _ ## func ## _INT32  ,    \
          int32_t    p : prefix ## _ ## T ## _ ## func ## _INT32  ,    \
    const int64_t    p : prefix ## _ ## T ## _ ## func ## _INT64  ,    \
          int64_t    p : prefix ## _ ## T ## _ ## func ## _INT64  ,    \
    const uint8_t    p : prefix ## _ ## T ## _ ## func ## _UINT8  ,    \
          uint8_t    p : prefix ## _ ## T ## _ ## func ## _UINT8  ,    \
    const uint16_t   p : prefix ## _ ## T ## _ ## func ## _UINT16 ,    \
          uint16_t   p : prefix ## _ ## T ## _ ## func ## _UINT16 ,    \
    const uint32_t   p : prefix ## _ ## T ## _ ## func ## _UINT32 ,    \
          uint32_t   p : prefix ## _ ## T ## _ ## func ## _UINT32 ,    \
    const uint64_t   p : prefix ## _ ## T ## _ ## func ## _UINT64 ,    \
          uint64_t   p : prefix ## _ ## T ## _ ## func ## _UINT64 ,    \
    const float      p : prefix ## _ ## T ## _ ## func ## _FP32   ,    \
          float      p : prefix ## _ ## T ## _ ## func ## _FP32   ,    \
    const double     p : prefix ## _ ## T ## _ ## func ## _FP64   ,    \
          double     p : prefix ## _ ## T ## _ ## func ## _FP64   ,    \
    const GxB_FC32_t p : GxB    ## _ ## T ## _ ## func ## _FC32   ,    \
          GxB_FC32_t p : GxB    ## _ ## T ## _ ## func ## _FC32   ,    \
    const GxB_FC64_t p : GxB    ## _ ## T ## _ ## func ## _FC64   ,    \
          GxB_FC64_t p : GxB    ## _ ## T ## _ ## func ## _FC64   ,    \
    const void       * : prefix ## _ ## T ## _ ## func ## _UDT    ,    \
          void       * : prefix ## _ ## T ## _ ## func ## _UDT

#include "matrix.h"
#include "generic.h"
