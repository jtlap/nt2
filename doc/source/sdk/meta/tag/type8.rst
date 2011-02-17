.. _tag_type8_:

type8
=======

.. index::
    single: type8_ (tag)
    single: tag; type8_
    single: type8_ (meta)
    single: meta; type8_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
types of 8 bits.

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
      struct type8_;
    }
    
    namespace meta
    {
      template<typename T>
      struct type8_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
