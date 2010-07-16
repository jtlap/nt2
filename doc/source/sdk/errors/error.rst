.. _errors:

Errors
======

Description
^^^^^^^^^^^

The ``NT2_ERROR`` reports misbehavior by throwing an exception containing
potential diagnostic information.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/error.hpp>

.. _nt2_error:

NT2_ERROR
^^^^^^^^^

.. index::
    single: NT2_ERROR

**Synopsis:**

.. code-block:: cpp

  #define NT2_ERROR(EXC, INFOSEQ)

**Description:**
By default, this macro throw an exception of type ``EXC`` filled with the
diagnostic information extracted from ``INFOSEQ``.

