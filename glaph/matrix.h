_GL_STRUCT(GrB, AXB, GrB_Matrix mask; GrB_Vector vmask; GrB_BinaryOp accum;
           GrB_Semiring semiring; GrB_Descriptor descriptor);

#define _MOPKWARGS()                                                    \
    _GL_KWARG(GrB_Matrix, mask, NULL);                                  \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);

_GL_FUNC(GrB, mxm, GrB, AXB, GrB_Matrix C, GrB_Matrix A, GrB_Matrix B) {
    _MOPKWARGS()
    GL_TRY(GrB_mxm(C, mask, accum, semiring, A, B, descriptor));
}

#define _VOPKWARGS()                                                    \
    _GL_KWARG(GrB_Vector, vmask, NULL);                                 \
    _GL_KWARG(GrB_BinaryOp, accum, NULL);                               \
    _GL_KWARG(GrB_Semiring, semiring, GrB_PLUS_TIMES_SEMIRING_FP64);    \
    _GL_KWARG(GrB_Descriptor, descriptor, NULL);                        \

_GL_FUNC(GrB, mxv, GrB, AXB, GrB_Vector C, GrB_Matrix A, GrB_Vector B)  {
    _VOPKWARGS()
    GL_TRY(GrB_mxv(C, vmask, accum, semiring, A, B, descriptor));
}

_GL_FUNC(GrB, vxm, GrB, AXB, GrB_Vector C, GrB_Vector A, GrB_Matrix B)  {
    _VOPKWARGS()
    GL_TRY(GrB_vxm(C, vmask, accum, semiring, A, B, descriptor));
}

#define GL_MMREAD(...)

#define GL_IDENT(A, n, v, ...)                                          \
    _Matrix_new_(&A, (_GL_SNAME(GrB_Matrix, new))                       \
                 {.nrows=n, .ncols=n, __VA_ARGS__});                    \
    for (int A ## _ ## Si = 0; A ## _ ## Si < n; A ## _ ## Si++)        \
        GL_TRY(GrB_Matrix_setElement(S, v, A ## _ ## Si, A ## _ ## Si))
