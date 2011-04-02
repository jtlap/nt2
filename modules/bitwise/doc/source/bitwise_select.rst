.. _bitwise_select:

bitwise_select
==========

.. index::
    single: bitwise_select

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

  #include <nt2/toolbox/bitwise/function/bitwise_select.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/bitwise.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  bitwise_select(
                      const A0& a0, const A1& a1, const A2& a2
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/bitwise_select.cpp
   :language: cpp
