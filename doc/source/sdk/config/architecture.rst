.. _nt2_architecture_configuration:

Architecture Configuration
==========================

.. rubric:: Description

During compilation of a |nt2| application, |nt2| code detects which kind of
architecture is currently used and define a set of preprocessor symbols that can
be used when developing extensions to handle code variations points.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/config/arch.hpp>

.. _nt2_arch_detected:

NT2_ARCH_DETECTED
^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_DETECTED

This macro is defined when a supported architecture is detected.

.. _nt2_arch_string:

NT2_ARCH_STRING
^^^^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_STRING

Defines a string value containing the name of current architecture.

.. _nt2_arch_alignment:

NT2_ARCH_ALIGNMENT
^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_ALIGNMENT

Defines a value that represent the number of bytes on which memory should be
aligned on current architecture.

.. _nt2_arch_ia64:

NT2_ARCH_IA64
^^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_IA64

This macro is defined when |nt2| is compiled on IA64 architecture.

.. _nt2_arch_powerpc:

NT2_ARCH_POWERPC
^^^^^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_POWERPC

This macro is defined when |nt2| is compiled on PowerPC architecture.

.. _nt2_arch_x86:

NT2_ARCH_X86
^^^^^^^^^^^^

.. index::
    single: NT2_ARCH_X86

This macro is defined when |nt2| is compiled on X86 architecture.

.. rubric:: Example

.. literalinclude:: ../../../../examples/src/architecture.cpp
   :language: cpp
