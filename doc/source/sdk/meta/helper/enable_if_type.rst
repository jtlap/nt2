.. _meta_enable_if_type:

enable_if_type
==============

.. index::
    single: enable_if_type

Description
^^^^^^^^^^^
Silently checks if a given type ``T`` is actually defined and allows
:term:`SFINAE` based operations if it is not.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------------------+--------------------+
  | Parameter | Requirement                       | Description        |
  +===========+===================================+====================+
  | T         | None                              | Type to check for  |
  +-----------+-----------------------------------+--------------------+
  | R         | None                              | Return type        |
  +-----------+-----------------------------------+--------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/enable_if_type.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class R=void>  struct enable_if_type;
  }

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/enable_if_type.cpp
   :language: cpp
