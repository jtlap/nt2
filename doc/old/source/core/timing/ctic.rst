.. _timing_function_ctic:

ctic
====

.. index::
    single: time; ctic()

Description
^^^^^^^^^^^
Start a cycle-based timing section.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/tic.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace time
  {
    void    ctic()
  }

Expression Semantic
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  ctic();

**Semantics:** Starts a cycle-based timing section that will be ended by the
nearest :ref:`timing_function_ctoc` call.
