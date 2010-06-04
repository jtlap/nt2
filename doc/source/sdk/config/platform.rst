.. _os_configuration:

Operating System Configuration
==============================

.. rubric:: Description

During compilation of a |nt2| application, |nt2| code detects which kind of
operating system is currently used and define a set of preprocessor symbols
that can be used when developing extensions to handle code variations points.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/config/os.hpp>

.. _nt2_os_detected:

NT2_OS_DETECTED
^^^^^^^^^^^^^^^

.. index::
    single: NT2_OS_DETECTED

This macro is defined when a supported OS is detected.

.. _nt2_os_string:

NT2_OS_STRING
^^^^^^^^^^^^^

.. index::
    single: NT2_OS_STRING

Defines a string value containing the name of current OS.

.. _nt2_os_mac_os:

NT2_OS_MAC_OS
^^^^^^^^^^^^^

.. index::
    single: NT2_OS_MAC_OS

This macro is defined when |nt2| is compiled on Mac OS X.

.. _nt2_os_linux:

NT2_OS_LINUX
^^^^^^^^^^^^

.. index::
    single: NT2_OS_MAC_LINUX

This macro is defined when |nt2| is compiled on Linux.

.. _nt2_os_windows:

NT2_OS_WINDOWS
^^^^^^^^^^^^^^

.. index::
    single: NT2_OS_MAC_WINDOWS

This macro is defined when |nt2| is compiled on Windows.

.. rubric:: Example

.. literalinclude:: ../../../../examples/sdk/config/platform.cpp
   :language: cpp
