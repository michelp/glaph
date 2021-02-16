// New Matrix ------------------------------------------------------

_GL_KWARGS_STRUCT(GrB_Matrix, new, GrB_Index nrows; GrB_Index ncols; GrB_Type type);

_GL_KWARGS_FUNC(GrB_Matrix, new, GrB_Matrix *A) {
    _GL_KWARG(GrB_Index, nrows, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Index, ncols, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Matrix_new(A, type, nrows, ncols));
}
#define GL_MNEW(A, ...)                                                 \
    _GL_GrB_Matrix_new_func(&A, (_GL_GrB_Matrix_new_kwargs){__VA_ARGS__})

#define GL_NROWS(A, name)                       \
    GL_TRY(GrB_Matrix_nrows(&name, A))

#define GL_NCOLS(A, name)                          \
    GL_TRY(GrB_Matrix_ncols(&name, A))

// Matrix Operations ------------------------------------------------------

_GL_KWARGS_STRUCT(GrB, mxm, GrB_Matrix mask; GrB_BinaryOp accum;
                  GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _MOPKWARGS()                                                    \
    _GL_KWARG(GrB_Matrix, mask, NULL);                                  \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);                        \

_GL_KWARGS_FUNC(GrB, mxm, GrB_Matrix C, GrB_Matrix A, GrB_Matrix B) {
    _MOPKWARGS()
    GL_TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}

#define GL_MMREAD(...)

#define GL_IDENT(A, n, v, ...)                                          \
    _Matrix_new_(&A, (_GL_GrB_Matrix_new_kwargs){.nrows=n, .ncols=n, __VA_ARGS__}); \
    for (int A ## _ ## Si = 0; A ## _ ## Si < n; A ## _ ## Si++) {      \
    GL_TRY(GrB_Matrix_setElement(S, v, A ## _ ## Si, A ## _ ## Si));
