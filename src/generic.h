
#define GF_NVALS(A, name)                                  \
    GrB_Index name; _GF_TRY(GrB_Matrix_nvals(&name, A))

#define GF_ASSIGN(C, x, ...)                                            \
    _GF_TRY(                                                            \
            _Generic((C),                                               \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), _GF_(, GrB, Vector, setElement)),               \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), _GF_(, GrB, Matrix, setElement))                \
                  (C, x, __VA_ARGS__)))                                 \

#define GF_EXTRACT(x, C, ...)                                           \
    _GF_TRY(                                                            \
         _Generic((C),                                                  \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), _GF_(*, GrB, Vector, extractElement)),          \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), _GF_(*, GrB, Matrix, extractElement))           \
                  (x, C, __VA_ARGS__)))                                 \

#define GF_EXISTS(e, x, C, ...)                                         \
    { GrB_Info info =  _Generic((C),                                    \
                           GrB_Vector :                                 \
                           _Generic                                     \
                           ((x), _GF_(*, GrB, Vector, extractElement)), \
                           GrB_Matrix :                                 \
                           _Generic                                     \
                           ((x), _GF_(*, GrB, Matrix, extractElement))  \
                           (x, C, __VA_ARGS__));                        \
        if (info == GrB_NO_VALUE)                                       \
            e = false;                                                  \
        else                                                            \
            e = true;                                                   \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            _GF_CATCH (info) ;                                          \
    }                                                                   \

#define GF_AXB(C, A, B, ...)                            \
    _mxm_(C, A, B, (_GF_Matrix_op_kwargs){__VA_ARGS__})

_GF_DEFKWARGS(print, int level);

#define _GF_PRINTER(T)                                                  \
static inline void _ ## T ## _PRINT_(GrB_ ## T A, _GF_print_kwargs kwargs)  { \
    _GF_KWARG(int, level, 2);                                       \
    _GF_TRY(GxB_print(A, level));                                   \
}

_GF_PRINTER(Matrix);
_GF_PRINTER(Vector);
_GF_PRINTER(Semiring);

#define GF_PRINT(C, ...)                                        \
    _Generic(                                                   \
             (C),                                               \
             GrB_Matrix: _Matrix_PRINT_,                        \
             GrB_Vector: _Vector_PRINT_,                        \
             GrB_Semiring: _Semiring_PRINT_)                    \
    (C, (_GF_print_kwargs){__VA_ARGS__});
