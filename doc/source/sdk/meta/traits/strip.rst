.. _meta_strip:

strip
=====

.. index::
    single: strip (meta)
    single: meta; strip

Description
^^^^^^^^^^^
Removes all ``const`` and reference qualifier from any given types.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------+---------------------+
  | Parameter | Requirement           | Description         |
  +===========+=======================+=====================+ 
  | T         | None                  | Types to modify     |
  +-----------+-----------------------+---------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/strip.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T> struct strip;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::strip<T>::type r;

**Return type:** unspecified

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef remove_reference<remove_const<T>::type>::type r;

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/strip.cpp
   :language: cpp
