.. _meta_is_power_of_2:

is_power_of_2
=============

.. index::
    single: is_power_of_2
    single: meta; is_power_of_2

Description
^^^^^^^^^^^

Check if an `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_
is a non-null power of 2.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | N         | Integral Constant            | Value to check     |
  +-----------+------------------------------+--------------------+

Model
^^^^^
`Numeric Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/numeric-metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/alignment/is_power_of_2.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class N> struct is_power_of_2;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_power_of_2<N>::type r;

**Return type:** Boolean `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::bool_<(!(N::value & (N::value - 1)) && N::value)> r;

Example
^^^^^^^

.. literalinclude::  ../../../../../modules/sdk/examples/memory/is_power_of_2.cpp
   :language: cpp

