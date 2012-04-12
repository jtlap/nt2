.. _meta_all:

all
===

.. index::
    single: all (meta)
    single: meta; all

Description
^^^^^^^^^^^
Evaluates if a given meta-predicates is true for all types in a type sequence.
``all`` can either work on a `MPL Sequence <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/forward-sequence.html>`_
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
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/all.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class Lambda, class T0, ..., class Tn> struct all;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::all<Lambda,T0,...,Tn>::type r;

**Return type:** a Boolean |mpl_int|_

**Semantic:** If ``T0`` is a `MPL Sequence <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/forward-sequence.html>`_
, equivalent to:

.. code-block:: cpp

  typedef is_same< find_if<T0, not_<Lambda> >::type, end<T0>::type>::type r;

If not, it evaluates to ``boost::mpl::true_`` if ``apply1<Lambda,T>::type``
evaluates to ``boost::mpl::true_`` for all ``T0 ... Tn``. Otherwise, it evaluates
to ``boost::mpl::false_``.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/all.cpp
   :language: cpp
