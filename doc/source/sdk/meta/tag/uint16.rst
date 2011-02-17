.. _tag_uint16_:

uint16
=======

.. index::
    single: uint16_ (tag)
    single: tag; uint16_
    single: uint16_ (meta)
    single: meta; uint16_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned integers of 16 bits.

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
      struct uint16_;
    }
    
    namespace meta
    {
      template<typename T>
      struct uint16_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
