#include <GraphBLAS.h>
#include "glaph.h"

void main(int argc, char *argv[]) {
    GrB_Matrix A, B, C, M;
    GrB_Vector k, j, l, m;
    GxB_Scalar s, t, u, v;
    
    GL_INIT();
    GL_MNEW(A); GL_MNEW(B); GL_MNEW(C); GL_MNEW(M, .type=GrB_BOOL);
    GL_VNEW(k); GL_VNEW(j); GL_VNEW(l); GL_VNEW(m, .type=GrB_BOOL);
    GL_SNEW(s); GL_SNEW(t); GL_SNEW(u); GL_SNEW(v, .type=GrB_BOOL);
    
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
    
    GL_PRINT(GxB_ANY_SECOND_INT8, .level=5);

    GL_FINALIZE();
}
