.. _meta_validate:

validate
========

.. index::
    single: validate
    single: meta; validate

Description
^^^^^^^^^^^
Returns a |mpl_int|_ indicating if a function call using a given ``Tag``
and a given list of argument types is valid within |nt2|.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------------------+---------------------+
  | Parameter | Requirement                       | Description         |
  +===========+===================================+=====================+
  | Tag       | None                              | Tag to call         |
  +-----------+-----------------------------------+---------------------+

Model
^^^^^
|pfo|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/validate.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class Tag> struct validate;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef result_of< validate<Tag>(Args....)>::type r;

**Return type:** a Boolean |mpl_int|_

**Semantic:** Equivalents to

.. code-block:: cpp

  typedef result_of< functor<Tag>::validate(Args....)>::type r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/functor/validate.cpp
   :language: cpp
