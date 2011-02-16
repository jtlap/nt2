.. _tag_ints64_:

ints64
=======

.. index::
    single: ints64_ (tag)
    single: tag; ints64_
    single: ints64_ (meta)
    single: meta; ints64_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
integers of 64 bits.

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
      struct ints64_;
    }
    
    namespace meta
    {
      template<typename T>
      struct ints64_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
