# -----------------------------------------------------------------------------
# A 64-bit command line application to compute x^y.
#
# Syntax: power x y
# x and y are integers
# -----------------------------------------------------------------------------

        .global approx_sqrt
        .type approx_sqrt, @function
x = %xmm0
eps = %xmm1
xn = %xmm2
xn1 = %xmm8
tmp = %xmm6

       .section .text
approx_sqrt:
        movsd   x, xn
       
LOOP:   movsd   x, xn1
        divsd   xn, xn1
        addsd   xn, xn1
        divsd   pol, xn1 # xn+1 = 1/2 * (xn + x/xn)
        
        movsd   xn1, tmp
        subsd   xn, tmp
        andpd   abs, tmp #|xn - xn+1|
        
        movsd   xn1, xn
        
        comisd  eps, tmp
        ja   LOOP   
        
        movsd   xn, x
        ret
       
       
       
       
       .section .rodata
   
    .local pol
    .type pol, @object
    .align 8
pol:   .double 2.0

    .local abs
    .type pol, @object
    .align 8
abs:   .quad 0x7fffffffffffffff,0 #0x7fffffff,0,0
