#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector pagerank(GrB_Matrix A, float damping, float tol, int itermax) {
    GrB_Index n;
    NROWS  (n, A);
    float  teleport = (1 - damping) / n ;
    float  rdiff = 1 ;
    
    VNEW   (t,  .size=n);
    VNEW   (r,  .size=n);
    VNEW   (w,  .size=n);
    ASSIGN (r,  1.0 / n);
    VNEW   (d,  .size=n);
    APPLY  (d,  GrB_DIV_FP32, d_out, damping) ;
    VNEW   (d1  .size=n) ;
    ASSIGN (d1, 1.0 / damping);
    ADD    (d,  d1, d, op=GrB_MAX_FP32) ;
    FREE   (d1) ;
    
    ITER (i, 0, itermax && rdiff > tol)  {
        GrB_Vector temp = t ; t = r ; r = temp ;
        MULT       (w, t, d, .op=GrB_DIV_FP32) ;
        ASSIGN     (r, teleport) ;
        AXB        (r, AT, w,
                    .accum=GrB_PLUS_FP32,
                    .semiring=GxB_PLUS_SECOND_FP32);
        ASSIGN     (t, r);
        APPLY      (t, GxB_ABS_FP32, t) ;
        REDUCE     (&rdiff, t) ;
    }
    return r ;
}

void main(int argc, char *argv[]) {
    INIT() ;
    LOAD_MM(A, 'data.mm') ;
    v = page_rank(A, 0.85, 0.001, 100) ;
    PRINT(v) ;
    FREE(A, v) ;
    FINALIZE() ;
}
