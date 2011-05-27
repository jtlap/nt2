.. _nt2_throw:

NT2_THROW
=========

Description
^^^^^^^^^^^

The ``NT2_THROW`` macro reports misbehavior by throwing an exception containing
potential diagnostic information. It is based on Boost.Exception and support the
same semantic than ``BOOST_THROW``.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/error.hpp>

NT2_THROW
^^^^^^^^^

.. index::
    single: NT2_THROW

**Synopsis:**

.. code-block:: cpp

  #define NT2_THROW(X)

**Description:**
If exceptions are enabled, throws the exception passed as arguments. If not,
performs a no-op.

