.. _tag_type32_:

type32
=======

.. index::
    single: type32_ (tag)
    single: tag; type32_
    single: type32_ (meta)
    single: meta; type32_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
types of 32 bits.

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
      struct type32_;
    }
    
    namespace meta
    {
      template<typename T>
      struct type32_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
