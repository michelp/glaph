// New Vector ------------------------------------------------------

_GF_DEFKWARGS(Vector_new, GrB_Index size; GrB_Type type);

static inline void _Vector_new_(GrB_Vector *A, _GF_Vector_new_kwargs kwargs)  {
    _GF_KWARG(GrB_Index, size, GxB_INDEX_MAX);
    _GF_KWARG(GrB_Type, type, GrB_FP64);
    _GF_TRY(GrB_Vector_new(A, type, size));
}

#define GF_VNEW(v, ...)                                     \
    _Vector_new_(&v, (_GF_Vector_new_kwargs){__VA_ARGS__})
    
#define GF_VSIZE(A, name)                               \
    GrB_Index name; _GF_TRY(GrB_Vector_size(&name, A))

// Vector Operations ------------------------------------------------------

_GF_DEFKWARGS(Vector_op, GrB_Vector mask; GrB_BinaryOp accum;
          GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _VOPKWARGS()                                                    \
    _GF_KWARG(GrB_Vector, mask, NULL);                                     \
    _GF_KWARG(GrB_BinaryOp, accum, NULL);                                  \
    _GF_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);       \
    _GF_KWARG(GrB_Descriptor, descriptor, NULL);                           \

static inline void _mxv_(GrB_Vector C, GrB_Matrix A, GrB_Vector B, _GF_Vector_op_kwargs kwargs)  {
    _VOPKWARGS()
    _GF_TRY(GrB_mxv(C, mask, accum, semiring, A, B, descriptor));
}

static inline void _vxm_(GrB_Vector C, GrB_Vector A, GrB_Matrix B, _GF_Vector_op_kwargs kwargs)  {
    _VOPKWARGS()
    _GF_TRY(GrB_vxm(C, mask, accum, semiring, A, B, descriptor));
}
