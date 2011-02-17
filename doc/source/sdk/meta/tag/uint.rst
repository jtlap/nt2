.. _tag_uint_:

uint
=======

.. index::
    single: uint_ (tag)
    single: tag; uint_
    single: uint_ (meta)
    single: meta; uint_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
unsigned integers.

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
      struct uint_;
    }
    
    namespace meta
    {
      template<typename T>
      struct uint_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
