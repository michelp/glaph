// New Scalar ------------------------------------------------------

_GF_DEFKWARGS(Scalar_new, GrB_Type type);

static inline void _Scalar_new_(GxB_Scalar *A, _GF_Scalar_new_kwargs kwargs)  {
    _GF_KWARG(GrB_Type, type, GrB_FP64);
    _GF_TRY(GxB_Scalar_new(A, type));
}

#define GF_SNEW(v, ...)                                              \
    _Scalar_new_(&v, (_GF_Scalar_new_kwargs){__VA_ARGS__})           \

