#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector shortest_path(GrB_Matrix A, uint64_t start) {
    GrB_Vector v, w;
    GL_VNEW(v);
    GL_VNEW(w);
    GL_ASSIGN(v, start, 0);
    FORI(A, i) {
        GL_CLEAR(w);
        GL_ASSIGN(w, v);
        GL_AXB(v, v, A,
               .semiring=GrB_MIN_PLUS_SEMIRING_INT64, .accum=GrB_MIN_INT64);
        if (GL_ISEQ(w, v))
            break;
    }
    GL_FREE(w);
    return v;
}

void main(int argc, char *argv[]) {
    GrB_Matrix A;
    GrB_Vector v;
    GL_INIT    (.mode=GrB_NONBLOCKING);
    GL_MNEW    (A);
    GL_READMM  (A, 'data.mm');
    v = sssp   (A, 0);
    GL_PRINT   (v, 2);
    GL_FINALIZE();
}

/*

def sssp(A, start):
    v = Vector.sparse(A.type, A.nrows)
    v[start] = 0
    with INT64.MIN_PLUS, Accum(INT64.MIN):
        for _ in A.rows:
            w.clear()
            w[:] = v
            v @= A
            if w.iseq(v):
                break
        return v
*/
