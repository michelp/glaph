// New Scalar ------------------------------------------------------

_GL_KWARGS_STRUCT(GxB_Scalar, new, GrB_Type type);

_GL_KWARGS_FUNC(GxB_Scalar, new, GxB_Scalar *A) {
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GxB_Scalar_new(A, type));
}

#define GL_SNEW(s, ...)                                                 \
    _GL_KWARGS_FUNC_NAME(GxB_Scalar, new)                               \
    (&s, (_GL_KWARGS_STRUCT_NAME(GxB_Scalar, new)){__VA_ARGS__})

