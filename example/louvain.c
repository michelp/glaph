#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector louvain(GrB_Matrix A, uint64_t itermax) {
    GrB_Matrix ApAT, S;
    GrB_Vector Sj, e, k, v, q, t;
    GxB_Scalar max;
    GrB_Index n;
    float m, f;
    bool changed, exists;

    GL_NROWS  (A,    n) ;
    GL_MNEW   (ApAT, n, n) ;
    GL_IDENT  (S,    n, true, .type=GrB_BOOL) ;
    GL_VNEW   (Sj,   n, .type=GrB_BOOL) ;
    GL_VNEW   (e,    n, .type=GrB_BOOL) ;
    GL_VNEW   (k,    n) ;
    GV_VNEW   (v,    n) ;
    GL_VNEW   (q,    n) ;
    GL_VNEW   (t,    n) ;
    GL_SNEW   (max) ;

    GL_EADD   (ApAT,  A, T(A), .desc=GrB_DESC_T0) ;
    GL_REDUCE (k,     A) ;
    GL_REDUCE (m,     k) ;
    GL_APPLY  (k,     k, GrB_AINV_FP64) ;
    GL_APPLY  (k,     k, GrB_DIV_FP64, m) ;

    GL_FOR(i, 0, i < itermax && changed) {
        changed = false;
        GL_FORI(j, k) {
            GL_EXTRACT (Sj, S, j, .desc=GrB_DESC_T0) ;
            GL_ASSIGN  (S,  e, j);
            GL_EXTRACT (v,  ApAT, j, .desc=GrB_DESC_T0) ;
            GL_EXTRACT (f,  v, j) ;
            GL_APPLY   (v,  GrB_PLUS_FP32, v, f) ;
            GL_AXB     (q,  v, S) ;
            GL_NVALS   (tn, q);
            if (tn == 0)
                continue ;

            GL_SELECT (t, q, "max") ;
            if (tn == 1)
                r = GL_GETI(ts, 0) ;
            else
                GL_RANDI(r, ts);

            GL_ASSIGN (S, true, j, r) ;
            GL_EXISTS (exists, Sj, r) ;
            if (!exists)
                changed = True ;
        }
    }
    GL_FREE (S, ApAT, Sj, k, e, v, q, t, max) ;
    return v;
}

void main(int argc, char *argv[]) {
    GL_INIT     () ;
    GL_MNEW     (A, .nrows=10, .ncols=10) ;
    GL_VNEW     (v) ;
    GL_MMREAD   (A, 'data.mm') ;
    v = louvain (A, 0) ;
    GL_PRINT    (v) ;
    GL_FINALIZE () ;
}
