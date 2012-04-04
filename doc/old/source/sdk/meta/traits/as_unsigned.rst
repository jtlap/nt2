.. _meta_as_unsigned:

as_unsigned
===========

.. index::
    single: as_unsigned (meta)
    single: meta; as_unsigned

Description
^^^^^^^^^^^
Returns the input type rebound with the equivalent (same size) 
unsigned type of its primitive type.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+--------------------------------------+-----------------------------------------+
  | Parameter | Requirement                          | Description                             |
  +===========+======================================+=========================================+ 
  | T         | :ref:`concept_has_primitive_factory` | Input type                              |
  +-----------+--------------------------------------+-----------------------------------------+

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

**Return type:** :ref:`concept_has_primitive_factory`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef factory_of<T>::type::apply<boost::make_unsigned<primitive_of<T>::type>::type>::type r;
  

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/as_unsigned.cpp
   :language: cpp
