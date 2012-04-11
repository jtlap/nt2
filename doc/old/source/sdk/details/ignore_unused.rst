.. _ignore_unused:

ignore_unused
=============

.. index::
    single: ignore_unused

Description
^^^^^^^^^^^
In some :term:`SFINAE` enabled code, some functions parameters may be declared but not
used in a given implementation. Calling this function on such parameters prevent
some compilers to generate unwanted warnings in those cases. ``ignore_unused``
performs a no-op on its argument so compilers won't complain about it being unused.

Parameters
^^^^^^^^^^

  +-----------+---------------------------+
  | Parameter | Description               |
  +===========+===========================+
  | x         | Variable to silence       |
  +-----------+---------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/details/ignore_unused.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    template<class T> inline void ignore_unused(const T& x)
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    ignore_unused(x)

**Semantic:** Perform a no-op on ``x``.

Example
^^^^^^^

.. literalinclude:: ../../../../modules/sdk/examples/details/ignore_unused.cpp
   :language: cpp
