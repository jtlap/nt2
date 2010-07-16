.. _meta_join:

join
====

.. index::
    single: join (meta)
    single: meta; join

Description
^^^^^^^^^^^
Given two :ref:`meta_set`, lazily builds a set which is the union of its two
arguments.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/join.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class S1, class S2> struct join;
  } }


Example
^^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/join.cpp
   :language: cpp
