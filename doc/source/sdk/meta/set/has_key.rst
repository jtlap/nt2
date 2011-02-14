.. _meta_has_key:

has_key
=======

.. index::
    single: has_key (meta)
    single: meta; has_key

Description
^^^^^^^^^^^
Detects if a given type is a member of a given :ref:`meta_set`.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/has_key.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class Set, class T> struct has_key;
  } }

Expression semantic
^^^^^^^^^^^^^^^^^^^

For any type ``T`` and any :ref:`meta_set` ``Set``:

.. code-block:: cpp

  typedef has_key<Set,T>::type c;

**Return type:**	Boolean |mpl_int|_

**Semantic:**	``c::value`` evaluates to ``true`` if ``Set`` contains an element
of type ``T``, evaluates to false otherwise.

Example
^^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/has_key.cpp
   :language: cpp
