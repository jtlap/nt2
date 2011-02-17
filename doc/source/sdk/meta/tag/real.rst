.. _tag_real_:

real
=======

.. index::
    single: real_ (tag)
    single: tag; real_
    single: real_ (meta)
    single: meta; real_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
floating-point types.

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
      struct real_;
    }
    
    namespace meta
    {
      template<typename T>
      struct real_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
