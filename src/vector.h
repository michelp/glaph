// New Vector ------------------------------------------------------

typedef struct {
    GrB_Type type;
    GrB_Index size;
} _glaph_mnew_args;

void _Vector_new_(GrB_Vector *A, _glaph_mnew_args kwargs)  {
    _KWARG(GrB_Type, type, GrB_FP64);
    _KWARG(GrB_Index, size, GxB_INDEX_MAX);
    _TRY(GrB_Vector_new(A, type, size));
}

#define VNEW(v, ...) GrB_Vector v;                                \
    _Vector_new_(&v, (_glaph_mnew_args){__VA_ARGS__})             \
    
#define VSIZE(A, name) GrB_Index name; _TRY(GrB_Vector_size(&name, A))
