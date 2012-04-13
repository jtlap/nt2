.. _abs:

abs
==========

.. index::
    single: abs

Description
^^^^^^^^^^^


Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/include/functions/abs.hpp>

or 

.. code-block:: cpp

  #include <nt2/toolbox/arithmetic/functions/abs.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp
    template <class A0>
    unspecified  abs( const A0& a0 );

Expression Semantics
^^^^^^^^^^^^^^^^^^^^

For any ``a0`` modeling :ref:`concept_categorizable`, the expression:

.. code-block:: cpp

   type r = abs(a0)

computes ... .

**Return type:** an unspecified type depending on the :ref:`concept_category`
of input(s) parameters(s).

Supported Categories Semantics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Specific information about ``abs`` semantic can be found here:
* :ref:`scalar_abs`
* :ref:`simd_abs`
.. commentaire

Example  --> pas ici
^^^^^^^

.. literalinclude:: $self.path2examples2$/examples/src/abs.cpp
   :language: cpp

External links
^^^^^^^^^^^^^^

    `matlab <http:\\>`_