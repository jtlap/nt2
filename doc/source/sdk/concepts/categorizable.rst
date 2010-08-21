.. _concept_categorizable:

Categorizable
=============

Description
-----------

A :ref:`concept_categorizable` types is a type which :ref:`concept_category`
is not :ref:`tag_unknown`.

Header File
-----------

.. code-block:: cpp

  #include <nt2/sdk/concept/categorizable.hpp>

Invariant
---------

The following invariants always hold:

* ``boost::is_same< meta::category_of<T>::type::tag, tag::unknown>::value``
evaluates to ``false``.

Models
------

* Arithmetic types
