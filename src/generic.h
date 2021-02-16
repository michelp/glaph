
#define GL_NVALS(A, name)                                  \
    GrB_Index name; GL_TRY(GrB_Matrix_nvals(&name, A))

#define GL_ASSIGN(C, x, ...)                                            \
    GL_TRY(                                                            \
            _Generic((C),                                               \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), _GL_(, GrB, Vector, setElement)),               \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), _GL_(, GrB, Matrix, setElement))                \
                  (C, x, __VA_ARGS__)))                                 \

#define GL_EXTRACT(x, C, ...)                                           \
    GL_TRY(                                                            \
         _Generic((C),                                                  \
                  GrB_Vector :                                          \
                  _Generic                                              \
                  ((x), _GL_(*, GrB, Vector, extractElement)),          \
                  GrB_Matrix :                                          \
                  _Generic                                              \
                  ((x), _GL_(*, GrB, Matrix, extractElement))           \
                  (x, C, __VA_ARGS__)))                                 \

#define GL_EXISTS(e, x, C, ...)                                         \
    { GrB_Info info =  _Generic((C),                                    \
                           GrB_Vector :                                 \
                           _Generic                                     \
                           ((x), _GL_(*, GrB, Vector, extractElement)), \
                           GrB_Matrix :                                 \
                           _Generic                                     \
                           ((x), _GL_(*, GrB, Matrix, extractElement))  \
                           (x, C, __VA_ARGS__));                        \
        if (info == GrB_NO_VALUE)                                       \
            e = false;                                                  \
        else                                                            \
            e = true;                                                   \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            GL_CATCH (info) ;                                           \
    }                                                                   \

#define GL_AXB(C, A, B, ...)                                            \
    _GL_GrB_mxm_func(C, A, B, (_GL_GrB_mxm_kwargs){__VA_ARGS__})

_GL_KWARGS_STRUCT(, print, int level);

#define _GL_PRINTER(T)                                                  \
    static inline void _ ## T ## _PRINT_(GrB_ ## T A, _GL__print_kwargs kwargs)  { \
        _GL_KWARG(int, level, 2);                                       \
        GL_TRY(GxB_print(A, level));                                    \
    }

_GL_PRINTER(Matrix);
_GL_PRINTER(Vector);
_GL_PRINTER(Semiring);

#define GL_PRINT(C, ...)                                        \
    _Generic(                                                   \
             (C),                                               \
             GrB_Matrix: _Matrix_PRINT_,                        \
             GrB_Vector: _Vector_PRINT_,                        \
             GrB_Semiring: _Semiring_PRINT_)                    \
    (C, (_GL__print_kwargs){__VA_ARGS__});
