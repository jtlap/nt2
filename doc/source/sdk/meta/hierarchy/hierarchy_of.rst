.. _meta_category_of:

category_of
===========

.. index::
    single: category_of (meta)
    single: meta; category_of

Description
^^^^^^^^^^^
Evaluates the category tag of a given type.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/category_of.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class T> struct category_of;
  } }

Expression semantic
^^^^^^^^^^^^^^^^^^^

For any type ``T``:

.. code-block:: cpp

  typedef category_of<T> c;

**Semantic:**	``c::type`` evaluates to any tag type if ``T`` has an inner
`nt2_category_tag` or if :ref:`meta_category_of` is specialized. Otherwise,
``c::type`` evaluates to :ref:`tag_unknown`.
