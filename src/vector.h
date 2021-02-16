// New Vector ------------------------------------------------------

_GL_KWARGS_STRUCT(GrB_Vector, new, GrB_Index size; GrB_Type type);

_GL_KWARGS_FUNC(GrB_Vector, new, GrB_Vector *A) {
    _GL_KWARG(GrB_Index, size, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Vector_new(A, type, size));
}

#define GL_VNEW(v, ...)                                     \
    _GL_GrB_Vector_new_func(&v, (_GL_GrB_Vector_new_kwargs){__VA_ARGS__})
    
#define GL_VSIZE(A, name)                               \
    GrB_Index name; GL_TRY(GrB_Vector_size(&name, A))

// Vector Operations ------------------------------------------------------

_GL_KWARGS_STRUCT(GrB, mxv, GrB_Vector mask; GrB_BinaryOp accum;
                  GrB_Semiring semiring; GrB_Descriptor descriptor);

_GL_KWARGS_STRUCT(GrB, vxm, GrB_Vector mask; GrB_BinaryOp accum;
                  GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _VOPKWARGS()                                                    \
    _GL_KWARG(GrB_Vector, mask, NULL);                                  \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);                        \

_GL_KWARGS_FUNC(GrB, mxv, GrB_Vector C, GrB_Matrix A, GrB_Vector B)  {
    _VOPKWARGS()
    GL_TRY(GrB_mxv(C, mask, accum, semiring, A, B, descriptor));
}

_GL_KWARGS_FUNC(GrB, vxm, GrB_Vector C, GrB_Vector A, GrB_Matrix B)  {
    _VOPKWARGS()
    GL_TRY(GrB_vxm(C, mask, accum, semiring, A, B, descriptor));
}
