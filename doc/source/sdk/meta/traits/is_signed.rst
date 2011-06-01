.. _meta_is_signed:

is_signed
==========

.. index::
    single: is_signed (meta)
    single: meta; is_signed

Description
^^^^^^^^^^^
Returns (meta) true if the primitive of the input type is of hierarchy :ref:`tag_signed_` and 
(meta) false otherwise.

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

  #include <nt2/sdk/functor/meta/is_signed.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct is_signed;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_signed<T>::type r;

**Return type:** ``boost::mpl::true_`` or ``boost::mpl::false_``


Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/is_signed.cpp
   :language: cpp
