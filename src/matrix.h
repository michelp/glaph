// New Matrix ------------------------------------------------------

typedef struct {
    GrB_Type type;
    GrB_Index nrows;
    GrB_Index ncols;
} _glaph_mnew_kwargs;

void _Matrix_new_(GrB_Matrix *A, _glaph_mnew_kwargs kwargs)  {
    _KWARG(GrB_Type, type, GrB_FP64);
    _KWARG(GrB_Index, nrows, GxB_INDEX_MAX);
    _KWARG(GrB_Index, ncols, GxB_INDEX_MAX);
    _TRY(GrB_Matrix_new(A, type, nrows, ncols));
}

#define NEW(A, ...) GrB_Matrix A;                                       \
    _Matrix_new_(&A, (_glaph_mnew_kwargs){__VA_ARGS__})                   \
    
#define NROWS(A, name) GrB_Index name; _TRY(GrB_Matrix_nrows(&name, A))
#define NCOLS(A, name) GrB_Index name; _TRY(GrB_Matrix_ncols(&name, A))
#define NVALS(A, name) GrB_Index name; _TRY(GrB_Matrix_nvals(&name, A))

// Matrix Operations ------------------------------------------------------

typedef struct {
    GrB_Matrix mask;
    GrB_BinaryOp accum;
    GrB_Semiring semiring;
    GrB_Descriptor descriptor;
} _glaph_op_kwargs;

#define _OPKWARGS()                                                       \
    _KWARG(GrB_Matrix, mask, NULL);                                     \
    _KWARG(GrB_BinaryOp, accum, NULL);                                  \
    _KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);       \
    _KWARG(GrB_Descriptor, descriptor, NULL);                           \

void _mxm_(GrB_Matrix C, GrB_Matrix A, GrB_Matrix B, _glaph_op_kwargs kwargs)  {
    _OPKWARGS()
    _TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}
