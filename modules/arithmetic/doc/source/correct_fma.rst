.. _correct_fma:

correct_fma
==========

.. index::
    single: correct_fma

Description
^^^^^^^^^^^


Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------------------+--------------------+
  | Parameter | Requirement                       | Description        |
  +===========+===================================+====================+
  |           |                                   |                    |
  +-----------+-----------------------------------+--------------------+
  |           |                                   |                    |
  +-----------+-----------------------------------+--------------------+

Header File
^^^^^^^^^^^

This functor belongs to the namespace: ``functors``

.. code-block:: cpp

  #include <nt2/toolbox/arithmetic/function/correct_fma.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/arithmetic.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  correct_fma(
                      const A0& a0, const A1& a1, const A2& a2
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/correct_fma.cpp
   :language: cpp
