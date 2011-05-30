.. _timestamp:

timestamp
=========

.. index::
    single: timestamp
    single: sys; timestamp

Description
^^^^^^^^^^^

Return a string containing current date and time in a human readable format
based on current locale.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/sys/timestamp.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace sys
  {
    string timestamp();
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  sys::string d = timestamp()

**Return type:** ``sys::string``

**Semantics:** Build a ``string`` using the current platform function for retrieving
formatted date and time.

Example
^^^^^^^

.. literalinclude:: ../../../../modules/sdk/examples/details/timestamp.cpp
   :language: cpp
