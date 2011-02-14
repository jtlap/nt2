.. _meta_category:

category
========

.. index::
    single: category (meta)
    single: meta; category

Description
^^^^^^^^^^^
Helper type to build custom type category modeling the :ref:`concept_category`
Concept via inheritance. :ref:`meta_category` provides all the needed computation
to order new :ref:`concept_category` with respect to existing ones.

.. seealso:: :ref:`concept_category` :ref:`howto_category`

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/meta/category.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace meta
  {
    template<class T, boost::uint32_t Family, boost::uint32_t Grain>
    struct category
    {
      typedef T                     type;
      static const boost::uint32_t  rank = undefined integral constant;
    };
  } }
