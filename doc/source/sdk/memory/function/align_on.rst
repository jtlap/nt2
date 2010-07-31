.. _align_on:

align_on
========

.. index::
    single: align_on
    single: aligned; align_on

Description
^^^^^^^^^^^

Align a given value or address on an arbitray power of 2 bytes boundary.
By default, this boundary is equal to the system best alignment value
provided by the ``bootstrap.hpp`` file.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-------------------+--------------------+
  | Parameter | Requirement       | Description        |
  +===========+===================+====================+
  | N         | Integer Constant  | Alignment boundary |
  +-----------+-------------------+--------------------+
  | T         | None              | Pointer type       |
  +-----------+-------------------+--------------------+

Parameters
^^^^^^^^^^

  +-----------+---------------------------+
  | Parameter | Description               |
  +===========+===========================+
  | v         | Value or pointer to align |
  +-----------+---------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/alignment/align_on.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace aligned
  {
                                    std::size_t align_on( std::size_t v );
    template<class T>               T*          align_on( T* v );
    template<std::size_t N>         std::size_t align_on( std::size_t v );
    template<std::size_t N,class T> T*          align_on( T* v );
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  align_on<N>(v)

**Return type:** Type of ``v``

**Semantics:** If ``N`` is a power of 2, returns the an integer or address ``w``
greater than ``v`` for which ``w % N == 0``. Otherwise, the function is removed
by :term:`SFINAE`.

.. code-block:: cpp

  align_on(v)

**Return type:** Type of ``v``

**Semantics:** Returns the an integer or address ``w`` greater than ``v``
for which ``w % NT2_CONFIG_ALIGNMENT == 0``.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/memory/align_on.cpp
   :language: cpp
