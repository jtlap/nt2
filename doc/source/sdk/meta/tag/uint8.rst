.. _tag_uint8_:

uint8
=======

.. index::
    single: uint8_ (tag)
    single: tag; uint8_
    single: uint8_ (meta)
    single: meta; uint8_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned integers of 8 bits.

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
      struct uint8_;
    }
    
    namespace meta
    {
      template<typename T>
      struct uint8_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
