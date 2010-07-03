.. title:: NT2 - C++ High Performance Computing Made Easy


==============================
The Numerical Template Toolbox
==============================

.. image:: http://www.lri.fr/~falcou/nt2.png
   :align: right

.. contents:: Index

---------
About NT2
---------
NT2 is an Open Source C++ library providing various template matrix classes 
that can be used with a Matlab like syntax whose performances are close to those 
obtained with hand written C code thanks to various advanced C++ idioms
like generic programming, generative programming, expression templates or policy
driven design. 

So What is This About ?
:::::::::::::::::::::::
Various attempt has been made to provide a generic, rich and intuitive scientific 
computation library. Most of them failed to provide the expected performance due 
to various langage limitations. Based on advanced C++ techniques, NT2 proposes 
new ways to handle high-performance computating.

NT2 interface is based upon numeric arrays and their manipulation. It provides 
intuitive functions and operator to perform various operations on them using a 
Matlab or FORTRAN like interface including common arithmetic operations, original 
math.h functions, matrix product, singular value decomposition, gaussian elimination, 
sorting, filtering, eigenvalues and eigenvectors computation. NT2 use a modular 
system to provide other computation help classes.

The strongest advantage of NT2 is the high performance of the compiled executable. 
For most operations or operations composition, NT2 speed is very close to hand 
written C code. NT2 is also compatible with modern hardware, providing pervasive
exploitation of parallelism like SIMD multimedia extensions or multi-cores. In a 
matter of seconds, boost your performances thanks SSE2 or AltiVec, take advantage
of your dual or quad-core machine all without havign to think about it.

-------------
Documentation
-------------

User Documentation
::::::::::::::::::


Developer Documentation
:::::::::::::::::::::::

----------
References
----------

