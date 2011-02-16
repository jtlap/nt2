.. _meta_factory_of:

factory_of
===========

.. index::
    single: factory_of (meta)
    single: meta; factory_of

Description
^^^^^^^^^^^
Returns a |mpl_lambda|_ that can be used to build new types similar to the input but
with a different primitive.

Customization point for :ref:`concept_has_primitive_factory`.

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

  #include <nt2/sdk/functor/meta/factory_of.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct factory_of;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::factory_of<T>::type r;

**Return type:** |mpl_lambda|_

**Semantic:** Unless specialized, equivalent to:

.. code-block:: cpp

  typedef T r;
  
