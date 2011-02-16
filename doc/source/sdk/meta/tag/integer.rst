.. _tag_integer_:

integer
=======

.. index::
    single: integer_ (tag)
    single: tag; integer_
    single: integer_ (meta)
    single: meta; integer_

Description
^^^^^^^^^^^
Tag type used in |nt2| hierarchical overload resolution for discriminating
integers.

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
      struct integer_;
    }
    
    namespace meta
    {
      template<typename T>
      struct integer_;
    }
  }

.. seealso::

  :ref:`sdk_tags`
