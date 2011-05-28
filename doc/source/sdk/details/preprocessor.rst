.. _preprocessor_details:

Preprocessor Helpers
====================

.. rubric:: Description

In addition to the preprocessor macros provided by
`Boost.Preprocessor <http://www.boost.org/doc/libs/release/libs/preprocessor/doc/index.html>`_,
|nt2| provides some macros that simplify some code design.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/sdk/details/preprocessor.hpp>

.. _nt2_pp_debug:

NT2_PP_DEBUG
^^^^^^^^^^^^

.. index::
    single: NT2_PP_DEBUG

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_DEBUG(m)

**Description:** Evaluates the preprocessor argument ``m`` and turn it into a
printable string. This macro is mainly used to debug preprocessor calls.

.. _nt2_pp_index:

NT2_PP_INDEX
^^^^^^^^^^^^

.. index::
    single: NT2_PP_INDEX

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_INDEX(z,n,t)

**Description:** This macro is designed to be used with preprocessor repetition
structures and always return the current repetition iteration index.

**Example:**

.. literalinclude:: ../../../../modules/sdk/examples/details/pp_index.cpp
   :language: cpp

NT2_PP_TEXT
^^^^^^^^^^^

.. index::
    single: NT2_PP_TEXT

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_TEXT(z,n,t)

**Description:** This macro is designed to be used with preprocessor repetition
structures and always returns the current repetition value.

**Example:**

.. literalinclude:: ../../../../modules/sdk/examples/details/pp_text.cpp
   :language: cpp

NT2_PP_ENUM_VALUE
^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_PP_ENUM_VALUE

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_ENUM_VALUE(n,v)

**Description:** This macro generate a comma separated list of ``n``
integer equals to ``v``.

**Example:**

.. literalinclude:: ../../../../modules/sdk/examples/details/pp_enum_value.cpp
   :language: cpp

NT2_PP_ENUM_SHIFTED_VALUE
^^^^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_PP_ENUM_SHIFTED_VALUE

**Synopsis:**

.. code-block:: cpp

  #define NT2_PP_ENUM_SHIFTED_VALUE(n,v)

**Description:** This macro generate a comma separated list of ``n-1``
integer equals to ``v``.

**Example:**

.. literalinclude:: ../../../../modules/sdk/examples/details/pp_enum_shifted_value.cpp
   :language: cpp
