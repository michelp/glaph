
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


_GL_STRUCT(GrB, AXB, GrB_Matrix mask; GrB_Vector vmask; GrB_BinaryOp accum;
           GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _MOPKWARGS()                                                    \
    _GL_KWARG(GrB_Matrix, mask, NULL);                                  \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);

_GL_FUNC(GrB, mxm, GrB, AXB, GrB_Matrix C, GrB_Matrix A, GrB_Matrix B) {
    _MOPKWARGS()
    GL_TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}

#define _VOPKWARGS()                                                    \
    _GL_KWARG(GrB_Vector, vmask, NULL);                                 \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);                        \

_GL_FUNC(GrB, mxv, GrB, AXB, GrB_Vector C, GrB_Matrix A, GrB_Vector B)  {
    _VOPKWARGS()
    GL_TRY(GrB_mxv(C, vmask, accum, semiring, A, B, descriptor));
}

_GL_FUNC(GrB, vxm, GrB, AXB, GrB_Vector C, GrB_Vector A, GrB_Matrix B)  {
    _VOPKWARGS()
    GL_TRY(GrB_vxm(C, vmask, accum, semiring, A, B, descriptor));
}

#define GL_MMREAD(...)

#define GL_IDENT(A, n, v, ...)                                          \
    _Matrix_new_(&A, (_GL_SNAME(GrB_Matrix, new))                       \
                 {.nrows=n, .ncols=n, __VA_ARGS__});                    \
    for (int A ## _ ## Si = 0; A ## _ ## Si < n; A ## _ ## Si++)        \
        GL_TRY(GrB_Matrix_setElement(S, v, A ## _ ## Si, A ## _ ## Si))

_GL_STRUCT(GrB, new,
           GrB_Index nI; GrB_Index nJ; GrB_Type type);

_GL_FUNC(GrB_Matrix, new, GrB, new, GrB_Matrix *A) {
    _GL_KWARG(GrB_Index, nI, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Index, nJ, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Matrix_new(A, type, nI, nJ));
}

_GL_FUNC(GrB_Vector, new, GrB, new, GrB_Vector *A) {
    _GL_KWARG(GrB_Index, nI, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Vector_new(A, type, nI));
}

_GL_FUNC(GxB_Scalar, new, GrB, new, GxB_Scalar *A) {
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GxB_Scalar_new(A, type));
}

#define GL_NEW(A, ...)													\
	_GL_GENERIC((A),													\
				_GL_FNAME(GrB_Matrix, new),								\
				_GL_FNAME(GrB_Vector, new),								\
				_GL_FNAME(GxB_Scalar, new)								\
				) 														\
    (&A, (_GL_SNAME(GrB, new)){__VA_ARGS__})

#define GL_NI(n, A)								\
	GL_TRY(_GL_GENERIC((A),						\
					   GrB_Matrix_nrows,		\
					   GrB_Vector_size(&n, A)	\
					   GrB_Vector_size(&n, A)	\
					   )(&n, A))

#define GL_NJ(n, A)								\
	GL_TRY( GrB_Matrix_ncols(&n, A)

#define GL_NV(name, A)													\
    _GL_GENERIC((A),                                                    \
                GrB_Matrix_nvals,                                       \
                GrB_Vector_nvals,                                       \
                GxB_Scalar_nvals                                        \
                )(&name, A)

#define GL_ASSIGN(C, A, ...)

#define GL_EXTRACT(C, A, ...)

#define GL_SELECT(C, op, ...)

#define GL_SET(C, x, ...)                                               \
    GL_TRY(                                                             \
           _GL_GENERIC                                                  \
           ((C),                                                        \
            _GL_GENERIC_OP(x,, GrB, Matrix, setElement),                \
            _GL_GENERIC_OP(x,, GrB, Vector, setElement),                \
            _GL_GENERIC_OP(x,, GxB, Scalar, setElement))                \
           ((C), (x), __VA_ARGS__))

#define GL_GET(x, C, ...) { GrB_Info info =                             \
            _GL_GENERIC                                                 \
            ((C),                                                       \
             _GL_GENERIC_OP((x), *, GrB, Matrix, extractElement),       \
             _GL_GENERIC_OP((x), *, GrB, Vector, extractElement),       \
             _GL_GENERIC_OP((x), *, GxB, Scalar, extractElement))       \
            (x, C, __VA_ARGS__);                                        \
        if (info != GrB_SUCCESS)                                        \
            GL_CATCH (info) ;                                           \
    }

#define GL_EXISTS(e, x, C, ...) { GrB_Info info =                       \
        _GL_GENERIC                                                     \
        ((C),                                                           \
         _GL_GENERIC_OP((x), *, GrB, Matrix, extractElement),           \
         _GL_GENERIC_OP((x), *, GrB, Vector, extractElement),           \
         _GL_GENERIC_OP((x), *, GxB, Scalar, extractElement))           \
        (x, C, __VA_ARGS__);                                            \
        if (info == GrB_NO_VALUE)                                       \
            (e) = false;                                                \
        else                                                            \
            (e) = true;                                                 \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            GL_CATCH (info) ;                                           \
    }

#define GL_UNION (C, A, B, ...)
#define GL_INTERSECTION (C, A, B, ...)

#define GL_AXB(C, A, B, ...)                                            \
    _GL_GENERIC ( (C),                                                  \
                  _GL_FNAME(GrB, mxm),                                  \
                  _GL_GENERIC( (A),                                     \
                               _GL_FNAME(GrB, mxv),                     \
                               _GL_FNAME(GrB, vxm),                     \
                               _GL_FNAME(GrB, mxm)                      \
                               ),                                       \
                  _GL_FNAME(GrB, mxm)                                   \
                  )                                                     \
    (C, A, B, (_GL_SNAME(GrB, AXB)){__VA_ARGS__})

_GL_STRUCT(GrB, print, int level);

#define _GL_PRINTER(T, name)                                            \
    _GL_FUNC(T, name, GrB, print, T A) {                                \
        _GL_KWARG(int, level, 2);                                       \
        GL_TRY(GxB_print(A, level));                                    \
    }

_GL_PRINTER(GrB_Matrix, print);
_GL_PRINTER(GrB_Vector, print);
_GL_PRINTER(GxB_Scalar, print);

#define GL_PRINT(C, ...)                                                \
    _GL_GENERIC((C),                                                    \
                _GL_FNAME(GrB_Matrix, print),                           \
                _GL_FNAME(GrB_Vector, print),                           \
                _GL_FNAME(GxB_Scalar, print))                           \
    (C, (_GL_SNAME(GrB, print)){__VA_ARGS__})

#define GL_CLEAR(C)                                                     \
    _GL_GENERIC((C),                                                    \
                GrB_Matrix_clear,                                       \
                GrB_Vector_clear,                                       \
                GxB_Scalar_clear)(C)

