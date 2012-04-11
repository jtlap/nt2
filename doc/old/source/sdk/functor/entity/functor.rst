.. _functor:

functor
=======

.. index::
    single: functor

Description
^^^^^^^^^^^

``functor`` is a generic, |pfo|_ that acts as the central tag-dispatch hub for
all |nt2| function or method calls. Semantic of a ``functor`` is usually given
by the ``Function`` tag that act as an unique identifier to the function to perform.

.. seealso::

  :ref:`howto_custom_function`

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | Function  | None                         | Function tag       |
  +-----------+------------------------------+--------------------+
  | Info      | None                         | Custom attributes  |
  +-----------+------------------------------+--------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace functors
  {
    template<class Function, class Info = void> struct functor
    {
      template<class Sig> struct result;

      template<class Args...>  typename result<functor(Args...)>::type operator()(Args const& ...) const;
    };
  }

Operators
^^^^^^^^^

operator(Args const&... )
-------------------------

.. index::
    single: functor; operator(Args const&... )

**Synopsis:**

.. code-block:: cpp

    template<class Args...> typename result<functor(Args...)>::type operator()(Args... const&) const;

**Description:** Polymorph, variadic function call operator. This operator
performs a tag-dispatched call to a given implementation of the ``Function``
to be executed by matching its arguments list to a given category of types.

Types
^^^^^

struct result
-------------

.. index::
    single: functor; result

**Synopsis:**

.. code-block:: cpp

    template<class Sig> struct result;

**Description:** Template class implementing the |result_of|_ and evaluates
the concrete return type of a call to any `functor` function call operator
overloads.
