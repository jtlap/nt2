.. _meta_hierarchy_of:

hierarchy_of
============

.. index::
    single: hierarchy_of (meta)
    single: meta; hierarchy_of

Description
^^^^^^^^^^^
Evaluates the category tag of a given type.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/hierarchy_of.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class T> struct hierarchy_of;
  } }

Expression semantic
^^^^^^^^^^^^^^^^^^^

For any type ``T``:

.. code-block:: cpp

  typedef hierarchy_of<T> c;

**Semantic:**	``c::type`` evaluates the entry point of ``T`` inside the
type hierarchy lattice, or the hierarchy which type is :ref:`tag_unknown_` if
``T`` is not hierarchizable.
