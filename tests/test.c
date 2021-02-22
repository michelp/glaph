#include <GraphBLAS.h>
#include "glaph.h"

void main(int argc, char *argv[]) {
    GrB_Matrix A, B, C, M;
    GrB_Vector k, j, l, m;
    GxB_Scalar s, t, u, v;
    
    GL_INIT();
    GL_NEW(A); GL_NEW(B); GL_NEW(C); GL_NEW(M, .type=GrB_BOOL);
    GL_NEW(k); GL_NEW(j); GL_NEW(l); GL_NEW(m, .type=GrB_BOOL);
    GL_NEW(s); GL_NEW(t); GL_NEW(u); GL_NEW(v, .type=GrB_BOOL);
    
    GL_SET(A, 1.0, 0, 0);
    GL_SET(A, 1.0, 1, 1);
    GL_PRINT(A);
    
    GL_SET(B, 1.0, 1, 0);
    GL_SET(B, 1.0, 0, 1);
    GL_SET(B, 1.0, 0, 1);
    GL_PRINT(B);
    
    GL_SET(M, true, 0, 1);
    GL_SET(M, true, 1, 1);
    GL_PRINT(M);
    
    GL_SET (j, 1.0, 0);
    GL_SET (j, 1.0, 1);
    GL_PRINT(j);
    
    GL_AXB(C, A, B, .mask=M, .descriptor=GrB_DESC_T1);
    GL_PRINT(C, .level=5);

    GL_AXB(k, A, j, .vmask=m, .descriptor=GrB_DESC_T1);
    GL_PRINT(k, .level=5);
    
    double d;
    GL_GET(&d, C, 0, 1);

    bool exists;
    GL_EXISTS(exists, &d, C, 0, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    GL_EXISTS(exists, &d, C, 1, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    GL_EXISTS(exists, &d, j, 0);
    printf("exists is %i d is %f\n", exists, d);
    
    GL_EXISTS(exists, &d, j, 2);
    printf("exists is %i d is %f\n", exists, d);

    GrB_Index Cn;
    GL_NV(Cn, C);
    printf("C nvals %lu\n", Cn);
    GL_CLEAR(C);
    GL_NV(Cn, C);
    printf("C clear nvals %lu\n", Cn);
    
    GL_NV(Cn, j);
    printf("j nvals %lu\n", Cn);
    GL_CLEAR(j);
    GL_NV(Cn, j);
    printf("j clear nvals %lu\n", Cn);
	GL_FREE(A, B, C, M, k, j, l, m, s, t, u, v);
    GL_FINALIZE();
}
