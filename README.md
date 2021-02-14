# You gotta glaph about it

glaph is an include-only C library of evil magic macros that make
working with the GraphBLAS API less existential and more
hallucinogenic.  Just copy the header files into your project and do:

    #include "glaph.h"

Also provided is an `unglaph.h` file that will purge the decadent evil
that is glaph from your symbol tables after you've used it by putting
the following at the *end* of your C file where you use glaph:

    #include "unglaph.h"
    
## So what's so funny

Glaph is meta-boilerplate for dealing with GraphBLAS objects.  Instead of:

    GrB_Matrix A;
    CHECK(GrB_Matrix_new(&A, GrB_FP64, nrows, ncols));
    
In glaph you just do:

    NEW(A);
    
Glaph declares the variable, initializes it as a hypersparse matrix
with default type FP64.  It is now ready to use in your program.

