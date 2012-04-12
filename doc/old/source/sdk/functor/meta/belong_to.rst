.. _meta_belong_to:

belong_to
=========

.. index::
    single: belong_to
    single: meta; belong_to

Description
^^^^^^^^^^^
Returns a Returns a |mpl_int|_ indicating if a given type ``T`` belongs to a
given types set ``S`` or is the same type than ``S``.

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+-----------------------------------+---------------------+
  | Parameter | Requirement                       | Description         |
  +===========+===================================+=====================+
  | T         | None                              | Type to check       |
  +-----------+-----------------------------------+---------------------+
  | S         | None                              | Reference types set |
  +-----------+-----------------------------------+---------------------+

Model
^^^^^
`Tag-Dispatched Metafunction <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/tag-dispatched-metafunction.html>`_

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/meta/belong_to.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace meta
  {
    template<class T, class S> struct belong_to;
  }

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  typedef nt2::meta::belong_to<T,S>::type r;

**Return type:** a Boolean |mpl_int|_

**Semantic:** If ``S`` is a :ref:`meta_set`, equivalent to:

.. code-block:: cpp

  typedef has_key<S,T>::type r;

If not, equivalent to:

.. code-block:: cpp

  typedef is_same<T,S>::type r;

Example
^^^^^^^

.. literalinclude:: ../../../../../modules/sdk/examples/functor/belong_to.cpp
   :language: cpp
