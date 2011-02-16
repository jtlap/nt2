.. _tag_int8_:

int8
=======

.. index::
    single: int8_ (tag)
    single: tag; int8_
    single: int8_ (meta)
    single: meta; int8_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed integers of 8 bits.

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
      struct int8_;
    }
    
    namespace meta
    {
      template<typename T>
      struct int8_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
