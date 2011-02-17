.. _tag_signed_:

signed
=======

.. index::
    single: signed_ (tag)
    single: tag; signed_
    single: signed_ (meta)
    single: meta; signed_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
signed types.

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
      struct signed_;
    }
    
    namespace meta
    {
      template<typename T>
      struct signed_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
