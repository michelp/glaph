#include "glaph.h"

/**
def shortest_path_length(matrix, start):
    v = Vector.sparse(matrix.type, matrix.nrows)
    v[start] = 0

    with INT64.MIN_PLUS, Accum(INT64.MIN):
        for _ in range(matrix.nrows):
            w = Vector.dup(v)
            v @= matrix
            if w.iseq(v):
                break
        return v
**/

void main(int argc, char *argv[]) {
    INIT();
    NEW(A);
    LOAD_TSV(A, 'data.tsv');
    VNEW(v);
    VNEW(w);
    SET(v, start, 0);
    NROWS(n, A);
    FOR(i, 0, n) {
        DUP(w, v);
        AXB(v, v, A, .semiring=GrB_MIN_PLUS_SEMIRING_INT64, .accum=GrB_MIN_INT64);
        if (ISEQ(w, v))
            break;
    }
    FREE(A, v, w);
    FINALIZE();
}

#include "unglaph.h"
