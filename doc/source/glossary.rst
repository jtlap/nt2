.. _glossary:

Glossary
========

Generic Terms
^^^^^^^^^^^^^
.. glossary::

  MIMD
      Acronym for the Flynn's **Multiple Instruction, Multiple Data** architectures.
      Machines using MIMD have a number of processors that function asynchronously
      and independently. At any time, different processors may be executing different
      instructions on different pieces of data. See also `the Wikipedia page about MIMD <http://en.wikipedia.org/wiki/MIMD>`_

  SIMD
      Acronym for the Flynn's **Single Instruction, Multiple Data** architectures.
      SIMD architectures revolve around various techniques to achieve data level parallelism.
      The term SIMD extension is usually used to design a large set of intra-processor vector
      unit used for multimedia and gaming like the SSE extensions family or the Altivec extension.
      See also `the Wikipedia page about SIMD <http://en.wikipedia.org/wiki/SIMD>`_

  SSE
      Acronym for **Streaming SIMD Extensions** architecture family including
      Intel SSE, SSE2, SSE3, SSSE3, AMD SSE4 and Intel AVX. See also
      `the Wikipedia page about SSE <http://en.wikipedia.org/wiki/SSE2>`_

  VMX
      Acronym for **Vector Multimedia Extensions** architecture family including
      Freescale AltiVec, IBM Altivec, VSX and the XBOX VMX128. See also `the Wikipedia page about Altivec <http://en.wikipedia.org/wiki/AltiVec>`_

C++ Related Terms
^^^^^^^^^^^^^^^^^
.. glossary::

  PFO
      A Polymorphic Function Object (PFO) is a function object exposing a template function call
      operator and which result type has to be deduced from its arguments type via the
      `result_of protocol <http://www.boost.org/doc/libs/release/libs/utility/utility.htm#result_of>`_.
      See also `the Polymorphic Function Object concept <http://www.boost.org/doc/libs/release/libs/fusion/doc/html/fusion/functional/concepts/poly.html>`_

  POD
      Plain old data (POD) structures are data structures that are represented
      only as passive collections of field values, without using encapsulation
      or other object-oriented features. POD classes have no user-defined copy assignment
      operator, no user-defined destructor, and no non-static data members that
      are not themselves PODs. Moreover, POD classes must be an aggregate, meaning
      it has no user-declared constructors, no private nor protected non-static
      data, no bases and no virtual functions. See also `C++ Language Note: POD Types <http://www.fnal.gov/docs/working-groups/fpcltf/Pkg/ISOcxx/doc/POD.html>`_

  SFINAE
      Substitution failure is not an error (SFINAE) refers to a situation in C++
      where an invalid substitution of template parameters is not in itself an
      error. Specifically, when creating a candidate set for overload resolution,
      some (or all) candidates of that set may be the result of substituting template
      parameters with deduced template arguments. If during substitution an error
      occurs, the compiler drops the potential overload from the candidate set
      (instead of making the program erroneous outright) provided the C++ standard
      substitution recognizes the error for such treatment. If one or more
      candidates remain and overload resolution succeeds, the program may be well-formed.

  Tag Dispatching
      Tag dispatching is a way of using function overloading to effect concept
      based overloading, and is often used hand-in-hand with traits classes.
      See also `the Generic Programming page about Tag Dispatching <http://www.generic-programming.org/languages/cpp/techniques.php#tag_dispatching>`_

Mathematical Computations Related Terms
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. glossary::

  Floating point arithmetic
      are the current way of representation of real numbers in scientific computing
      as the have a tendancy to preserve relative precision (opposite to Fixed point values that
      preserve absolute precision) and store the number in a fixed bit amount 
      divided in sign, exponent and mantissa parts.
      See also `the Wikipedia page about Floating point <http://en.wikipedia.org/wiki/Floating_point>`_
      and `the IEEE 754 standard <http://en.wikipedia.org/wiki/IEEE_754-2008>`_

  ULP
     Not all real numbers can be represented exactly by floating point values. Unit in the last place is 
     for a real x is the gap between the two _finite_ floating-point numbers
     nearest x , even if x is one of them. (But ulp(NaN) is NaN.). It is used as 
     a measure of precision in numeric calculations and is related to the "machine epsilon".

  Machine epsilon 
      Machine epsilon gives an upper bound on the relative error due to rounding in floating 
      point arithmetic. Typically 2^(-53) for floating point doubles and 2^(-24) for
      floats. MATLAB(TM) language defines the value `'eps' <http://www.mathworks.com/help/techdoc/ref/eps.html>`_
      as the distance from 1.0 to the next larger double  (two times the machine epsilon).

Math Related Terms
^^^^^^^^^^^^^^^^^^
.. glossary::

  foo
    Test of sub glossary entry
