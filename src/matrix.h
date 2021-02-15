// New Matrix ------------------------------------------------------

DEFKWARGS(Matrix_new, GrB_Index nrows; GrB_Index ncols; GrB_Type type);

void _Matrix_new_(GrB_Matrix *A, _glaph_Matrix_new_kwargs kwargs)  {
    _KWARG(GrB_Index, nrows, GxB_INDEX_MAX);
    _KWARG(GrB_Index, ncols, GxB_INDEX_MAX);
    _KWARG(GrB_Type, type, GrB_FP64);
    _TRY(GrB_Matrix_new(A, type, nrows, ncols));
}

#define MNEW(A, ...)                                            \
    _Matrix_new_(&A, (_glaph_Matrix_new_kwargs){__VA_ARGS__})

#define NROWS(A, name)                          \
    _TRY(GrB_Matrix_nrows(&name, A))

#define NCOLS(A, name)                          \
    _TRY(GrB_Matrix_ncols(&name, A))

// Matrix Operations ------------------------------------------------------

DEFKWARGS(Matrix_op, GrB_Matrix mask; GrB_BinaryOp accum;
          GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _MOPKWARGS()                                                    \
    _KWARG(GrB_Matrix, mask, NULL);                                     \
    _KWARG(GrB_BinaryOp, accum, NULL);                                  \
    _KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);       \
    _KWARG(GrB_Descriptor, descriptor, NULL);                           \

void _mxm_(GrB_Matrix C, GrB_Matrix A, GrB_Matrix B, _glaph_Matrix_op_kwargs kwargs)  {
    _MOPKWARGS()
    _TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}

#define LOAD_MM(...)

#define IDENT(A, n, v, ...)                                             \
    _Matrix_new_(&A, (_glaph_Matrix_new_kwargs){.nrows=n, .ncols=n, __VA_ARGS__}); \
    for (int A ## _ ## Si = 0; A ## _ ## Si < n; A ## _ ## Si++) {      \
    _TRY(GrB_Matrix_setElement(S, v, A ## _ ## Si, A ## _ ## Si));      \
    
