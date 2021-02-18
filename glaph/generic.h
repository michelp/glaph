
_GL_STRUCT(GrB, new,
           GrB_Index nI; GrB_Index nJ; GrB_Type type);

_GL_FUNC(GrB_Matrix, new, GrB, new, GrB_Matrix *A) {
    _GL_KWARG(GrB_Index, nI, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Index, nJ, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Matrix_new(A, type, nI, nJ));
}

_GL_FUNC(GrB_Vector, new, GrB, new, GrB_Vector *A) {
    _GL_KWARG(GrB_Index, nI, GxB_INDEX_MAX);
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GrB_Vector_new(A, type, nI));
}

_GL_FUNC(GxB_Scalar, new, GrB, new, GxB_Scalar *A) {
    _GL_KWARG(GrB_Type, type, GrB_FP64);
    GL_TRY(GxB_Scalar_new(A, type));
}

#define GL_NEW(A, ...)													\
	_GL_GENERIC((A),													\
				_GL_FNAME(GrB_Matrix, new),								\
				_GL_FNAME(GrB_Vector, new),								\
				_GL_FNAME(GxB_Scalar, new)								\
				) 														\
    (&A, (_GL_SNAME(GrB, new)){__VA_ARGS__})

#define GL_NI(n, A)								\
	GL_TRY(_GL_GENERIC((A),						\
					   GrB_Matrix_nrows,		\
					   GrB_Vector_size(&n, A)	\
					   GrB_Vector_size(&n, A)	\
					   )(&n, A))

#define GL_NJ(n, A)								\
	GL_TRY( GrB_Matrix_ncols(&n, A)

#define GL_NV(name, A)													\
    _GL_GENERIC((A),                                                    \
                GrB_Matrix_nvals,                                       \
                GrB_Vector_nvals,                                       \
                GxB_Scalar_nvals                                        \
                )(&name, A)

#define GL_ASSIGN(C, A, ...)

#define GL_EXTRACT(C, A, ...)

#define GL_SELECT(C, op, ...)

#define GL_SET(C, x, ...)                                               \
    GL_TRY(                                                             \
           _GL_GENERIC                                                  \
           ((C),                                                        \
            _GL_GENERIC_OP(x,, GrB, Matrix, setElement),                \
            _GL_GENERIC_OP(x,, GrB, Vector, setElement),                \
            _GL_GENERIC_OP(x,, GxB, Scalar, setElement))                \
           ((C), (x), __VA_ARGS__))

#define GL_GET(x, C, ...) { GrB_Info info =                             \
            _GL_GENERIC                                                 \
            ((C),                                                       \
             _GL_GENERIC_OP((x), *, GrB, Matrix, extractElement),       \
             _GL_GENERIC_OP((x), *, GrB, Vector, extractElement),       \
             _GL_GENERIC_OP((x), *, GxB, Scalar, extractElement))       \
            (x, C, __VA_ARGS__);                                        \
        if (info != GrB_SUCCESS)                                        \
            GL_CATCH (info) ;                                           \
    }

#define GL_EXISTS(e, x, C, ...) { GrB_Info info =                       \
        _GL_GENERIC                                                     \
        ((C),                                                           \
         _GL_GENERIC_OP((x), *, GrB, Matrix, extractElement),           \
         _GL_GENERIC_OP((x), *, GrB, Vector, extractElement),           \
         _GL_GENERIC_OP((x), *, GxB, Scalar, extractElement))           \
        (x, C, __VA_ARGS__);                                            \
        if (info == GrB_NO_VALUE)                                       \
            (e) = false;                                                \
        else                                                            \
            (e) = true;                                                 \
        if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))            \
            GL_CATCH (info) ;                                           \
    }

#define GL_UNION (C, A, B, ...)
#define GL_INTERSECTION (C, A, B, ...)

#define GL_AXB(C, A, B, ...)                                            \
    _GL_GENERIC ( (C),                                                  \
                  _GL_FNAME(GrB, mxm),                                  \
                  _GL_GENERIC( (A),                                     \
                               _GL_FNAME(GrB, mxv),                     \
                               _GL_FNAME(GrB, vxm),                     \
                               _GL_FNAME(GrB, mxm)                      \
                               ),                                       \
                  _GL_FNAME(GrB, mxm)                                   \
                  )                                                     \
    (C, A, B, (_GL_SNAME(GrB, AXB)){__VA_ARGS__})

_GL_STRUCT(GrB, print, int level);

#define _GL_PRINTER(T, name)                                            \
    _GL_FUNC(T, name, GrB, print, T A) {                                \
        _GL_KWARG(int, level, 2);                                       \
        GL_TRY(GxB_print(A, level));                                    \
    }

_GL_PRINTER(GrB_Matrix, print);
_GL_PRINTER(GrB_Vector, print);
_GL_PRINTER(GxB_Scalar, print);

#define GL_PRINT(C, ...)                                                \
    _GL_GENERIC((C),                                                    \
                _GL_FNAME(GrB_Matrix, print),                           \
                _GL_FNAME(GrB_Vector, print),                           \
                _GL_FNAME(GxB_Scalar, print))                           \
    (C, (_GL_SNAME(GrB, print)){__VA_ARGS__})

#define GL_CLEAR(C)                                                     \
    _GL_GENERIC((C),                                                    \
                GrB_Matrix_clear,                                       \
                GrB_Vector_clear,                                       \
                GxB_Scalar_clear)(C)

