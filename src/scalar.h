// New Scalar ------------------------------------------------------

DEFKWARGS(Scalar_new, GrB_Type type);

void _Scalar_new_(GxB_Scalar *A, _glaph_Scalar_new_kwargs kwargs)  {
    _KWARG(GrB_Type, type, GrB_FP64);
    _TRY(GxB_Scalar_new(A, type));
}

#define SNEW(v, ...)                                                    \
    _Scalar_new_(&v, (_glaph_Scalar_new_kwargs){__VA_ARGS__})           \

