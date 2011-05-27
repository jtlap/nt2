.. _meta_from_bits:

from_bits
=========

.. index::
    single: from_bits (meta)
    single: meta; from_bits

Description
^^^^^^^^^^^
Builds an union type that contains the specified type and an integral type with
the same size that can be used to access its representation in bits.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+------------------------------------------------------------+
  | Parameter | Requirement                | Description                                                |
  +===========+============================+============================================================+ 
  | T         | POD                        | Type to put in the union                                   |
  +-----------+----------------------------+------------------------------------------------------------+
  | Sign      | ``signed`` or ``unsigned`` | Whether the integral type for bits should be signed or not |
  +-----------+----------------------------+------------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/from_bits.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class Sign = unsigned>
    struct from_bits;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::from_bits<T, Sign>::type r;

**Return type:** unspecified

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef union { T value; meta::as_integer<T, Sign>::type bits; } r;

.. seealso::

  :ref:`meta_as_integer`

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/from_bits.cpp
   :language: cpp
