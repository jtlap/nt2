.. _configuration_function:

Configuration Status
====================

.. rubric:: Description

The configuration module provides a function to retrieve either complete or partial
information about current settings as a human-readable string.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/config.hpp>

.. rubric:: Synopsis

.. code-block:: cpp

  namespace nt2 { namespace config
  {
    unspecified-type status;
  } }

.. _config_function_status:

status
^^^^^^

.. index::
    single: status
    single: config; status

**Synopsis:**

.. code-block:: cpp

  unspecified-type status

**Description:** ``status`` is a nullary function object that carry out
compile-time information about |nt2| which can be displayed on the standard
output.


.. rubric:: Example

.. literalinclude:: ../../../../examples/sdk/config/status.cpp
   :language: cpp

