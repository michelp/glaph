// New Vector ------------------------------------------------------

DEFKWARGS(Vector_new, GrB_Index size; GrB_Type type);

void _Vector_new_(GrB_Vector *A, _glaph_Vector_new_kwargs kwargs)  {
    _KWARG(GrB_Index, size, GxB_INDEX_MAX);
    _KWARG(GrB_Type, type, GrB_FP64);
    _TRY(GrB_Vector_new(A, type, size));
}

#define VNEW(v, ...)                                            \
    _Vector_new_(&v, (_glaph_Vector_new_kwargs){__VA_ARGS__})
    
#define VSIZE(A, name)                              \
    GrB_Index name; _TRY(GrB_Vector_size(&name, A))

// Vector Operations ------------------------------------------------------

DEFKWARGS(Vector_op, GrB_Vector mask; GrB_BinaryOp accum;
          GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _VOPKWARGS()                                                    \
    _KWARG(GrB_Vector, mask, NULL);                                     \
    _KWARG(GrB_BinaryOp, accum, NULL);                                  \
    _KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);       \
    _KWARG(GrB_Descriptor, descriptor, NULL);                           \

void _mxv_(GrB_Vector C, GrB_Matrix A, GrB_Vector B, _glaph_Vector_op_kwargs kwargs)  {
    _VOPKWARGS()
    _TRY(GrB_mxv(C, mask, accum, semiring, A, B, descriptor));
}

void _vxm_(GrB_Vector C, GrB_Vector A, GrB_Matrix B, _glaph_Vector_op_kwargs kwargs)  {
    _VOPKWARGS()
    _TRY(GrB_vxm(C, mask, accum, semiring, A, B, descriptor));
}
