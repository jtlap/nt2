.. _configuration_function:

Configuration Status
====================

.. rubric:: Description

The configuration module provide function to retrieve either complete or partial
informations about current settings as a human-readable string.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/config/status.hpp>

.. rubric:: Synopsis

.. code-block:: cpp

  namespace nt2 { namespace config
  {
    const char* status();
    const char* os();
    const char* compiler();
    const char* architecture();
  } }

.. _config_function_status:

status()
^^^^^^^^

.. index::
    single: status()

**Synopsis:**

.. code-block:: cpp

  const char* status()

**Description:** Returns a constant string containing a human-readable summary
of all active compile-time configuration settings of the current application.

.. _config_function_os:

os()
^^^^

.. index::
    single: os()

**Synopsis:**

.. code-block:: cpp

  const char* os()

**Description:** Returns a constant string containing the OS settings
of the current application.

.. _config_function_compiler:

compiler()
^^^^^^^^^^

.. index::
    single: compiler()

**Synopsis:**

.. code-block:: cpp

  const char* compiler()

**Description:** Returns a constant string containing the compiler used to compile
current application.

.. _config_function_arch:

architecture()
^^^^^^^^^^^^^^

.. index::
    single: architecture()

**Synopsis:**

.. code-block:: cpp

  const char* architecture()

**Description:** Returns a constant string containing the architecture settings
of the current application.
