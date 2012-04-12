.. _preprocessor_include:

Configurable Include Directive
==============================

.. rubric:: Description

In various architecture or operating specific parts, |nt2| needs to be able to
select between various implementations of a given component. To simplify this process,
a customizable include file generation macro helper is provided. This macro is
able to generate a proper include filename from a file name and a macro function
building the path to this file.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/details/preprocessor.hpp>

.. _nt2_pp_include:

NT2_PP_INCLUDE
^^^^^^^^^^^^^^

.. index::
    single: NT2_PP_INCLUDE

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_INCLUDE(PATH,FILE)

**Description:** Build a file path compatible with the include directive by
evaluating ``PATH()`` and concatenating the resulting path to ``FILE``.


**Example:**

.. literalinclude:: ../../../../modules/sdk/examples/details/pp_include.cpp
   :language: cpp
