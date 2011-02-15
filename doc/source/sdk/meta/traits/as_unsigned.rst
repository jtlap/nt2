.. _meta_as_unsigned:

as_unsigned
===========

.. index::
    single: as_unsigned (meta)
    single: meta; as_unsigned

Description
^^^^^^^^^^^
Returns the equivalent unsigned type if the input is an :ref:`tag_arithmetic_` type and the input type otherwise.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+----------------------------------------------------------+
  | Parameter | Requirement                | Description                                              |
  +===========+============================+==========================================================+ 
  | T         | None                       | Input type                                               |
  +-----------+----------------------------+----------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/as_unsigned.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct as_unsigned;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::as_unsigned<T>::type r;

**Return type:** unspecified

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef boost::make_unsigned<T>::type r;
  
if T is :ref:`tag_arithmetic_` and

.. code-block:: cpp

  typedef T r;
  
otherwise.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/as_unsigned.cpp
   :language: cpp
