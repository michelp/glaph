

#define SET(C, x, i, j) _TRY(GrB_Matrix_setElement(C, x, i, j))

#define AXB(C, A, B, ...) _mxm_(C, A, B, (_glaph_op_kwargs){__VA_ARGS__})
