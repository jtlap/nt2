.. _tag_unknown_:

unknown
=======

.. index::
    single: unknown_ (tag)
    single: tag; unknown_
    single: unknown_ (meta)
    single: meta; unknown_

Description
^^^^^^^^^^^
Tag type for discriminating unregistered types in |nt2| hierarchical overload
resolution.

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
      struct unknown_;
    }
    
    namespace meta
    {
      template<typename T>
      struct unknown_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
