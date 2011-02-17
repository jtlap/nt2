.. _meta_make_integer:

make_integer
============

.. index::
    single: make_integer (meta)
    single: meta; make_integer

Description
^^^^^^^^^^^
Builds a built-in integral type from a size in bytes and a signedness.
Can also take an optional lambda argument to apply to the result.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+------------------------------------------------------------+
  | Parameter | Requirement                | Description                                                |
  +===========+============================+============================================================+ 
  | Size      | std::size_t                | Size in bytes of desired integral type                     |
  +-----------+----------------------------+------------------------------------------------------------+
  | Sign      | ``signed`` or ``unsigned`` | Whether the integral type for bits should be signed or not |
  +-----------+----------------------------+------------------------------------------------------------+
  | Lambda    | |mpl_lambda|_              | Transform to apply to the result                           |
  +-----------+----------------------------+------------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/make_integer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class Size, class Signed = unsigned, class Lambda = na> struct make_integer;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::make_integer<Size, Sign, Lambda>::type r;

**Return type:** :ref:`tag_integer_`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef boost::mpl::apply1<Lambda, typename meta::make_integer<Size, Sign>::type>::type r;

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/make_integer.cpp
   :language: cpp
