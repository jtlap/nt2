.. _sub:

sub
==========

.. index::
    single: sub

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

  #include <nt2/toolbox/gmp/function/sub.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/gmp.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  sub(
                      const A0& a0, const A1& a1
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/sub.cpp
   :language: cpp
