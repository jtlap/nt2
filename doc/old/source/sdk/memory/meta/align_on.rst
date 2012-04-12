.. _meta_align_on:

align_on
========

.. index::
    single: align_on
    single: meta; align_on

Description
^^^^^^^^^^^

Align an `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_
to an arbitrary boundary. By default, this boundary is equal to the system bets alignment values provided by
the ``bootstrap.hpp`` file.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | V         | Integral Constant            | Value to align     |
  +-----------+------------------------------+--------------------+
  | N         | Power of 2 Integral Constant | Alignment boundary |
  +-----------+------------------------------+--------------------+

Model
^^^^^
`Numeric Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/numeric-metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/alignment/align_on.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class V, class N = boost::mpl::size_t<NT2_CONFIG_ALIGNMENT> > struct align_on;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::align_on<V,N>::type r;

**Pre-condition:** ``N`` is an `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_
which is power of 2. If this pre-condition is violated, a ``INVALID_ALIGNMENT_VALUE`` static assertion is thrown at compile-time.

**Return type:** `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef mpl::integral_c<typename V::value_type, (V::value+N::value-1) & ~(N::value-1)> r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/memory/meta_align_on.cpp
   :language: cpp
