.. _meta_is_fundamental:

is_fundamental
==============

.. index::
    single: is_fundamental (meta)
    single: meta; is_fundamental

Description
^^^^^^^^^^^
Returns true if the type is of hierarchy :ref:`tag_fundamental_` and false otherwise.

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

  #include <nt2/sdk/functor/meta/is_fundamental.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T>
    struct is_fundamental;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::is_fundamental<T>::type r;

**Return type:** ``boost::mpl::true_`` or ``boost::mpl::false_``

**Semantic:** Equivalent to:

.. code-block:: cpp

  typedef boost::is_base_of< fundamental_<T>, hierarchy_of<T>::type > r;
  
.. seealso::

  :ref:`tag_fundamental_`, :ref:`meta_hierarchy_of`

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/meta/is_fundamental.cpp
   :language: cpp
