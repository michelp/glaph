// New Matrix ------------------------------------------------------

_GF_DEFKWARGS(Matrix_new, GrB_Index nrows; GrB_Index ncols; GrB_Type type);

static inline void _Matrix_new_(GrB_Matrix *A, _GF_Matrix_new_kwargs kwargs)  {
    _GF_KWARG(GrB_Index, nrows, GxB_INDEX_MAX);
    _GF_KWARG(GrB_Index, ncols, GxB_INDEX_MAX);
    _GF_KWARG(GrB_Type, type, GrB_FP64);
    _GF_TRY(GrB_Matrix_new(A, type, nrows, ncols));
}

#define GF_MNEW(A, ...)                                         \
    _Matrix_new_(&A, (_GF_Matrix_new_kwargs){__VA_ARGS__})

#define GF_NROWS(A, name)                       \
    _GF_TRY(GrB_Matrix_nrows(&name, A))

#define GF_NCOLS(A, name)                          \
    _GF_TRY(GrB_Matrix_ncols(&name, A))

// Matrix Operations ------------------------------------------------------

_GF_DEFKWARGS(Matrix_op, GrB_Matrix mask; GrB_BinaryOp accum;
              GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _MOPKWARGS()                                                    \
    _GF_KWARG(GrB_Matrix, mask, NULL);                                     \
    _GF_KWARG(GrB_BinaryOp, accum, NULL);                                  \
    _GF_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);       \
    _GF_KWARG(GrB_Descriptor, descriptor, NULL);                           \

static inline void _mxm_(GrB_Matrix C, GrB_Matrix A, GrB_Matrix B, _GF_Matrix_op_kwargs kwargs)  {
    _MOPKWARGS()
    _GF_TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}

#define GF_MMREAD(...)

#define GF_IDENT(A, n, v, ...)                                          \
    _Matrix_new_(&A, (_GF_Matrix_new_kwargs){.nrows=n, .ncols=n, __VA_ARGS__}); \
    for (int A ## _ ## Si = 0; A ## _ ## Si < n; A ## _ ## Si++) {      \
    _GF_TRY(GrB_Matrix_setElement(S, v, A ## _ ## Si, A ## _ ## Si));   \
    
