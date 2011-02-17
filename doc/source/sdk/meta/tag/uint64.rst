.. _tag_uint64_:

uint64
=======

.. index::
    single: uint64_ (tag)
    single: tag; uint64_
    single: uint64_ (meta)
    single: meta; uint64_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned integers of 64 bits.

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
      struct uint64_;
    }
    
    namespace meta
    {
      template<typename T>
      struct uint64_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
