.. _concept_has_primitive:

HasPrimitive
============

Description
-----------

A model of HasPrimitive is a type from which a primitive type, i.e. a type
which hierarchy is :ref:`tag_fundamental_`, can be extracted.

Notation
^^^^^^^^

``T``
    Model of HasPrimitive
    
``Primitive``
    Type that verifies :ref:`meta_is_fundamental`

Expression requirements
-----------------------

    +-----------------------------+-------------------------------------------------+-------------+
    | Expression                  | Return Type                                     | Semantics   |
    +=============================+=================================================+=============+
    |  ``primitive_of<T>::type``  | Primitive                                       | unspecified |
    +-----------------------------+-------------------------------------------------+-------------+


Models
------

* all fundamental types (int, float, ...)
* :ref:`simd_native`
* :ref:`simd_pack`
* :ref:`simd_expression`
* all models of `ReadableIterator <http://www.boost.org/doc/libs/release/libs/iterator/doc/new-iter-concepts.html#readable-iterators-lib-readable-iterators>`_
* all models of `SinglePassRange <http://www.boost.org/doc/libs/release/libs/range/doc/html/range/concepts/single_pass_range.html>`_

.. seealso::
    :ref:`meta_primitive_of`
