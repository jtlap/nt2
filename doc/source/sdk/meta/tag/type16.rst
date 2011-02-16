.. _tag_type16_:

type16
=======

.. index::
    single: type16_ (tag)
    single: tag; type16_
    single: type16_ (meta)
    single: meta; type16_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
types of 16 bits.

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
      struct type16_;
    }
    
    namespace meta
    {
      template<typename T>
      struct type16_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
