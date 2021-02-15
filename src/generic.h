
#define NVALS(A, name)                                  \
    GrB_Index name; _TRY(GrB_Matrix_nvals(&name, A))

#define SETE(C, x, ...)                                                 \
    _TRY(                                                               \
         _Generic((C),                                                  \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), GLF_(, GrB, Vector, setElement)),               \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), GLF_(, GrB, Matrix, setElement))                \
                  (C, x, __VA_ARGS__)))                                 \

#define GETE(x, C, ...)                                                 \
    _TRY(                                                               \
         _Generic((C),                                                  \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), GLF_(*, GrB, Vector, extractElement)),          \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), GLF_(*, GrB, Matrix, extractElement))           \
                  (x, C, __VA_ARGS__)))                                 \

#define EXISTS(e, x, C, ...)                                            \
    { GrB_Info info =  _Generic((C),                                    \
                           GrB_Vector :                                 \
                           _Generic                                     \
                           ((x), GLF_(*, GrB, Vector, extractElement)), \
                           GrB_Matrix :                                 \
                           _Generic                                     \
                           ((x), GLF_(*, GrB, Matrix, extractElement))  \
                           (x, C, __VA_ARGS__));                        \
        if (info == GrB_NO_VALUE)                                       \
            e = false;                                                  \
        else                                                            \
            e = true;                                                   \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            _CATCH (info) ;                                             \
    }                                                                   \

#define AXB(C, A, B, ...)                                   \
    _mxm_(C, A, B, (_glaph_Matrix_op_kwargs){__VA_ARGS__})

DEFKWARGS(print, int level);

#define _PRINTER_(T)                                                    \
    void _ ## T ## _PRINT_(GrB_ ## T A, _glaph_print_kwargs kwargs)  {  \
        _KWARG(int, level, 2);                                          \
        _TRY(GxB_print(A, level));                                      \
}

_PRINTER_(Matrix);
_PRINTER_(Vector);
_PRINTER_(Semiring);

#define PRINT(C, ...)                                           \
    _Generic(                                                   \
             (C),                                               \
             GrB_Matrix: _Matrix_PRINT_,                        \
             GrB_Vector: _Vector_PRINT_,                        \
             GrB_Semiring: _Semiring_PRINT_)                    \
    (C, (_glaph_print_kwargs){__VA_ARGS__});
