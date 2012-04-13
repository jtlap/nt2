.. _config:

Compile-time Configuration
==========================

.. rubric:: Description

This module defines a compile-time machine model gathering information
about the architecture, compiler, operating systems used to compile current
application.

|nt2| compilation model relies on a compile-time machine-model. This model allows
the library to resolve as much code generation choices as possible at compile-time,
thus ensuring a fast runtime behavior.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/include/config.hpp>

.. rubric:: Content

.. toctree::
   :maxdepth: 1

   config/architecture
   config/compiler
   config/platform
   config/flags
   config/function
