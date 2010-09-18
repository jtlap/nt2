.. _timing_function_ctoc:

ctoc
====

.. index::
    single: time; ctoc()

Description
^^^^^^^^^^^
End a cycle-based timing section.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/tic.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace time
  {
    double    ctoc(bool display = true)
  }

**Parameter:**

  +-------------+---------------+-------------------------+
  | Parameter   | Requirement   | Description             |
  +=============+===============+=========================+
  | ``display`` | Boolean value | Standard output trigger |
  +-------------+---------------+-------------------------+

Expression Semantic
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  double d = ctoc();

**Return type:** ``double``

**Semantics:** Returns the amount of cycles elapsed since the nearest
:ref:`timing_function_ctic` call. If ``display`` is set to true, a message is
send to standard output.

**Exception:** Throws an :ref:`unbalanced_timing` if called without a previous
call to :ref:`timing_function_ctic`.
