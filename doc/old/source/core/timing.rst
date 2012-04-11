.. _timing:

Timing
======

.. index::
    single: time;

.. rubric:: Description

This module provides |MT|-like functions to perform timing of code fragments
in a platform and compiler independent way. These functions either measure elapsed
seconds or CPU cycles and can, optionally, report those measures to standard
output. All these functions works in pairs and can be nested or cross function calls 
as long as they form well-formed enclosing calls.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/core/include/timing.hpp>

.. rubric:: Content

.. toctree::
   :maxdepth: 2

   timing/functions
   timing/classes
