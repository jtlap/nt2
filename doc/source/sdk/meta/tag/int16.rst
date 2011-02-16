.. _tag_int16_:

int16
=======

.. index::
    single: int16_ (tag)
    single: tag; int16_
    single: int16_ (meta)
    single: meta; int16_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed integers of 16 bits.

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
      struct int16_;
    }
    
    namespace meta
    {
      template<typename T>
      struct int16_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
