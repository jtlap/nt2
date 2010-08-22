.. _meta_dominant:

dominant
========

.. index::
    single: dominant
    single: meta; dominant

Description
^^^^^^^^^^^
For a given list of types, return the type with the greatest category rank.

Model
^^^^^
|pfo|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/dominant.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    struct dominant;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef result_of< dominant(Args....)>::type r;

**Return type:** an unspecified type

**Semantic:** ``r`` is the first type within ``Args...`` for which its category
rank is greater than all other types within ``Args..``

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/functor/dominant.cpp
   :language: cpp
