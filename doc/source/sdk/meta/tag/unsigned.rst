.. _tag_unsigned_:

unsigned
========

.. index::
    single: unsigned_ (tag)
    single: tag; unsigned_
    single: unsigned_ (meta)
    single: meta; unsigned_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned types.

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
      struct unsigned_;
    }
    
    namespace meta
    {
      template<typename T>
      struct unsigned_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
