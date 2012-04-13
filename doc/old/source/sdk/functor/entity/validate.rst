.. _functor_validate:

validate
========

.. index::
    single: validate

Description
^^^^^^^^^^^
``validate`` is an extensible |pfo|_ which enables or disables subset of
``functor`` based functions by using :term:`SFINAE`.

.. seealso::

  :ref:`howto_custom_function`

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+------------------------+
  | Parameter | Requirement                  | Description            |
  +===========+==============================+========================+
  | Function  | None                         | Function tag           |
  +-----------+------------------------------+------------------------+
  | Category  | Type Category Set            | Current types category |
  +-----------+------------------------------+------------------------+
  | Info      | None                         | Custom attributes      |
  +-----------+------------------------------+------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/details/validate.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace functors
  {
    template<class Function,class Category,class Info=void> struct validate
    {
      template<class Sig> struct result;
    };
  }

Types
^^^^^

struct result
-------------

.. index::
    single: validate; result

**Synopsis:**

.. code-block:: cpp

    template<class Sig> struct result;

**Description:**

Template class implementing the |result_of|_. It returns a |mpl_int|_
that dictates if, for a given set of concrete arguments, the current Function is
callable or should be pruned by :term:`SFINAE`. By default, ``validate`` checks
that a call to the said function implementation through :ref:`functor_call` with
a given set of arguments is valid. This means that not providing an given implementation
of :ref:`functor_call` for a type category will automatically prevent calls of functions
on those types, thus limiting the amount of error noise in user code.

