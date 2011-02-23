.. _memories:

memories
========

.. index::
    single: memories

Description
^^^^^^^^^^^

``memories`` print the memory alignment and allocation used on the current platform.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/memory/report.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace config
  {
    inline void memories()
  } }

Example
^^^^^^^^

The compilation of the following code sample:

.. literalinclude:: ../../../../../examples/sdk/memory/report.cpp
   :language: cpp

leads to the following compiler output when compiled with g++ on a posix machine:

.. code-block:: bash

  Memory alignment        : 64
  Memory allocation       : posix_memalign


