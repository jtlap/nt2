.. _meta_primitive_of:

primitive_of
============

.. index::
    single: primitive_of (meta)
    single: meta; primitive_of

Description
^^^^^^^^^^^
Extracts a :ref:`tag_fundamental_` from an arbitrary type.

Customization point for :ref:`concept_has_primitive`.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-------------------------------+-----------------------------------------+
  | Parameter | Requirement                   | Description                             |
  +===========+===============================+=========================================+ 
  | T         | :ref:`concept_has_primitive`  | Input type                              |
  +-----------+-------------------------------+-----------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/primitive_of.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct primitive_of;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::primitive_of<T>::type r;

**Return type:** :ref:`tag_fundamental_`

**Semantic:** Unless specialized, equivalent to:

.. code-block:: cpp

  typedef T r;
  
