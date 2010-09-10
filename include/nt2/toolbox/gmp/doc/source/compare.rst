.. _compare:

compare
==========

.. index::
    single: compare

Description
^^^^^^^^^^^
Returns the integral type with a given signedness and the same ``sizeof`` than its
argument.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------------------+--------------------+
  | Parameter | Requirement                       | Description        |
  +===========+===================================+====================+
  |           |                                   |                    |
  +-----------+-----------------------------------+--------------------+
  |           |                                   |                    |
  +-----------+-----------------------------------+--------------------+

Model
^^^^^


Header File
^^^^^^^^^^^

This functor belongs to the namespace: ``gmp``

.. code-block:: cpp

  #include <nt2/toolbox/gmp/function/compare.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/gmp.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  compare(
                      const A0& a0, const A1& a1, const A2& a2
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/compare.cpp
   :language: cpp
