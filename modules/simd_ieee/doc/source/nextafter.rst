.. _nextafter:

nextafter
==========

.. index::
    single: nextafter

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

  #include <nt2/toolbox/ieee/function/nextafter.hpp>

or simply

.. code-block:: cpp

  #include <nt2/toolbox/ieee.hpp>

for the whole toolbox

Synopsis
^^^^^^^^

.. code-block:: cpp

    <unspecified return type>  nextafter(
                      const A0& a0, const A1& a1
                     );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp


**Return type:** an unspecified type

**Semantic:** Equivalent to


Example
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/nextafter.cpp
   :language: cpp
