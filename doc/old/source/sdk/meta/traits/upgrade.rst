.. _meta_upgrade:

upgrade
==========

.. index::
    single: upgrade (meta)
    single: meta; upgrade

Description
^^^^^^^^^^^
Returns the input type rebound with an integral type that is twice as big as its primitive, with optional sign.
If the primitive type is floating-point, use the floating-point type that is twice as big (the sign is ignored).

For :ref:`simd_pack`, also makes cardinal twice as small.

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

  #include <nt2/sdk/functor/meta/upgrade.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class Sign = typename sign_of<T>::type>
    struct upgrade;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::upgrade<T, Sign>::type r;

**Return type:** :ref:`concept_has_primitive_factory`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef make_real<min<sizeof(primitive_of<T>::type)*2, 8>::value, factory_of<T>::type>::type r;
  
if primitive is of hierarchy :ref:`tag_real_` and

.. code-block:: cpp

  typedef make_integer<min<sizeof(primitive_of<T>::type)*2, 8>::value, Sign, factory_of<T>::type>::type r;
  
otherwise.

.. seealso::

  :ref:`meta_sign_of`, :ref:`meta_make_real`, :ref:`meta_make_integer`

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/upgrade.cpp
   :language: cpp
