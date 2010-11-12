.. _atan2:

atan2
==========

.. index::
    single: atan2

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

This functor belongs to the namespace: ``cephes``

.. code-block:: cpp

  #include <nt2/toolbox/cephes/function/atan2.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/cephes.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  atan2(
                      const A0& a0, const A1& a1
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/atan2.cpp
   :language: cpp
