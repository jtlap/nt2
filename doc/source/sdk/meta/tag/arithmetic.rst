.. _tag_arithmetic_:

arithmetic
==========

.. index::
    single: arithmetic_ (tag)
    single: tag; arithmetic_
    single: arithmetic_ (meta)
    single: meta; arithmetic_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
arithmetic types, i.e. built-in integral and floating-point types.
Note ``bool`` is not considered an arithmetic type.

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
      struct arithmetic_;
    }
    
    namespace meta
    {
      template<typename T>
      struct arithmetic_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
