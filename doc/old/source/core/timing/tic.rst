.. _timing_function_tic:

tic
===

.. index::
    single: time; tic()

Description
^^^^^^^^^^^
Start a second-based timing section.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/tic.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  void    tic();

Expression Semantic
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  tic();

**Semantics:** Starts a second-based timing section that will be ended by the
nearest :ref:`timing_function_toc` call.
