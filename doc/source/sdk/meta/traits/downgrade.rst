.. _meta_downgrade:

downgrade
==========

.. index::
    single: downgrade (meta)
    single: meta; downgrade

Description
^^^^^^^^^^^
Returns the input type rebound with an integral type that is twice as small as its primitive, with optional sign.
If the primitive type is floating-point, use the floating-point type that is twice as small and discard the sign.

For :ref:`simd_pack`, also makes cardinal twice as big.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+--------------------------------------+------------------------------------------------------------------+
  | Parameter | Requirement                          | Description                                                      |
  +===========+======================================+==================================================================+ 
  | T         | :ref:`concept_has_primitive_factory` | Input type                                                       |
  +-----------+--------------------------------------+------------------------------------------------------------------+
  | Sign      | ``signed`` or ``unsigned``           | Whether the primitive type should be signed or not (if integral) |
  +-----------+--------------------------------------+------------------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/downgrade.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class Sign = typename sign_of<T>::type>
    struct downgrade;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::downgrade<T, Sign>::type r;

**Return type:** :ref:`concept_has_primitive_factory`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef make_real<max<sizeof(primitive_of<T>::type)/2, 4>::value, factory_of<T>::type>::type r;
  
if primitive is of hierarchy :ref:`tag_real_` and

.. code-block:: cpp

  typedef make_integer<max<sizeof(primitive_of<T>::type)/2, 1>::value, Sign, factory_of<T>::type>::type r;
  
otherwise.

.. seealso::

  :ref:`meta_sign_of`, :ref:`meta_make_real`, :ref:`meta_make_integer`

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/downgrade.cpp
   :language: cpp
