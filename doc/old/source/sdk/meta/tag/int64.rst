.. _tag_int64_:

int64
=======

.. index::
    single: int64_ (tag)
    single: tag; int64_
    single: int64_ (meta)
    single: meta; int64_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed integers of 64 bits.

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
      struct int64_;
    }
    
    namespace meta
    {
      template<typename T>
      struct int64_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
