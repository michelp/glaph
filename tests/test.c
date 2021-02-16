#include <GraphBLAS.h>
#include "glaph.h"

void main(int argc, char *argv[]) {
    GrB_Matrix A, B, C, M;
    GrB_Vector k, j, l, m;
    GxB_Scalar s, t, u, v;
    
    GF_INIT();
    GF_MNEW(A); GF_MNEW(B); GF_MNEW(C); GF_MNEW(M, .type=GrB_BOOL);
    GF_VNEW(k); GF_VNEW(j); GF_VNEW(l); GF_VNEW(m, .type=GrB_BOOL);
    GF_SNEW(s); GF_SNEW(t); GF_SNEW(u); GF_SNEW(v, .type=GrB_BOOL);
    
    GF_ASSIGN(A, 1.0, 0, 0);
    GF_ASSIGN(A, 1.0, 1, 1);
    GF_PRINT(A);
    
    GF_ASSIGN(B, 1.0, 1, 0);
    GF_ASSIGN(B, 1.0, 0, 1);
    GF_ASSIGN(B, 1.0, 0, 1);
    GF_PRINT(B);
    
    GF_ASSIGN(M, true, 0, 1);
    GF_ASSIGN(M, true, 1, 1);
    GF_PRINT(M);
    
    GF_AXB(C, A, B, .mask=M, .descriptor=GrB_DESC_T1);
    GF_PRINT(C, .level=5);

    double d;
    GF_EXTRACT(&d, C, 0, 1);

    bool exists;
    GF_EXISTS(exists, &d, C, 0, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    GF_EXISTS(exists, &d, C, 1, 1);
    printf("exists is %i d is %f\n", exists, d);
    
    GF_PRINT(GxB_ANY_SECOND_INT8, .level=5);

    GF_FINALIZE();
}
