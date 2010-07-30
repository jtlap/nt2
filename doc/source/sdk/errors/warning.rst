.. _warnings:

Compile-time Warnings
=====================

Description
^^^^^^^^^^^

Some configuration or file inclusion need to warn the user about some errors or
incorrect parametrization during compile-time. If ``gcc`` provide a helpful
``#pragma warning`` construct, it is not portable. The followign macro fix this.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/warning.hpp>

.. _nt2_warning:

NT2_WARNING
^^^^^^^^^^^

.. index::
    single: NT2_WARNING

Synopsis
--------

.. code-block:: cpp

  #define NT2_WARNING(MSG)

Description
------------
Emit a message during compile-time to warn about a file-level error or
misconfiguration.
