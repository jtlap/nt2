.. _failures:

Runtime Assertions
==================

Description
^^^^^^^^^^^
Runtime assertions report precondition violations by halting the current
application at runtime.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/assert.hpp>

.. _nt2_assert:

NT2_ASSERT
^^^^^^^^^^

.. index::
    single: NT2_ASSERT

**Synopsis:**

.. code-block:: cpp

  #define NT2_ASSERT(COND)

**Description:** If ``COND`` evaluates to ``false``, then a runtime assertion
is emitted, halting the program either via an abort or, if :ref:`nt2_debug` is defined,
by firing a debug trap. If assertions are disabled by :ref`nt2_disable_asserts`,
nothing happens. If :ref:`nt2_asserts_as_exceptions` is defined, an
:ref:`assertion_failure` exception is thrown instead.

