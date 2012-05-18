.. _nt2_compiler_configuration:

Compiler Configuration
======================

.. rubric:: Description

During compilation of a |nt2| application, |nt2| code detects which kind of
compiler is currently used and define a set of preprocessor symbols that can
be used when developing extensions to handle code variations points.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/config/compiler.hpp>

.. _nt2_compiler_detected:

NT2_COMPILER_DETECTED
^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_COMPILER_DETECTED

This macro is defined when a supported compiler is detected.

.. _nt2_compiler_string:

NT2_COMPILER_STRING
^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_COMPILER_STRING

Defines a string value containing the name of current compiler.

.. _nt2_compiler_gnu_c:

NT2_COMPILER_GNU_C
^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_COMPILER_GNU_C

This macro is defined when a GCC compiler is detected.

.. _nt2_compiler_gnu_c_xml:

NT2_COMPILER_GNU_C_XML
^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_COMPILER_GNU_C_XML

This macro is defined when a GCC-XML compiler is detected.

.. _nt2_compiler_msvcl:

NT2_COMPILER_MSVC
^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_COMPILER_MSVC

This macro is defined when a Microsoft Visual Studio compiler is detected.

.. rubric:: Example

.. literalinclude:: ../../../../examples/sdk/config/compiler.cpp
   :language: cpp
