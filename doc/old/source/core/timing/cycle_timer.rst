.. _class_cycle_timer:

cycle_timer
===========

.. index::
    single: time; time::cycle_timer

Description
^^^^^^^^^^^
:ref:`class_cycle_timer` is a RAII-based timing class that performs safe timing in a given
code block and prevents the misuse of the :ref:`timing_function_ctic`/
:ref:`timing_function_ctoc` function pairs.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/cycle_timer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace time
  {
    struct cycle_timer
    {
       cycle_timer(double& elapsed, bool display = true);
      ~cycle_timer();
    };
  }

Constructors and Destructors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

cycle_timer(double&, bool)
---------------------------

.. index::
    single: time::cycle_timer; cycle_timer(double&,bool)

**Synopsis:**

.. code-block:: cpp

  cycle_timer(double& elapsed, bool display = true);

**Description:** Creates an instance of :ref:`class_cycle_timer`, links it to
a user-defined variable that will contain the result of the timing when the
current instance goes out of scope and starts a timing section by calling
:ref:`timing_function_ctic`. The display parameters specifies if the inner
:ref:`timing_function_ctoc` call will display the elapsed time to standard
output or not.

Example
^^^^^^^

.. literalinclude:: ../../../../examples/core/timing/cycle_timer.cpp
   :language: cpp
