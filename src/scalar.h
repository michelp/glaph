// New Scalar ------------------------------------------------------

_GL_STRUCT(GxB_Scalar, new, GrB_Type type);

_GL_FUNC(GxB_Scalar, new, GxB_Scalar, new, GxB_Scalar *A) {
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GxB_Scalar_new(A, type));
}

#define GL_SNEW(s, ...)                                                 \
    _GL_FNAME(GxB_Scalar, new)                               \
    (&s, (_GL_SNAME(GxB_Scalar, new)){__VA_ARGS__})

