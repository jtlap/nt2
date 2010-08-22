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

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>
  #include <nt2/sdk/functor/preprocessor/function.hpp>

  namespace nt2
  {
    namespace functors { struct fibonnacci_ {}; }

    NT2_FUNCTION_IMPLEMENTATION(functors::fibonnacci_,fibonnacci,1)
  }


Implementing the function
^^^^^^^^^^^^^^^^^^^^^^^^^

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

Restricting function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace functors
  {
    template<class Info>
    struct validate<fibonnacci_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This, class A0>
      struct result<This(A0)> : boost::is_integral<A0>
      {};
    };
  } }


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

Then we change the :ref:`call` specialization to take care of this.

.. code-block:: cpp

  namespace nt2 { namespace functors
  {
    template<class ReturnType, class Info>
    struct call<fibonnacci_<ReturnType>,tag::scalar_(tag::arithmetic_),Info>
    {
      typedef ReturnType result_type;

      NT2_FUNCTOR_CALL(1)
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

