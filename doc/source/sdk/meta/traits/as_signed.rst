.. _meta_as_signed:

as_signed
==========

.. index::
    single: as_signed (meta)
    single: meta; as_signed

Description
^^^^^^^^^^^
Returns the equivalent signed type if the input is an :ref:`tag_arithmetic_` type and the input type otherwise.

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

  #include <nt2/sdk/functor/meta/as_signed.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct as_signed;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::as_signed<T>::type r;

**Return type:** unspecified

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef boost::make_signed<T>::type r;
  
if T is :ref:`tag_arithmetic_` and

.. code-block:: cpp

  typedef T r;
  
otherwise.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/as_signed.cpp
   :language: cpp
