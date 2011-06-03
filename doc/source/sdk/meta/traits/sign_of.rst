.. _meta_sign_of:

sign_of
==========

.. index::
    single: sign_of (meta)
    single: meta; sign_of

Description
^^^^^^^^^^^
Returns ``signed`` if the primitive of the input type is of hierarchy :ref:`tag_signed_`
and ``unsigned`` otherwise.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+----------------------------------------------------------+
  | Parameter | Requirement                  | Description                                              |
  +===========+==============================+==========================================================+ 
  | T         | :ref:`concept_has_primitive` | Input type                                               |
  +-----------+------------------------------+----------------------------------------------------------+

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

.. literalinclude:: ../../../../../modules/sdk/examples/meta/sign_of.cpp
   :language: cpp
