.. _type_id:

type_id
=======

.. index::
    single: type_id

Description
^^^^^^^^^^^

Returns a human-readable, demangled type name.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-------------------+--------------------+
  | Parameter | Requirement       | Description        |
  +===========+===================+====================+
  | T         | None              | Type to name       |
  +-----------+-------------------+--------------------+

Parameters
^^^^^^^^^^

  +-----------+---------------------------+
  | Parameter | Description               |
  +===========+===========================+
  | x         | Instance to print type of |
  +-----------+---------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/details/type_id.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    template<class T> inline std::string type_id(const T& x)
    template<class T> inline std::string type_id()
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  type_id(x)

**Return type:** String containing the demangled type name of the type of ``x``

.. code-block:: cpp

  type_id<T>()

**Return type:** String containing the demangled type name of the type ``T``

Example
^^^^^^^

.. literalinclude:: ../../../../modules/sdk/examples/details/type_id.cpp
   :language: cpp
