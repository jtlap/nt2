.. _meta_align_on_c:

align_on_c
==========

.. index::
    single: align_on_c
    single: meta; align_on_c

Description
^^^^^^^^^^^

Align an integral constant to an arbitrary boundary. By default, this boundary
is equal to the system bets alignment values provided by the ``bootstrap.hpp``
file.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | V         | Integral constant            | Value to align     |
  +-----------+------------------------------+--------------------+
  | N         | Power of 2 integral constant | Alignment boundary |
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

  namespace n2 { namespace meta
  {
    template<std::size_t V, std::size_t N = NT2_CONFIG_ALIGNMENT> struct align_on_c;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::align_on_c<V,N>::type r;

**Pre-condition:** ``N`` is an integral constant which is power of 2. If this pre-condition is
violated, a ``INVALID_ALIGNMENT_VALUE`` static assertion is thrown at compile-time.

**Return type:** `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef mpl::integral_c<std::size_t, (V+N-1) & ~(N-1)> r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/memory/meta_align_on_c.cpp
   :language: cpp

