.. _meta_next_power_of_2_c:

next_power_of_2_c
=================

.. index::
    single: next_power_of_2_c
    single: meta; next_power_of_2_c

Description
^^^^^^^^^^^

Compute the integral power of 2 greater or equal to a given `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | N         | integral constant            | Value to compute   |
  +-----------+------------------------------+--------------------+

Model
^^^^^
`Numeric Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/numeric-metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/alignment/next_power_of_2.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<std::size_t N> struct next_power_of_2_c;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::next_power_of_2_c<N>::type r;

**Return type:** Numeric `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::integral_c<std::size_t,V> r;

with ``V`` equal to the power of 2 greater or equal to ``N::value``.

Example
^^^^^^^

.. literalinclude::  ../../../../../modules/sdk/examples/memory/next_power_of_2_c.cpp
   :language: cpp

