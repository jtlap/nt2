General Parameters
==================

.. rubric:: Description
Various global settings of |nt2| can be customized by being redefined by the
users.

.. rubric:: Header File

.. code-block:: cpp

  #include <nt2/extension/parameters.hpp>

.. rubric:: Preprocessor Symbols

NT2_MAX_DIMENSIONS
------------------

.. index::
    single: NT2_MAX_DIMENSIONS

**Synopsis:**

.. code-block:: cpp

  #define NT2_MAX_DIMENSIONS

**Description:**
This macro controls the maximum number of dimensions unbounded containers may
holds. Default value is 4.

NT2_DEFAULT_INDEX
-----------------

.. index::
    single: NT2_DEFAULT_INDEX

**Synopsis:**

.. code-block:: cpp

  #define NT2_DEFAULT_INDEX

**Description:**
This macro controls the default base index used in containers.
Default value is 1.
