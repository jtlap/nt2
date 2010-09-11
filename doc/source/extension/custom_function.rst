.. _howto_custom_function:

Defining a new |nt2| function
=============================

Motivation
^^^^^^^^^^

The simplest entry point to extend |nt2| is to provide new user or internal
polymorphic functions. Use-cases are aplenty: forwarding some third-party
library calls, building a new domain-specific set of operations or creating
new internal helpers. This section will describe the process of creating such
a function using the various element from the :ref:`functors` components as
specified in its :ref:`functors_rationale` by trying to implement a ``fibonnaccci``
function for scalar arithmetic values.

Registering the function
^^^^^^^^^^^^^^^^^^^^^^^^

First step is to register the function in |nt2|. This is done by creating a
**functor tag** and generating the function body.

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>
  #include <nt2/sdk/functor/preprocessor/function.hpp>

  namespace nt2
  {
    namespace functors { struct fibonnacci_ {}; }

    NT2_FUNCTION_IMPLEMENTATION(functors::fibonnacci_,fibonnacci,1)
  }

Once done, the function ``fibonnacci`` is ready to use. Except currently, any call
to this function will result in a statis assertion telling you that there is no
implementation for ``fibonnacci`` available.

Implementing the function
^^^^^^^^^^^^^^^^^^^^^^^^^

The next step is then to give ``fibonnacci`` an actual implementation. This is
done by creating an specialization of :ref:`functor_call`. :ref:`functor_call`
is just a |pfo|_ that will contains the code needed to compute any given
function represented by its tag for a given category of types.

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>
  #include <nt2/sdk/functor/category.hpp>
  #include <nt2/sdk/functor/preprocessor/call.hpp>

  namespace nt2 { namespace functors
  {
    template<class Info>
    struct call<fibonnacci_,tag::scalar_(tag::arithmetic_),Info>
    {
      typedef double result_type;

      NT2_FUNCTOR_CALL(1)
      {
        double n0(0),n1(1),r(1);
        if(a0==0) return 0;
        if(a0==1) return 1;
        for(A0 i=0;i<a0-1;++i)
        {
          r = n0+n1;
          n0 = n1;
          n1 = r;
        }
        return r;
      }
    };
  } }

Here, we provide a simple, straightforward implementation of the Fibonnacci
serie (I will urge our numerician readers to not burn us right now, this is
just an example). As said earlier, ``call`` follow the |result_of|_. To help
users, we provide various macros to generate the boilerplate code for the
main `operator()` required.

Restricting function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^

At this point, one is able to call ``fibonnacci`` over arguments of any types,
including non-sensical thing like ``fibonnacci(4.734f)``. The nest step in defining
a |nt2| functon is to restrict its domain so that incorrect calls are caught early
and produce an error thanks to :term:`SFINAE`. To do so, we have to specialize
:ref:`functor_validate` for our functor and type set.

.. code-block:: cpp

  namespace nt2 { namespace functors
  {
    template<class Info>
    struct validate<fibonnacci_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This, class A0>
      struct result<This(A0)> : boost::is_integral<typename meta::strip<A0>::type>
      {};
    };
  } }

In our case, we specialize :ref:`functor_validate` so that ``fibonnacci`` only
accept integral types as input. To do so, we just reuse ``boost::is_integral``
and apply it to the input type. Note the use of :ref:`meta_strip` to be sure we
work on the naked type and some const qualified or reference type.

Internal Tag Dispatching
^^^^^^^^^^^^^^^^^^^^^^^^

In this implementation, we focus on the integral support of the function. One
may want to provide an implementation of ``fibonnacci`` for real numbers. This
implementation rationale could be that if the real argument is in fact an integer,
the call is forwarded to the integral version. If not, a runtime assertion is
triggered. |nt2| provides :ref:`functor_hierarchy` to help simplifying the dispatch
of function calls over type or set if types. This dispacthing reduce the amount
of code one need to replicate between variations thanks to :ref:`functor_call_macro`.
The ``call`` code is then modified accordingly.

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>
  #include <nt2/sdk/functor/category.hpp>
  #include <nt2/sdk/functor/preprocessor/call.hpp>

  namespace nt2 { namespace functors
  {
    template<class Info>
    struct call<fibonnacci_,tag::scalar_(tag::arithmetic_),Info>
    {
      typedef double result_type;

      NT2_FUNCTOR_CALL_DISPATCH ( 1
                                , A0
                                , (2, (int_,real_) )
                                )

      NT2_FUNCTOR_EVAL_IF(1, int_)
      {
        double n0(0),n1(1),r(1);
        if(a0==0) return 0;
        if(a0==1) return 1;
        for(A0 i=0;i<a0-1;++i)
        {
          r = n0+n1;
          n0 = n1;
          n1 = r;
        }
        return r;
      }

      NT2_FUNCTOR_EVAL_IF(1, real_)
      {
        NT2_ASSERT(is_integral(a0));
        return fibonnacci(static_cast<typename meta::as_integer<A0>::type>(a0));
      }
    };
  } }

