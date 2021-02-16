#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector louvain(GrB_Matrix A, uint64_t itermax) {
    GrB_Matrix ApAT, S;
    GrB_Vector Sj, empty, k, v, q, t;
    GxB_Scalar max;
    GrB_Index n;
    float m, f;
    bool changed, exists;

    GF_NROWS  (A,     n) ;
    GF_MNEW   (ApAT,  n, n) ;
    GF_IDENT  (S,     n, true, .type=GrB_BOOL) ;
    GF_VNEW   (Sj,    n, .type=GrB_BOOL) ;
    GF_VNEW   (empty, n, .type=GrB_BOOL) ;
    GF_VNEW   (k,     n) ;
    GV_VNEW   (v,     n) ;
    GF_VNEW   (q,     n) ;
    GF_VNEW   (t,     n) ;
    GF_SNEW   (max) ;

    GF_EADD   (ApAT,  A, T(A), .desc=GrB_DESC_T0) ;
    GF_REDUCE (k,     A) ;
    GF_REDUCE (m,     k) ;
    GF_APPLY  (k,     k, GrB_AINV_FP64) ;
    GF_APPLY  (k,     k, GrB_DIV_FP64, m) ;

    GF_FOR(i, 0, itermax && changed) {
        changed = false;
        GF_FORI(k, j) {
            GF_EXTRACT (Sj, S, j, .desc=GrB_DESC_T0) ;
            GF_ASSIGN  (S,  empty, j);
            GF_EXTRACT (v,  ApAT, j, GrB_DESC_T0) ;
            GF_EXTRACT (f,  v, j) ;
            GF_APPLY   (v,  GrB_PLUS_FP32, v, f) ;
            GF_AXB     (q,  v, S) ;
            GF_NVALS   (tn, q);
            if (tn == 0)
                continue ;

            GF_SELECT  (t, q, "max") ;
            if (tn == 1)
                r = GF_GETI(ts, 0) ;
            else
                GF_RANDI(r, ts);

            GF_ASSIGN (S, true, j, r) ;
            GF_EXISTS(exists, Sj, r) ;
            if (!exists)
                changed = True ;
        }
    }
    GF_FREE (S, ApAT, Sj, k, empty, v, q, t, max) ;
    return v;
}

void main(int argc, char *argv[]) {
    GF_INIT () ;
    GF_MNEW (A, .nrows=10, .ncols=10) ;
    GF_VNEW (v) ;
    GF_MMREAD(A, 'data.mm') ;
    v = louvain(A, 0) ;
    GF_PRINT(v) ;
    GF_FINALIZE() ;
}
