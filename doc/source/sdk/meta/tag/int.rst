.. _tag_int_:

int
=======

.. index::
    single: int_ (tag)
    single: tag; int_
    single: int_ (meta)
    single: meta; int_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed integers.

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
      struct int_;
    }
    
    namespace meta
    {
      template<typename T>
      struct int_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
