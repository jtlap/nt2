.. _load:

load
====

.. index::
    single: load

Description
^^^^^^^^^^^

Load a value from a memory block and an offset.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-------------------+--------------------+
  | Parameter | Requirement       | Description        |
  +===========+===================+====================+
  | N         | Integer Constant  | Local memory offset|
  +-----------+-------------------+--------------------+
  | T         | None              | Type to load       |
  +-----------+-------------------+--------------------+

Parameters
^^^^^^^^^^

  +-----------+------------------------------------------+
  | Parameter | Description                              |
  +===========+==========================================+
  | ptr       | Base address of the memory block to load |
  +-----------+------------------------------------------+
  | offset    | Offset the memory block to load          |
  +-----------+------------------------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/memory/load.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    template<class T, class P,class O>               T load(P const& ptr, O const& offset );
    template<std::size_t N,class T, class P,class O> T load(P const& ptr, O const& offset );
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  load<T>(ptr,offset)

**Return type:** ``T``

**Semantics:** Return an instance of ``T`` containing the data loaded from the
address ``ptr+offset``.

.. code-block:: cpp

    load<T,N>(ptr,offset)

**Return type:** ``T``

**Semantics:** Return an instance of ``T`` containing the data loaded from the
address ``ptr+offset+N`` if ``T`` is a scalar type and from an implementation
specific address otherwise (see other load function specialization documentation).

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/operator/examples/memory/load.cpp
   :language: cpp
