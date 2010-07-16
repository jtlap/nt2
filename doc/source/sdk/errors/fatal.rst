.. _failures:

Failures
========

Description
^^^^^^^^^^^
The ``NT2_FAILURE`` macro notify the users that an unrecoverable error occurred
and that the application must terminate.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/failure.hpp>

.. _nt2_failure:

NT2_FAILURE
^^^^^^^^^^^

.. index::
    single: NT2_FAILURE

**Synopsis:**

.. code-block:: cpp

  #define NT2_FAILURE(COND,MSG)

**Description:** If ``COND`` evaluates to ``false``, then the ``MSG`` string
is logged and the application terminates in error.

