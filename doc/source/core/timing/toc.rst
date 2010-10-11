.. _timing_function_toc:

toc
===

.. index::
    single: time; toc()

Description
^^^^^^^^^^^
End a second-based timing section.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/tic.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  double toc(bool display = true);

**Parameter:**

  +-------------+---------------+-------------------------+
  | Parameter   | Requirement   | Description             |
  +=============+===============+=========================+
  | ``display`` | Boolean value | Standard output trigger |
  +-------------+---------------+-------------------------+

Expression Semantic
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  double d = toc();

**Return type:** ``double``

**Semantics:** Returns the amount of seconds elapsed since the nearest
:ref:`timing_function_tic` call. If ``display`` is set to true, a message is
send to standard output.

Exception
^^^^^^^^^

Throws an :ref:`unbalanced_timing` if called without a previous call to
:ref:`timing_function_tic`.
