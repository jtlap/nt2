.. _user_defined_configuration:

User-defined Configuration Flags
================================

.. rubric:: Description

|nt2| provide a large array of sub-systems that both the end user or the
extensions developer should be able to configure either globally or
locally. The following preprocessor symbols can be defined or undefined to
tune those customizable behaviors.

.. _nt2_verbose:

NT2_VERBOSE
^^^^^^^^^^^

.. index::
    single: NT2_VERBOSE

When defined, this macro triggers additional warning messages at compile time
that give information about the actual configuration of |nt2|.

Example
-------

The compilation of the following code sample:

.. code-block:: cpp

  #define NT2_VERBOSE
  #include <nt2/include/config.hpp>

  int main() {}

leads to the following compiler output when compiled with g++ on a x86 Linux
machine:

.. code-block:: bash

  nt2/config/arch/x86.hpp:17:6: warning: #warning NT2 Configuration: X86 architecture detected.
  nt2/config/compiler/gcc.hpp:16:6: warning: #warning NT2 Configuration: GNU C/C++ compiler detected.
  nt2/config/os/nix.hpp:17:6: warning: #warning NT2 Configuration: Linux platform detected.

.. _nt2_use_custom_machine_model:

NT2_CUSTOM_BOOTSTRAP
^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_CUSTOM_BOOTSTRAP

When defined, this macro forces |nt2| to look for an external ``bootstrap.hpp``
file located in the ``nt2/extensions/config`` folder.

Example
-------

The compilation of the following code sample:

.. code-block:: cpp

  #define NT2_CUSTOM_BOOTSTRAP arm_model.hpp
  #include <nt2/include/config.hpp>

  int main() {}

makes |nt2| load up ``nt2/extensions/config/arm_model.hpp`` as a machine model
instead of ``nt2/sdk/config/bootstrap.hpp``.
