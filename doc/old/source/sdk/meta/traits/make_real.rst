.. _meta_make_real:

make_real
=========

.. index::
    single: make_real (meta)
    single: meta; make_real

Description
^^^^^^^^^^^
Builds a built-in floating-point type from a size in bytes.
Can also take an optional lambda argument to apply to the result.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------+----------------------------------------------+
  | Parameter | Requirement           | Description                                  |
  +===========+=======================+==============================================+ 
  | Size      | std::size_t           | Size in bytes of desired floating-point type |
  +-----------+-----------------------+----------------------------------------------+
  | Lambda    | |mpl_lambda|_         | Transform to apply to the result             |
  +-----------+-----------------------+----------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/make_real.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class Size, class Lambda = na> struct make_real;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::make_real<Size, Lambda>::type r;

**Return type:** :ref:`tag_real_`

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef boost::mpl::apply1<Lambda, typename meta::make_real<Size>::type>::type r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/make_real.cpp
   :language: cpp
