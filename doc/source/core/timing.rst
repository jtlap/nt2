.. _timing:

Timing
======

.. index::
    single: time;

.. rubric:: Description

This module provides Matlab-like functions to perform timing of code fragment
in a platform, compiler independant way. Those functions either measure elapsed
seconds or CPU cycles and can, optionnaly, reports those measures to the standard
output. All those functions works in pair and can be nested or cross functions
calls as long as their form well-formed enclosing calls.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/core/include/timing.hpp>

.. rubric:: Content

.. toctree::
   :maxdepth: 2

   timing/functions
   timing/classes
