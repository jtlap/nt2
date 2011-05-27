.. _meta_is_aligned:

is_aligned
==========

.. index::
    single: is_aligned
    single: meta; is_aligned

Description
^^^^^^^^^^^

Check if an `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_
is aligned on an arbitrary boundary. By default, this boundary is equal to the
system best alignment values provided by the ``bootstrap.hpp`` file.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | V         | Integral Constant            | Value to check     |
  +-----------+------------------------------+--------------------+
  | N         | Power of 2 Integral Constant | Alignment boundary |
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
    template<class V, class N = boost::mpl::size_t<NT2_CONFIG_ALIGNMENT> > struct is_aligned;
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_aligned<V,N>::type r;

**Pre-condition:** ``N`` is an `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_
which is power of 2. If this pre-condition is violated, a ``INVALID_ALIGNMENT_VALUE`` static assertion is thrown at compile-time.

**Return type:** Boolean `Integral Constant <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:** Equivalent to

  .. code-block:: cpp

    typedef boost::mpl::bool_<!(V::value & (N::value-1) )> r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/memory/meta_is_aligned.cpp
   :language: cpp

