.. _tag_type64_:

type64
=======

.. index::
    single: type64_ (tag)
    single: tag; type64_
    single: type64_ (meta)
    single: meta; type64_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
types of 64 bits.

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
      struct type64_;
    }
    
    namespace meta
    {
      template<typename T>
      struct type64_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
