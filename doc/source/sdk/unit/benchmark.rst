.. _unit_benchmark:

Benchmark Framework
====================

Description
^^^^^^^^^^^
The following macro helps build up a runtime benchmarking

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/unit/benchmark.hpp>

Timing Macros
^^^^^^^^^^^^^

NT2_TIMING
----------

.. index::
    single: NT2_TIMING

**Synopsis:**

.. code-block:: cpp

  #define NT2_TIMING(TAG,ARGS)

**Description:** Generate a timing session to test a |nt2| function identified
by its ``TAG`` and working on inputs which types and value ranges are passed
as the preprocessor sequence of tuples ``ARGS``.

**Example:** The following code performs the timing of `plus` over double
and float within a [-1,1] range.

.. code-block:: cpp

  NT2_TIMING(nt2::functors::plus_, ((double,-1,1))((float,-1,1)) )

NT2_TIMING_EXT
--------------

.. index::
    single: NT2_TIMING_EXT

**Synopsis:**

.. code-block:: cpp

  #define NT2_TIMING_EXT(NAME,TYPE,ARGS)

**Description:** Generate a timing session to test a free function identified
by its ``NAME`` and working on inputs which types and value ranges are passed
as the preprocessor sequence of tuples ``ARGS`` and forcing the return value
to be stored into a value of type ``TYPE``.

**Example:** The following code performs the timing of ``std::cos`` over double
within a [-1,1] range.

.. code-block:: cpp

  NT2_TIMING_EXT(std::cos, double, ((double,-1,1)) )

Configuration
^^^^^^^^^^^^^

NT2_TEST_DURATION
-----------------

.. index::
    single: NT2_TEST_DURATION

**Description:** Define the time in seconds during which the timing should be
run. By default, its value is 2.5s

NT2_TEST_SAMPLES
----------------

.. index::
    single: NT2_TEST_SAMPLES

**Description:** Define the number of sample values to compute during the
timing session. By defualt, its value is 100000.

NT2_TEST_RANDOM_SEED
--------------------

.. index::
    single: NT2_TEST_RANDOM_SEED

**Description:** Define the random seed used to populate the sample values
pool. By default, a value tied to the real world time is used.
