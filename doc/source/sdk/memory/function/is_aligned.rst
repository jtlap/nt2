.. is_aligned:

is_aligned
==========

.. index::
    single: is_aligned
    single: aligned; is_aligned

Description
^^^^^^^^^^^

Check if a given value or pointer is aligned on an arbitrary power of 2 bytes
boundary. By default, this boundary is equal to the system best alignment value
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

  +-----------+----------------+
  | Parameter | Description    |
  +===========+================+
  | v         | Value to check |
  +-----------+----------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/memory/is_aligned.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace memory
  {
                                    bool is_aligned( std::size_t v )
    template<class T>               bool is_aligned( T* v )
    template<std::size_t N>         bool is_aligned( std::size_t v )
    template<std::size_t N,class T> bool is_aligned( T* v )
  } }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  is_aligned<N>(v)

**Return type:** ``bool``

**Semantics:** If ``N`` is a power of 2, returns ``v % N == 0``. Otherwise, the
function is pruned through :term:`SFINAE`.

.. code-block:: cpp

  is_aligned(v)

**Return type:** ``bool``

**Semantics:** Returns ``v % NT2_CONFIG_ALIGNMENT == 0``.

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/memory/is_aligned.cpp
   :language: cpp
