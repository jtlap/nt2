.. _tag_ints16_:

ints16
=======

.. index::
    single: ints16_ (tag)
    single: tag; ints16_
    single: ints16_ (meta)
    single: meta; ints16_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
integers of 16 bits.

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
      struct ints16_;
    }
    
    namespace meta
    {
      template<typename T>
      struct ints16_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
