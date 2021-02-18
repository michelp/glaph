
#define GL_NVALS(A, name)                               \
    GrB_Index name; GL_TRY(GrB_Matrix_nvals(&name, A))

// (M)atrix (v)ector (s)calar

// ASSIGN(M, M)  Assign matrix to matrix
// ASSIGN(M, v, i) Assign vector to row, .desc=GrB_DESC_T0 for col assign
// ASSIGN(M, s, i, j) set element
// ASSIGN(v, v) Assign vector to vector
// ASSIGN(v, s, i) set element

#define _GL_GENERIC(C, M, V, S)                                         \
    _Generic((C),                                                       \
             GrB_Matrix : M,                                            \
             GrB_Vector : V,                                            \
             GxB_Scalar : S)                                            

#define _GL_GENERIC_OP(x, p, P, T, F)                                  \
    _Generic( (x), _GL_(p, P, T, F))                                   \

#define GL_ASSIGN(C, x, ...)                                            \
    GL_TRY(                                                             \
           _GL_GENERIC(C,                                               \
                       _GL_GENERIC_OP(x,, GrB, Matrix, setElement),     \
                       _GL_GENERIC_OP(x,, GrB, Vector, setElement),     \
                       _GL_GENERIC_OP(x,, GxB, Scalar, setElement))     \
           (C, x, __VA_ARGS__))

// EXTRACT(M, M)  Extract matrix from matrix
// EXTRACT(v, M, i) Extract vector from row, .desc=GrB_DESC_T0 for col extract
// EXTRACT(s, M, i, j) get element
// EXTRACT(v, v) Extract vector from vector
// EXTRACT(s, v, i) get element

#define GL_EXTRACT(x, C, ...)                                           \
    GL_TRY(                                                             \
           _GL_GENERIC(C,                                               \
                       _GL_GENERIC_OP(x, *, GrB, Matrix, extractElement), \
                       _GL_GENERIC_OP(x, *, GrB, Vector, extractElement), \
                       _GL_GENERIC_OP(x, *, GxB, Scalar, extractElement)) \
           (x, C, __VA_ARGS__))

#define GL_EXISTS(e, x, C, ...)                                         \
    { GrB_Info info =  _GL_GENERIC(C,                                   \
                       _GL_GENERIC_OP(x,, GrB, Matrix, extractElement), \
                       _GL_GENERIC_OP(x,, GrB, Vector, extractElement), \
                       _GL_GENERIC_OP(x,, GxB, Scalar, extractElement)) \
        if (info == GrB_NO_VALUE)                                       \
            e = false;                                                  \
        else                                                            \
            e = true;                                                   \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            GL_CATCH (info) ;                                           \
    }

#define GL_UNION (C, A, B, ...)
#define GL_INTERSECTION (C, A, B, ...)

#define GL_AXB(C, A, B, ...)                                            \
    _Generic ( (C),                                                     \
               GrB_Matrix : _GL_FNAME(GrB, mxm),                        \
               GrB_Vector : _Generic( (A),                              \
                                      GrB_Matrix: _GL_FNAME(GrB, mxv),  \
                                      GrB_Vector: _GL_FNAME(GrB, vxm)   \
                                      )                                 \
               )                                                        \
    (C, A, B, (_GL_SNAME(GrB, AXB)){__VA_ARGS__})

_GL_STRUCT(GrB, print, int level);

#define _GL_PRINTER(T, name)                                            \
    _GL_FUNC(T, name, GrB, print, T A) {                                \
        _GL_KWARG(int, level, 2);                                       \
        GL_TRY(GxB_print(A, level));                                    \
    }

_GL_PRINTER(GrB_Matrix,   print);
_GL_PRINTER(GrB_Vector,   print);
_GL_PRINTER(GrB_Semiring, print);

#define GL_PRINT(C, ...)                                                \
_Generic(                                                               \
         (C),                                                           \
         GrB_Semiring: _GL_FNAME(GrB_Semiring,   print),                \
         GrB_Vector:   _GL_FNAME(GrB_Vector,   print),                  \
         GrB_Matrix:   _GL_FNAME(GrB_Matrix,   print))                  \
(C, (_GL_SNAME(GrB, print)){__VA_ARGS__});

#define GL_CLEAR(...)
