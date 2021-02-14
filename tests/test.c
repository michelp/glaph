#include "glaph.h"

void main(int argc, char *argv[]) {
    INIT();

    NEW(C);
    NEW(A);
    NEW(B);
    NEW(M, GrB_BOOL);
    
    SET(A, 1.0, 0, 0);
    SET(A, 1.0, 1, 1);

    PRINT(A);
    
    SET(B, 1.0, 1, 0);
    SET(B, 1.0, 0, 1);
    
    PRINT(B);
    
    SET(M, true, 0, 1);
    SET(M, true, 1, 1);

    PRINT(M);
    
    AXB(C, A, B, .mask=M, .descriptor=GrB_DESC_T1);
    
    PRINT(C, .level=5);
    
    FINALIZE();
}

#include "unglaph.h"
