#include <GraphBLAS.h>
#include "glaph.h"

void main(int argc, char *argv[]) {
    GrB_Matrix A, B, C, M;
    GrB_Vector k, j, l, m;
    GxB_Scalar s, t, u, v;
    
    INIT();
    MNEW(A);
    MNEW(B);
    MNEW(C);
    MNEW(M, .type=GrB_BOOL);
    
    VNEW(k);
    VNEW(j);
    VNEW(l);
    VNEW(m, .type=GrB_BOOL);
    
    SNEW(s);
    SNEW(t);
    SNEW(u);
    SNEW(v, .type=GrB_BOOL);
    
    SETE(A, 1.0, 0, 0);
    SETE(A, 1.0, 1, 1);
    PRINT(A);
    
    SETE(B, 1.0, 1, 0);
    SETE(B, 1.0, 0, 1);
    SETE(B, 1.0, 0, 1);
    PRINT(B);
    
    SETE(M, true, 0, 1);
    SETE(M, true, 1, 1);
    PRINT(M);
    
    AXB(C, A, B, .mask=M, .descriptor=GrB_DESC_T1);
    PRINT(C, .level=5);

    double d;
    GETE(&d, C, 0, 1);

    bool exists;
    EXISTS(exists, &d, C, 0, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    EXISTS(exists, &d, C, 1, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    PRINT(GxB_ANY_SECOND_INT8, .level=5);

    FINALIZE();
}

#include "unglaph.h"
