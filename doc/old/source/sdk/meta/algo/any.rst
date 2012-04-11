.. _meta_any:

any
===

.. index::
    single: any (meta)
    single: meta; any

Description
^^^^^^^^^^^
Evaluates if a given meta-predicates is true for at least one type in a type sequence.
``any`` can either work on a `MPL Sequence <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/forward-sequence.html>`_
or a linear list of types.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +---------------------+-----------------------+---------------------+
  | Parameter           | Requirement           | Description         |
  +=====================+=======================+=====================+
  | ``T0`` ,..., ``Tn`` | None                  | Types to check      |
  +---------------------+-----------------------+---------------------+
  | ``Lambda``          | MPL Lambda Expression | Predicate           |
  +---------------------+-----------------------+---------------------+

Model
^^^^^
`Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/any.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class Lambda, class T0, ..., class Tn> struct any;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::any<Lambda,T0,...,Tn>::type r;

**Return type:** a Boolean |mpl_int|_

**Semantic:** If ``T0`` is a `MPL Sequence <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/forward-sequence.html>`_
, equivalent to:

.. code-block:: cpp

  typedef not_<is_same< boost::mpl::find_if<T0,Lambda>::type, boost::mpl::end<T0>::type> >::type r;

If not, it evaluates to ``boost::mpl::true_`` if it exists a type ``T`` in ``T0 ... Tn``
for which ``apply1<Lambda,T>::type`` evaluates to ``boost::mpl::true_``. Otherwise, it evaluates
to ``boost::mpl::false_``.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/any.cpp
   :language: cpp
