.. _meta_is_power_of_2_c:

is_power_of_2_c
===============

.. index::
    single: is_power_of_2_c
    single: meta; is_power_of_2_c

Description
^^^^^^^^^^^

Check if an compile-time integer value is a non-null power of 2.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | N         | An integral constant         | Value to check     |
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
    template<std::size_t N> struct is_power_of_2_c;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_power_of_2_c<N>::type r;

**Return type:** Boolean `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::bool_<(!(N & (N - 1)) && N)> r;

Example
^^^^^^^

.. literalinclude::  ../../../../../modules/sdk/examples/memory/is_power_of_2_c.cpp
   :language: cpp
