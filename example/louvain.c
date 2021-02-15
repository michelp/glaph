#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector louvain(GrB_Matrix A, uint64_t itermax) {
    GrB_Matrix ApAT, S;
    GrB_Vector Sj, empty, k, v, q, t;
    GxB_Scalar max;
    GrB_Index n;
    float m, f;
    bool changed, exists;

    NROWS  (A,     n) ;
    MNEW   (ApAT,  n, n) ;
    IDENT  (S,     n, true, .type=GrB_BOOL) ;
    VNEW   (Sj,    n, .type=GrB_BOOL) ;
    VNEW   (empty, n, .type=GrB_BOOL) ;
    VNEW   (k,     n) ;
    VNEW   (v,     n) ;
    VNEW   (q,     n) ;
    VNEW   (t,     n) ;
    SNEW   (max) ;

    EADD   (ApAT,  A, T(A), .desc=GrB_DESC_T0) ;
    REDUCE (k,     A) ;
    REDUCE (m,     k) ;
    APPLY  (k,     k, GrB_AINV_FP64) ;
    APPLY  (k,     k, GrB_DIV_FP64, m) ;

    FOR(i, 0, itermax && changed) {
        changed = false;
        FORI(k, j) {
            EXTRACT (Sj, S, j, .desc=GrB_DESC_T0) ;
            ASSIGN  (S,  empty, j);
            EXTRACT (v,  ApAT, j, GrB_DESC_T0) ;
            EXTRACT (f,  v, j) ;
            APPLY   (v,  GrB_PLUS_FP32, v, f) ;
            AXB     (q,  v, S) ;
            NVALS   (tn, q);
            if (tn == 0)
                continue ;

            SELECT  (t, q, "max") ;
            if (tn == 1)
                r = GETI(ts, 0) ;
            else
                RANDI(r, ts);

            ASSIGN (S, true, j, r) ;
            EXISTS(exists, Sj, r) ;
            if (!exists)
                changed = True ;
        }
    }
    FREE (S, ApAT, Sj, k, empty, v, q, t, max) ;
    return v;
}

void main(int argc, char *argv[]) {
    INIT () ;
    MNEW (A, .nrows=10, .ncols=10) ;
    VNEW (v) ;

    LOAD_MM(A, 'data.mm') ;
    v = louvain(A, 0) ;
    PRINT(v) ;
    FINALIZE() ;
}
