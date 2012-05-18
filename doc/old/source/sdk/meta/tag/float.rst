.. _tag_float_:

float
=======

.. index::
    single: float_ (tag)
    single: tag; float_
    single: float_ (meta)
    single: meta; float_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
the ``float`` type.

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
      struct float_;
    }
    
    namespace meta
    {
      template<typename T>
      struct float_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
