.. _meta_is_aligned_c:

is_aligned_c
============

.. index::
    single: is_aligned_c
    single: meta; is_aligned_c

Description
^^^^^^^^^^^

Check if an integral constant is aligned on an arbitrary boundary.
By default, this boundary is equal to the system bets alignment values provided by
the ``bootstrap.hpp`` file.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | V         | Integral constant            | Value to check     |
  +-----------+------------------------------+--------------------+
  | N         | Power of 2 integral constant | Alignment boundary |
  +-----------+------------------------------+--------------------+

Model
^^^^^
`Numeric Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/numeric-metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/alignment/is_aligned.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<std::size_t V, std::size_t N = NT2_CONFIG_ALIGNMENT> struct is_aligned_c;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_aligned_c<V,N>::type r;

**Pre-condition:** ``N`` is an integral constant which is power of 2. If this pre-condition is violated,
a ``INVALID_ALIGNMENT_VALUE`` static assertion is thrown at compile-time.

**Return type:** Boolean `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::bool_<!(V & (N-1) )> r;

Example
^^^^^^^

.. literalinclude::  ../../../../../modules/sdk/examples/memory/meta_is_aligned_c.cpp
   :language: cpp

