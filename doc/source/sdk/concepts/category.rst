.. _concept_category:

Category
========

Description
-----------

A :ref:`concept_category` discriminates types in the context of a |nt2| function
call or functor instanciation and helps dispatching said call to the proper
function implementation.

Header File
-----------

.. code-block:: cpp

  #include <nt2/sdk/concept/category.hpp>

Compile-time Expression Requirements
-------------------------------------

For any type ``T`` modeling the :ref:`concept_category` Concept, the following
compile-time expression are defined.

  +-------------+-----------------+
  | Expression  | Expression Type |
  +=============+=================+
  | ``T::tag``  | Any type        |
  +-------------+-----------------+
  | ``T::rank`` | |mpl_int|_      |
  +-------------+-----------------+

Compile-time Expression Semantics
---------------------------------

  +-------------+----------------------------------------------------------------------------------+
  | Expression  | Semantic                                                                         |
  +=============+==================================================================================+
  | ``T::tag``  | An unique type discriminating the :ref:`concept_category`                        |
  +-------------+----------------------------------------------------------------------------------+
  | ``T::rank`` | The :ref:`concept_category` numeric rank among all other :ref:`concept_category` |
  +-------------+----------------------------------------------------------------------------------+

Invariant
---------

The following invariants always hold:

* If ``T`` is not :ref:`tag_unknown`, then ``T::rank`` < ``tag::unknown::rank``.

Models
------

* :ref:`tag_unknown`
