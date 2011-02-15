.. _meta_as_real:

as_real
==========

.. index::
    single: as_real (meta)
    single: meta; as_real

Description
^^^^^^^^^^^
Returns the floating-point type with the same size and sign as the input type.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+----------------------------------------------------------+
  | Parameter | Requirement                | Description                                              |
  +===========+============================+==========================================================+ 
  | T         | None                       | Input type                                               |
  +-----------+----------------------------+----------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/as_real.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct as_real;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::as_real<T>::type r;

**Return type:** :ref:`tag_real_`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef make_real<sizeof(T)>::type r;
  
.. seealso::

  :ref:`meta_make_real`

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/as_real.cpp
   :language: cpp
