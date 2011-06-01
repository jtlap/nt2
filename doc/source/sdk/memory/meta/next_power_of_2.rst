.. _meta_next_power_of_2:

next_power_of_2
===============

.. index::
    single: next_power_of_2
    single: meta; next_power_of_2

Description
^^^^^^^^^^^

Compute the integral power of 2 greater or equal to a given `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | N         | Integral Constant            | Value to compute   |
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
    template<class N> struct next_power_of_2;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::next_power_of_2<N>::type r;

**Return type:** Numeric `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::integral_c<N::value_type,V> r;

with ``V`` equal to the power of 2 greater or equal to ``N::value``.

Example
^^^^^^^

.. literalinclude::  ../../../../../modules/sdk/examples/memory/next_power_of_2.cpp
   :language: cpp

