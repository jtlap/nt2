.. _failures:

Failures
========

Description
^^^^^^^^^^^
The ``NT2_FAILURE`` macro notify the users that an unrecoverable error occurred
and that the applciation msut terminate.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/failure.hpp>

.. nt2_failure:

NT2_FAILURE
^^^^^^^^^^^

.. index::
    single: NT2_FAILURE

**Synopsis:**

.. code-block:: cpp

  #define NT2_FAILURE(COND,MSG)

**Description:** If ``COND`` evaluates to ``false``, then the ``MSG`` string
is logged and the applciation terminates in error.

