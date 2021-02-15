#include <GraphBLAS.h>
#include "glaph.h"

GrB_Vector shortest_path(GrB_Matrix A, uint64_t start) {
    NEWV(v);
    NEWV(w);
    ASSIGN(v, start, 0);
    FORI(A, i) {
        DUP(w, v);
        AXB(v, v, A, .semiring=GrB_MIN_PLUS_SEMIRING_INT64, .accum=GrB_MIN_INT64);
        if (ISEQ(w, v))
            break;
    }
    FREE(w);
    return v;
}

void main(int argc, char *argv[]) {
    INIT();
    NEW(A);
    LOAD_MM(A, 'data.mm');
    v = shortest_path(A, 0);
    PRINT(v);
    FINALIZE();
}

#include "unglaph.h"

