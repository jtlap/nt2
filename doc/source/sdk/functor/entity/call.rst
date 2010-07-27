.. _functor_call:

call
====

.. index::
    single: call

Description
^^^^^^^^^^^
``call`` is an extensible |pfo|_ implementing the actual semantic of a
given ``functor`` class.

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

  #include <nt2/sdk/functor/details/call.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace functors
  {
    template<class Function,class Category,class Info=void> struct call
    {
      template<class Sig> struct result;

      template<class Args...> typename result<call(Args...)>::type operator()( Args const&... ) const;
    };
  }

Operators
^^^^^^^^^

operator(Args const& ...)
-------------------------

.. index::
    single: call; operator(Args const&...)

**Synopsis:**

.. code-block:: cpp

    template<class Args...> typename result<call(Args...)>::type operator()( Args... const& ) const;

**Description:** Polymorphic function call operator that, for a given `Function` tag
and a given `Category` of argument types, provides the proper implementation of
`Function`.

Types
^^^^^

struct result
-------------

.. index::
    single: call; result

**Synopsis:**

.. code-block:: cpp

    template<class Sig> struct result;

**Description:** Template class implementing the |result_of|_ and evaluates
the concrete return type of a call to any `call` function call operator overloads.
