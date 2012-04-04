.. _compile_time_assert:

Compile-time Assertions
=======================

.. rubric:: Description

A strong compile-time pre- or post-condition is violated and prevent further
compilation of the program. Those errors appears as static assertion with a
custom error message.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/errors/static_assert.hpp>

.. nt2_static_assert:

NT2_STATIC_ASSERT
^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_STATIC_ASSERT

**Synopsis:**

.. code-block:: cpp

  #define NT2_STATIC_ASSERT(EXPR,MSG,T)

**Description:** If compile-time ``EXPR`` evaluates to false, generates a
compile-time assertion with message ``MSG`` and types ``T``.

.. nt2_static_assert_not:

NT2_STATIC_ASSERT_NOT
^^^^^^^^^^^^^^^^^^^^^

**Synopsis:**

.. code-block:: cpp

  #define NT2_STATIC_ASSERT_NOT(EXPR,MSG,T)

**Description:** If compile-time ``EXPR`` evaluates to true, generates a compile-time
assertion with message ``MSG`` and types ``T``.
