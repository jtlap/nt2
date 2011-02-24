.. _align_on:

align_on
========

.. index::
    single: align_on
    single: memory; align_on

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

  #include <nt2/sdk/memory/align_on.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace memory
  {
    template<class T>               unspecified_type align_on( T const& v );
    template<std::size_t N,class T> unspecified_type align_on( T const& v );
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  align_on<N>(v)

**Return type:** Type of ``v``

**Semantics:** If ``N`` is a power of 2, returns the integer or address ``w``
greater than ``v`` for which ``w % N == 0``. Otherwise, the function is removed
by :term:`SFINAE`.

.. code-block:: cpp

  align_on(v)

**Return type:** Type of ``v``

**Semantics:** Returns the integer or address ``w`` greater than ``v``
for which ``w % NT2_CONFIG_ALIGNMENT == 0``.

Example
^^^^^^^

The compilation of the following code sample:

.. literalinclude:: ../../../../../examples/sdk/memory/align_on.cpp
   :language: cpp

leads to the following compiler output when compiled with g++ on a Linux machine:

.. code-block:: bash

  0
  4
  12
  1340


