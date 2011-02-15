.. _meta_sign_of:

sign_of
==========

.. index::
    single: sign_of (meta)
    single: meta; sign_of

Description
^^^^^^^^^^^
Returns ``signed`` if the input type is a :ref:`tag_signed_` type and ``unsigned`` otherwise.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+----------------------------+----------------------------------------------------------+
  | Parameter | Requirement                | Description                                              |
  +===========+============================+==========================================================+ 
  | T         | None                       | Input type                                               |
  +-----------+----------------------------+----------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/sign_of.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct sign_of;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::sign_of<T>::type r;

**Return type:** ``signed`` or ``unsigned``


Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/sign_of.cpp
   :language: cpp
