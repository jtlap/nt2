.. _concept_check:

Concept Checking
================

.. rubric:: Description

A compile-time Concept is violated and prevent further correct compilation of
the program. Those errors appears as static assertion with a custom error message.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/errors/concepts.hpp>

.. _nt2_use_concepts:

NT2_USE_CONCEPTS
^^^^^^^^^^^^^^^^

.. index::
    single: NT2_USE_CONCEPTS

When defined, this macro triggers the use of compile-time concept check in key
points of |nt2| internal code, preventing some compile-time errors earlier.

Concept checking is a powerful tool to assert correctness of template programs
and other generative programming idioms. However, current implementation of
Concept checking is rather demanding in term of compilation time. This macro
allows developer to check for non-obvious template related errors at compile time
and can be disabled if no such errors are found.

.. _nt2_concept_assert:

NT2_CONCEPT_ASSERT
^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_CONCEPT_ASSERT

**Synopsis:**

.. code-block:: cpp

  #define NT2_CONCEPT_ASSERT(CONCEPT)

**Description:** Check if the Concepts class passed as argument is actually
fulfilled in current class or function scope.

.. _nt2_concept_require:

NT2_CONCEPT_REQUIRE
^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_CONCEPT_REQUIRE

**Synopsis:**

.. code-block:: cpp

  #define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)

**Description:** Check if the Concepts class passed as argument is actually
fulfilled in current function signature. If all Concepts are fulfilled, the
function is allowed to return type ``TYPE``
