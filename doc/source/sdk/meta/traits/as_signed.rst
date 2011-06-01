.. _meta_as_signed:

as_signed
==========

.. index::
    single: as_signed (meta)
    single: meta; as_signed

Description
^^^^^^^^^^^
Returns the input type rebound with the equivalent (same size) 
signed type of its primitive type.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+----------------------------------------------------------+
  | Parameter | Requirement                | Description                                              |
  +===========+============================+==========================================================+ 
  | T         | HasPrimitiveFactory        | Input type                                               |
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

**Return type:** :ref:`concept_has_primitive_factory`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef factory_of<T>::type::apply<boost::make_signed<primitive_of<T>::type>::type>::type r;
  

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/as_signed.cpp
   :language: cpp
