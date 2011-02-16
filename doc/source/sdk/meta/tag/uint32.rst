.. _tag_uint32_:

uint32
=======

.. index::
    single: uint32_ (tag)
    single: tag; uint32_
    single: uint32_ (meta)
    single: meta; uint32_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned integers of 32 bits.

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
      struct uint32_;
    }
    
    namespace meta
    {
      template<typename T>
      struct uint32_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
