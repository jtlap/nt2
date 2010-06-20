.. _warnings:

Warnings
========

Description
^^^^^^^^^^^

Some function or methods may want to report some misbehavior by warning the user
that something strange but not necesseraliy wrong happened. The ``NT2_WARNING``
macro actually reports a message to the user by sending it to some predefined
output that can be examined later.

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
By default, this macro send a formatted message including date, time, file, line,
function name and user message indicating that a warning was emitted.
