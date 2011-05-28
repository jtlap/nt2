.. _meta_dominant:

dominant
========

.. index::
    single: dominant
    single: meta; dominant

Description
^^^^^^^^^^^
For a given list of types, return the category of the type with the greatest
category rank.

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

  typedef result_of<dominant(Args....)>::type r;

**Return type:** an unspecified type

**Semantic:** ``r`` is the category of the first type within ``Args...``
for which its category rank is greater than all other types within ``Args..``

.. code-block:: cpp

  r = dominant(Args....);

**Return type:** Equivalent to ``result_of<dominant(Args....)>::type``

**Semantic:** ``r`` is an instance of the category type of the first type within
``Args...`` for which its category rank is greater than all other types within
``Args...``

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/functor/dominant.cpp
   :language: cpp
