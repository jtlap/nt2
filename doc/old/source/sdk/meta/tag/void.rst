.. _tag_void_:

void
=======

.. index::
    single: void_ (tag)
    single: tag; void_
    single: void_ (meta)
    single: meta; void_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
the ``void`` type.

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
      struct void_;
    }
    
    namespace meta
    {
      template<typename T>
      struct void_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