The new elements here are the :ref:`functor_call_dispatch` and :ref:`functor_call_eval_if`
macros.

* :ref:`functor_call_dispatch`

This macro generates an `operator()` that actually dispatch its arguments to
some internal specialization based on a type quality. Here, we define a one
argument dispatching `operator()` that use `A0` to performs the dispatch. The
disptach map is then given as a Boost.Preprocessor array that contains types or
:ref:`functor_hierarchy` we want to dispatch over. In this case, we want to
handle integers or real types differently.

* :ref:`functor_call_eval_if`

This macros builds dispatching handler for a given dispatching target. Here we
define two such dispatching handler - one for `int_`, one for `real_` - and implement
them. Notice how the real type can just freely reuse the `fibonnacci` function directly.

Handling template parameters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In some case, we may want to pass additional template parameters to our
function to specify special strategies, policies or to force the return type.
In our case, we may want ``fibonnacci`` to return something else than a double.
To do so, we'll slighty modify the ``fibonnacci_`` tag so it can pass these
types down to the calling site and see how to open up :ref:`nt2_function_implementation`
to take care of it.

First we make ``fibonnacci_`` a template class.

.. code-block:: cpp

  namespace nt2 { namespace functors
  {
    template<class ReturnType> struct fibonnacci_ {};
  } }

Then we change the :ref:`functor_call` specialization to take care of this.

.. code-block:: cpp

  namespace nt2 { namespace functors
  {
    template<class ReturnType, class Info>
    struct call<fibonnacci_<ReturnType>,tag::scalar_(tag::arithmetic_),Info>
    {
      typedef ReturnType result_type;

      NT2_FUNCTOR_CALL_DISPATCH ( 1
                                , A0
                                , (2, (int_,real_) )
                                )

      NT2_FUNCTOR_EVAL_IF(1, int_)
      {
        ReturnType n0(0),n1(1),r(1);
        if(a0==0) return 0;
        if(a0==1) return 1;
        for(A0 i=0;i<a0-1;++i)
        {
          r = n0+n1;
          n0 = n1;
          n1 = r;
        }
        return r;
      }

      NT2_FUNCTOR_EVAL_IF(1, real_)
      {
        NT2_ASSERT(is_flint(a0));
        return fibonnacci<ReturnType>(static_cast<typename meta::as_integer<A0>::type>(a0));
      }
    };
  } }

The last part is to build the fibonnacci function itself. We'll make the choice
to have both a non-templated function which will return double and a template
one. By looking at the internals of :ref:`nt2_function_implementation`, we can
see that it basically gather various smaller macro calls.

.. code-block:: cpp

  #define NT2_FUNCTION_IMPLEMENTATION(TAG,NAME,N)                       \
  template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                      \
  typename nt2::meta::enable_call<TAG(BOOST_PP_ENUM_PARAMS(N,A))>::type \
  NAME ( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) )                   \
  {                                                                     \
    nt2::functors::functor<TAG> callee;                                 \
    return callee(BOOST_PP_ENUM_PARAMS(N,a));                           \
  }                                                                     \
  /**/

We'll just have to reuse this structure and add the support for ``ReturnType``.
The function declaration then become:

.. code-block:: cpp

  template<class A0> inline
  typename nt2::meta::enable_call<functors::fibonnacci_<double>(A0)>::type
  fibonnacci( A0 const& a0 )
  {
    nt2::functors::functor< functors::fibonnacci_<double> > callee;
    return callee(a0);
  }

  template<class ReturnType, class A0> inline
  typename nt2::meta::enable_call<functors::fibonnacci_<ReturnType>(A0)>::type
  fibonnacci( A0 const& a0 )
  {
    nt2::functors::functor< functors::fibonnacci_<ReturnType> > callee;
    return callee(a0);
  }
