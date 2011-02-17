.. _tag_bool_:

bool
=======

.. index::
    single: bool_ (tag)
    single: tag; bool_
    single: bool_ (meta)
    single: meta; bool_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
the ``bool`` type.

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
      struct bool_;
    }
    
    namespace meta
    {
      template<typename T>
      struct bool_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
