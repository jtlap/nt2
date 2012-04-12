.. _tag_int32_:

int32
=======

.. index::
    single: int32_ (tag)
    single: tag; int32_
    single: int32_ (meta)
    single: meta; int32_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed integers of 32 bits.

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
      struct int32_;
    }
    
    namespace meta
    {
      template<typename T>
      struct int32_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
