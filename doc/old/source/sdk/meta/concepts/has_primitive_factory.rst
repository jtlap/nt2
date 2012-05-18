.. _concept_has_primitive_factory:

HasPrimitiveFactory
===================

Description
-----------

A model of HasPrimitive is a type from which a primitive type can be extracted,
and which can also be built from a primitive type using a factory.

Refinement of
^^^^^^^^^^^^^

* :ref:`concept_has_primitive`

Notation
^^^^^^^^

``T``
    Model of HasPrimitive

Expression requirements
-----------------------

    +---------------------------+----------------------------+--------------------------------------------+
    | Expression                | Return Type                | Semantics                                  |
    +===========================+============================+============================================+
    | ``factory_of<T>::type``   | Model of |mpl_lambda|_     | The lambda takes a :ref:`tag_fundamental_` |
    |                           |                            | and returns ``T`` rebound to that type.    |
    +---------------------------+----------------------------+--------------------------------------------+


Models
------

* all fundamental types (int, float, ...)
* :ref:`simd_native`
* :ref:`simd_pack`
* Object pointer types

.. seealso::   
    :ref:`meta_factory_of`
