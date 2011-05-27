.. _store:

store
=====

.. index::
    single: store

Description
^^^^^^^^^^^

store a value into memory block from an address and an offset.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-------------------+--------------------+
  | Parameter | Requirement       | Description        |
  +===========+===================+====================+
  | Value     | None              | Type to store      |
  +-----------+-------------------+--------------------+
  | Ptr       | None              | Address Type       |
  +-----------+-------------------+--------------------+
  | Offset    | None              | Offset Type        |
  +-----------+-------------------+--------------------+

Parameters
^^^^^^^^^^

  +-----------+-------------------------------------------+
  | Parameter | Description                               |
  +===========+===========================================+
  | v         | value to store into memory                |
  +-----------+-------------------------------------------+
  | ptr       | Base address of the memory block to store |
  +-----------+-------------------------------------------+
  | offset    | Offset the memory block to store          |
  +-----------+-------------------------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/include/functions/store.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    template<class Value, class Ptr, class Offset>  Value store(Value const& v, Ptr const& ptr, Offset const& o);
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  store(value,ptr,offset)

**Return type:** type of ``value``

**Semantics:** Return the instance of ``Value`` that is also stored at the address ``ptr+offset``.

Example
^^^^^^^

.. literalinclude:: ../../../../modules/operator/examples/memory/store.cpp
   :language: cpp
