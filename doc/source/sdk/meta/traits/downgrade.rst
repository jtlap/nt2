.. _meta_downgrade:

downgrade
==========

.. index::
    single: downgrade (meta)
    single: meta; downgrade

Description
^^^^^^^^^^^
Returns the integral type that is twice as small as the input type, with optional sign.
If the input type is floating-point, return the floating-point type that is twice as small.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+---------------------------------------------------------------+
  | Parameter | Requirement                | Description                                                   |
  +===========+============================+===============================================================+ 
  | T         | None                       | Input type                                                    |
  +-----------+----------------------------+---------------------------------------------------------------+
  | Sign      | ``signed`` or ``unsigned`` | Whether the return type should be signed or not (if integral) |
  +-----------+----------------------------+---------------------------------------------------------------+

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

**Return type:** :ref:`tag_real_` if T is :ref:`tag_real_`, :ref:`tag_integer_` otherwise.

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef make_real<max<sizeof(T)/2, 4>::value>::type r;
  
if T is :ref:`tag_real_` and

.. code-block:: cpp

  typedef make_integer<max<sizeof(T)/2, 1>::value, Sign>::type r;
  
otherwise.

.. seealso::

  :ref:`meta_sign_of`, :ref:`meta_make_real`, :ref:`meta_make_integer`

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/downgrade.cpp
   :language: cpp
