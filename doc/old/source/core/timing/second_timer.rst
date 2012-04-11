.. _class_second_timer:

second_timer
============

.. index::
    single: time; time::second_timer

Description
^^^^^^^^^^^
:ref:`class_second_timer` is a RAII-based timing class that performs safe timing
in a given code block and prevents the misuse of the :ref:`timing_function_tic`/
:ref:`timing_function_toc` function pair.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/second_timer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace time
  {
    struct second_timer
    {
       second_timer(double& elapsed, bool display = true);
      ~second_timer();
    };
  }

Constructors and Destructors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

second_timer(double&, bool)
---------------------------

.. index::
    single: time::second_timer; second_timer(double&,bool)

**Synopsis:**

.. code-block:: cpp

  second_timer(double& elapsed, bool display = true)

**Description:** Creates an instance of :ref:`class_second_timer`, links it to
a user-defined variable that will contain the result of the timing when the
current instance goes out of scope and starts a timing section by calling
:ref:`timing_function_tic`. The display parameters specifies if the inner
:ref:`timing_function_toc` call will display the elapsed time to standard
output or not.

.. _second_timer_dtor:

~second_timer()
---------------

**Synopsis:**

.. code-block:: cpp

  ~second_timer()

**Description:**  When an instance of scoped_timer goes out of scope, the
destructor ends a timing section by calling toc or ctoc, puts the result into
the linked variable and options displays it.

Example
^^^^^^^
.. literalinclude:: ../../../../examples/core/timing/second_timer.cpp
   :language: cpp
