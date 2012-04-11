.. _meta_na:

na_
===

.. index::
    single: na_ (meta)
    single: meta; na_

Description
^^^^^^^^^^^
Nilpotent type for use in compile-time container in place of ``boost::mpl::na_``
to prevent unwanted ADL in some use cases.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/na.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    struct na_;
  } }
