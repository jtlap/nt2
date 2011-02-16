.. _tag_unspecified_:

unspecified
===========

.. index::
    single: unspecified_ (tag)
    single: tag; unspecified_
    single: unspecified_ (meta)
    single: meta; unspecified_

Description
^^^^^^^^^^^
Tag type for discriminating non-categorized types in |nt2| hierarchical overload
resolution.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/hierarchy.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    namespace tag
    {
      struct unspecified_;
    }
    
    namespace meta
    {
      template<typename T>
      struct unspecified_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
