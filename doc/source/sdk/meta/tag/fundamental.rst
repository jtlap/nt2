.. _tag_fundamental_:

fundamental
===========

.. index::
    single: fundamental_ (tag)
    single: tag; fundamental_
    single: fundamental_ (meta)
    single: meta; fundamental_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
fundamental types, i.e. C++ built-in types.

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
      struct fundamental_;
    }
    
    namespace meta
    {
      template<typename T>
      struct fundamental_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
