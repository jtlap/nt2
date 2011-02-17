.. _tag_double_:

double
=======

.. index::
    single: double_ (tag)
    single: tag; double_
    single: double_ (meta)
    single: meta; double_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
the ``double`` type.

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
      struct double_;
    }
    
    namespace meta
    {
      template<typename T>
      struct double_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
