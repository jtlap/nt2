.. _tag_ints8_:

ints8
=======

.. index::
    single: ints8_ (tag)
    single: tag; ints8_
    single: ints8_ (meta)
    single: meta; ints8_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
integers of 8 bits.

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
      struct ints8_;
    }
    
    namespace meta
    {
      template<typename T>
      struct ints8_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
