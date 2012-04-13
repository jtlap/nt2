.. _meta_is_set:

is_set
======

.. index::
    single: is_set (meta)
    single: meta; is_set

Description
^^^^^^^^^^^
Detects if a given type is indeed a :ref:`meta_set`.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/is_set.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class T> struct is_set;
  } }

Expression semantic
^^^^^^^^^^^^^^^^^^^

For any type ``T``:

.. code-block:: cpp

  typedef is_set<T>::type c;

**Return type:**	Boolean
`Integral Constant <http://www.boost.org/doc/libs/1_43_0/libs/mpl/doc/refmanual/integral-constant.html>`_

**Semantic:**	``c::value`` evaluates to ``true`` if ``T`` is a :ref:`meta_set`
and to ``false`` otherwise.

Example
^^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/is_set.cpp
   :language: cpp
