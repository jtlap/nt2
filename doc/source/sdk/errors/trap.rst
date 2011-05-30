.. _trap:

Debug Traps
===========

Description
^^^^^^^^^^^
The ``trap`` template function inserts a platform specific debugging trap if a
given meta-function evaluates to ``true``. Its main usage is to generate template
based breakpoint in some instantiations of template classes.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/trap.hpp>

.. _nt2_trap:

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace sys
  {
    template<class Condition> void trap();
  } }

Expression Semantic
^^^^^^^^^^^^^^^^^^^

If ``Condition::value`` evaluates to ``true``, a code inducing a forced
debugger breakpoint will be generated. Otherwise, no operation is generated.
