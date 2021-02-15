# You gotta glaph about it

glaph is an include-only C library of macros that make working with
the GraphBLAS API less existential and more hallucinogenic.  Just copy
the header files into your project and do:

## So what's so funny

Glaph is macro meta-boilerplate for dealing with GraphBLAS objects.  Instead of:

    GrB_TRY(GrB_Matrix_new(&A, GrB_FP64, nrows, ncols));
    
In glaph you just do:

    MNEW(A);
    
Glaph declares the variable, initializes it as a hypersparse matrix
with default type FP64.  It is now ready to use in your program for
many cases.

## Even more Generic

SuiteSparse comes with a number of generic macros that can work with
various types with the same funciton name.  Instead of calling
`GrB_Matrix_assign_FP64`, you can just call `GrB_assign` with the
right order and type of arguments that the compiler will pick the
right concrete function (for matrices with double floating point
arguments, as given in this example).

## Keyword arguments?

Everyone knows C doesn't have keyword arguments.  Glaph bends reality
slightly with some macro sleigh of hand to make using the C api a lot
easier.  Combined with the polymorphism of generic macros, there is a
lot of simplication.  Don't worry it's all pure 100% C!

For example `AXB` is the generic matrix mulitpilicaiton macro in
glaph.  It covers all cases that `GrB_mxm`, `GrB_vxm` and `GrB_mxv`
cover in the API.  Just Do `AXB (C, A, B)` and the macro will expand
to the correct underlying function for the argument types with all the
optional arguments filled in with `NULL`.

All other arguments to those 3 functions are optional, so instead of a
wall of NULLs they are specified by keyword argument:

    AXB (v, AT, w,
         .mask=M,
         .accum=GrB_PLUS_FP32,
         .semiring=GxB_PLUS_SECOND_FP32,
         .desc=GrB_DESC_T0);

The "keyword arguments" are really the guts of a struct initializer
that the macro is hiding from you.  No worries, it all works out great.
