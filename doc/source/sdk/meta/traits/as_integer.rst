.. _meta_as_integer:

as_integer
==========

.. index::
    single: as_integer (meta)
    single: meta; as_integer

Description
^^^^^^^^^^^
Returns the integral type with the same size and sign as the input type.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+----------------------------------------------------------+
  | Parameter | Requirement                | Description                                              |
  +===========+============================+==========================================================+ 
  | T         | None                       | Input type                                               |
  +-----------+----------------------------+----------------------------------------------------------+
  | Sign      | ``signed`` or ``unsigned`` | Whether the return integral type should be signed or not |
  +-----------+----------------------------+----------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/as_integer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class Sign = typename sign_of<T>::type>
    struct as_integer;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::as_integer<T, Sign>::type r;

**Return type:** :ref:`tag_integer_`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef make_integer<sizeof(T), Sign>::type r;

.. seealso::

  :ref:`meta_sign_of`, :ref:`meta_make_integer`

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/as_integer.cpp
   :language: cpp
