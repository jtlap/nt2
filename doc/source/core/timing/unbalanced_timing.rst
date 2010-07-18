.. _unbalanced_timing:

unbalanced_timing
=================

.. index::
    single: unbalanced_timing

Description
^^^^^^^^^^^
:ref:`unbalanced_timing` is thrown when the number of :ref:`timing_function_tic` 
or :ref:`timing_function_ctic` calls doesn't match the number of :ref:`timing_function_toc` 
or :ref:`timing_function_ctoc` calls.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/core/timing/unbalanced_timer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  struct unbalanced_timing : virtual nt2::exception
  {
    virtual void display(std::ostream& os) const throw();
  };

.. _unbalanced_timer_methods:

Methods
^^^^^^^

.. _unbalanced_timer_method_display:

void display(ostream&)
----------------------

.. index::
    single: invalid_pointer; display()

**Synopsis:**

.. code-block:: cpp

  virtual void display(std::ostream& os) const throw() = 0

**inherited from nt2::exception**
