.. _meta_is_unspecified:

is_fundamental
==============

.. index::
    single: is_unspecified (meta)
    single: meta; is_unspecified

Description
^^^^^^^^^^^
Returns true if the type is of hierarchy :ref:`tag_unspecified_` and false otherwise.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+----------------------------------------------------------+
  | Parameter | Requirement                  | Description                                              |
  +===========+==============================+==========================================================+ 
  | T         | None                         | Input type                                               |
  +-----------+------------------------------+----------------------------------------------------------+

Model
^^^^^
|metafunction|_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/is_unspecified.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct is_unspecified;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_fundamental<T>::type r;

**Return type:** ``boost::mpl::true_`` or ``boost::mpl::false_``

.. code-block:: cpp

  typedef boost::is_base_of< unspecified_<T>, hierarchy_of<T>::type > r;

.. seealso::

  :ref:`tag_unspecified_`, :ref:`meta_hierarchy_of`

Example
^^^^^^^

.. literalinclude:: ../../../../../examples/sdk/meta/is_unspecified.cpp
   :language: cpp
