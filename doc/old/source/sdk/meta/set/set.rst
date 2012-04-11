.. _meta_set:

set
===

.. index::
    single: set (meta)
    single: meta; set

Description
^^^^^^^^^^^
Defines a compile-time set of types similar in principles to
`Boost.MPL set class <http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/set.html>`_
but optimized to be  immutable, which means that it doesn't support insertion
nor deletion of key and has a preprocessor based maximum size.

.. warning::

  This class have been implemented to reduce compilation time of |nt2| client
  code. Removing it in favor of ``boost::mpl::set`` have to be carefully
  tested and discussed.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/set.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class T... > struct set;
  } }

Configuration
^^^^^^^^^^^^^

The maximum number of types to be stored in a :ref:`meta_set` is controlled by
the ``NT2_META_SET_SIZE`` which is set to 5 by default.
