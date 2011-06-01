.. _functor_hierarchy:

Types Hierarchical Sets
=======================

Description
^^^^^^^^^^^
Considering the amount of tag dispatched based code needed by |nt2| functions implementation,
|nt2| provides a list of types sets. Those sets can be used together with meta-functions
like :ref:`meta_belong_to` to perform fine to coarse grain type categorization.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/hierarchy.hpp>

Empty Set
^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<>  empty_;
    }

Description
-----------
The ``empty_`` is used as a default, catch-all set for error handling during the
:term:`Tag Dispatching` process

Boolean Set
^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<bool>  bool_;}

Description
-----------
The ``bool_`` set identifies boolean types.

Integral Sets
^^^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<uint8_t ,int8_t >  int8_;
      typedef set<uint16_t,int16_t>  int16_;
      typedef set<uint32_t,int32_t>  int32_;
      typedef set<uint64_t,int64_t>  int64_;
    }

Description
-----------
Integral sets discriminate integral types with respect to their size.

Sized Sets
^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<uint8_t, int8_t >        types8_;
      typedef set<uint16_t,int16_t>        types16_;
      typedef set<uint32_t,int32_t,float>  types32_;
      typedef set<uint64_t,int64_t,double> types64_;
    }

Description
-----------
Sized sets discriminate types with respect to their size.

Integral Signed Sets
^^^^^^^^^^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<uint8_t,uint16_t,uint32_t,uint64_t>  uint_;
      typedef set<int8_t,int16_t,int32_t,int64_t>      int_;
    }

Description
-----------
Integral Signed sets discriminate integral types with respect to their signedness.

Signed Sets
^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<uint8_t,uint16_t,uint32_t,uint64_t>            unsigned_;
      typedef set<float,double,int8_t,int16_t,int32_t,int64_t>   signed_;
    }

Description
-----------
Signed sets discriminate types with respect to their signedness.

Integral Set
^^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

    namespace functors
    {
      typedef set<uint8_t,uint16_t,uint32_t,uint64_t, int8_t ,int16_t ,int32_t ,int64_t>  integer_;
    }

Description
-----------
Discriminate any integral type.

Real Set
^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

      namespace functors
      {
        typedef set<float,double> real_;
      }

Description
-----------
Discriminate any floating-point type.

Arithmetic Set
^^^^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

      namespace functors
      {
        typedef set<uint8_t,uint16_t,uint32_t,uint64_t,int8_t,int16_t,int32_t,int64_t,float,double> arithmetic_;
      }

Description
-----------
Discriminate any arithmetic type.

Fundamental Set
^^^^^^^^^^^^^^^

Synopsis
--------

  .. code-block:: cpp

      namespace functors
      {
        typedef set<uint8_t,uint16_t,uint32_t,uint64_t,int8_t,int16_t,int32_t,int64_t,float,double,bool> fundamental_;
      }

Description
-----------
Discriminate any fundamental type.
