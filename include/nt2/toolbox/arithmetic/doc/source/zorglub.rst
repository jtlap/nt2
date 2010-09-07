.. _zorglub:

zorglub
==========

.. index::
    single: zorglub

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

This functor belongs to the namespace: ``functors``

.. code-block:: cpp

  #include <nt2/toolbox/arithmetic/function/zorglub.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/arithmetic.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  zorglub(
                      const A0 a0, const A1 a1
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/zorglub.cpp
   :language: cpp
