.. _assertion_failure:

assert_exception
================

.. index::
    single: assertion_failure

Description
^^^^^^^^^^^
:ref:`assertion_failure` is used when |nt2| assertions are handled as exceptions
via the :ref:`nt2_asserts_as_exceptions` preprocessor symbol.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/errors/assert.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2
  {
    struct assert_exception : virtual nt2::exception
    {
      virtual void display(std::ostream& os) const throw();
    };
  }

Methods
^^^^^^^

void display(ostream&)
----------------------

.. index::
    single: assertion_failure; display()

**Synopsis:**

.. code-block:: cpp

  virtual void display(std::ostream& os) const throw() = 0

**inherited from nt2::exception**

Example
^^^^^^^

.. literalinclude:: ../../../../modules/sdk/examples/details/assertion_failed.cpp
   :language: cpp

The expected output of this code, with respect to platform dependant details, is:

.. code-block:: none

  *************************** NT2 ERROR ****************************
  Raised: Tue Aug 31 19:27:18 2010
  File  : ./examples/sdk/details/assertion_failed.cpp
  Line  : 9
  In    : void f(const T&) [with T = double]
  *******************************************************************
  Assertion: v > 4 failed.
  *******************************************************************
