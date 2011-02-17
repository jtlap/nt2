.. _tag_ints32_:

ints32
=======

.. index::
    single: ints32_ (tag)
    single: tag; ints32_
    single: ints32_ (meta)
    single: meta; ints32_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
integers of 32 bits.

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
      struct ints32_;
    }
    
    namespace meta
    {
      template<typename T>
      struct ints32_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
