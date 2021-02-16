# glaph: Generics Library for GraphBLAS

glaph is an include-only C library of macros and inline functions that
make working with the GraphBLAS API less C like and more "Python
like".  Just copy the header files into your project and do:

    #include "glaph.h"

## So what's so funny

Glaph is macro and inline function meta-boilerplate for dealing with
GraphBLAS objects.  Instead of:

    GrB_TRY(GrB_Matrix_new(&A, GrB_FP64, nrows, ncols));
    
In glaph you just do:

    MNEW(A);
    
This is a rather tame example of a glaph macro.  It initializes it as
a hypersparse matrix with default type FP64.  It is now ready to use
in your program for many cases.  But lets say you don't want a 10 by
10 boolean matrix instead, do:

    MNEW(A, 10, 10, .type=GrB_BOOL);
    
It's the same macro, it's just generic enough to handle various cases
including optional types and dimensions provided as keywork arguments.

Now, everyone knows C doesn't have keyword arguments.  Glaph bends
reality with some macro sleigh of hand to make using the C api a lot
easier.  Combined with the polymorphism of generic macros, there is a
lot of simplication and glaph algorithms are usualy line for line
operationally identical to their Python equivalents.  Don't worry it's
all pure 100% C!

Another example is that where the GraphBLAS C API provides `GrB_mxm`,
`GrB_mxv` and `GrB_vxm` for Matix/Matrix, Matrix/Vector, and
Vector/Matrix multiplication respectively, glaph has only `GL_AXB(C,
A, B)`:

        GL_AXB(C, A, B,
               .mask=M,
               .accum=GrB_MIN_INT64);
               
        GL_AXB(c, a, B,
               .mask=m,
               .semiring=GrB_MIN_PLUS_SEMIRING_INT64);

        GL_AXB(c, A, b,
               .mask=m,
               .semiring=GrB_MIN_PLUS_SEMIRING_INT64, 
               .accum=GrB_MIN_INT64);
               
The only invalid combination is (Vector, Vector, Vector) which will
throw a compiler error.

One of the consequence of glaph using C metaprogramming is that the C
compiler optimizing pass will generate the same code that you would
have written by hand.  The keyword arguments structs and inline
functions "evaporate" to static arguments, just as if you had placed
them there by hand.  In a sense glaph self-destructs when it's
compiled, leaving only a GraphBLAS program behind.

## shortest path example

This is the shortest path example:

    GrB_Vector sssp(GrB_Matrix A, uint64_t start) {
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

Here is the equivalent Python with pygraphblas:

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

## Even more Generic

SuiteSparse comes with a number of generic macros that can work with
various types with the same funciton name.  Instead of calling
`GrB_Matrix_assign_FP64`, you can just call `GrB_assign` with the
right order and type of arguments that the compiler will pick the
right concrete function (for matrices with double floating point
arguments, as given in this example).

glaph takes this idea even further, instead of
`GrB_Matrix_setElement`, the `ASSIGN` macro can handle the scalar case
as well as the already supported vector and matrix cases.  It also
includes support for `GxB_Scalar`, All in one macro.

This pattern is carred over to `GL_EXTRACT` as well, you can extract
sub-graphs, vectors, Scalars, and C scalar values all with one macro,
each with its own distinct set of keyword arguments depending on the
input types of the operation.

All macros take the pattern:

   GL_NAME(C, [A, [B, ...] ...])
   
They all require at least one input (for things like `GL_PRINT`) or
output.  Glaph macros NEVER return values so never do something like
`x = GL_NAME(...)`.  If the macro has output, it is always the first
argument.  Keyword arguments depend on whatever pattern of positional
arguments matched the _Generic expansion.  `GL_EXTRACT` for example,
will accept `mask`, `accum` and `desc` keywork arguments in all cases
except scalar.  Trying to use inappropriate keyworks arguments will
result in a compiler error.

All glaph macros automatically check for and handle SuiteSparse
errors.  The default behavior is to print and abort on any error
except `GrB_SUCCESS` or `GrB_NO_VALUE`.  You can re-define the
`GL_CATCH` macro to handle your own errors.

## Keyword arguments?

For example `AXB` is the generic matrix mulitpilicaiton macro in
glaph.  It covers all cases that `GrB_mxm`, `GrB_vxm` and `GrB_mxv`
cover in the API.  Just Do `AXB (C, A, B)` and the macro will expand
to the correct underlying function for the argument types with all the
optional arguments filled in with `NULL`.

All other arguments to those 3 functions are optional, so they are
specified by keyword argument:

    AXB (v, AT, w,
         .mask=M,
         .accum=GrB_PLUS_FP32,
         .semiring=GxB_PLUS_SECOND_FP32,
         .desc=GrB_DESC_T0);

The "keyword arguments" are really the guts of a struct initializer
that the macro is hiding from you.  No worries, it all works out
great.  In fact, the C compiler knows that these structs are all
statically initialized, and completely optimizes all of glaph away,
exactly compiling the same assembly code that using the GraphBLAS API
directly "by hand" would create.
