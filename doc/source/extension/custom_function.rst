.. _howto_custom_function:

Defining a new |nt2| function
=============================

Motivation
^^^^^^^^^^

The simplest entry point to extend |nt2| is to provide new user or internal
polymorphic functions. Use-cases are aplenty: forwarding some third-party
library calls, building a new domain-specific set of operations or creating
new internal helpers are a few examples. This section describes the process
of creating such a function using the various element from the :ref:`functors`
components as specified in its :ref:`functors_rationale` by implementing
a ``fibonacci`` function for scalar arithmetic values.

Registering the function
^^^^^^^^^^^^^^^^^^^^^^^^

The first step is to register the function in |nt2|. This is done by creating a
**functor tag** and generating the function body.

.. code-block:: cpp

  #include <nt2/sdk/functor/functor.hpp>
  #include <nt2/sdk/functor/preprocessor/function.hpp>

  namespace nt2
  {
    namespace tag { struct fibonacci_ {}; }

    NT2_FUNCTION_IMPLEMENTATION(tag::fibonacci_,fibonacci,3)
  }

Once done, the function ``fibonacci`` is ready to use. Without further work,
though, any call to this function will result in a static assertion telling
you that there is no implementation for ``fibonacci`` available.

Implementing the function
^^^^^^^^^^^^^^^^^^^^^^^^^

The next step is to give ``fibonacci`` an actual implementation. This is
done by creating an specialization of :ref:`functor_call`. :ref:`functor_call`
is just a |pfo|_ that will contains the code needed to compute any given
function represented by its tag for a given category of types.

.. code-block:: cpp

  NT2_REGISTER_DISPATCH(tag::fibonacci_, tag::cpu_,
                     (A0)(A1)(A2),
                     (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A1>)
                    )
  namespace nt2 { namespace ext
  {
    template<class Dummy>
    struct call<tag::fibonacci_(tag::arithmetic_,
                                tag::arithmetic_,
                                tag::arithmetic_),tag::cpu_, Dummy>
    : Callable
    {
      typedef double result_type;

      NT2_FUNCTOR_CALL(3)
      {
        double n0(a1),n1(a2),r;
        if(a0==0) return n0;
        if(a0==1) return n1;
        for(A0 i=1;i<a0;++i)
        {
          r = n0+n1;
          n0 = n1;
          n1 = r;
        }
        return r;
      }
    };
  } }

Here, we provide a simple, straightforward implementation of the
Fibonacci sequence (I will urge our mathematician readers to not burn
us right now, this is just an example, Binet formula can be
sometimes better). As said earlier, ``call`` follows the |result_of|_. To help
users, we provide various macros to generate the boilerplate code for
the main `operator()` required.

Restricting function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^

At this point, one is able to call ``fibonacci`` over triples of
arguments of any types, including non-nonsensical things like
``fibonacci(4.734f,0.0f,1.0f)``. The next step in defining a |nt2|
function is to restrict its domain so that incorrect calls are caught
early and produce an error thanks to :term:`SFINAE`. To do so, we only
have to specify the dispatch registration, the call and the result
protocol.

.. code-block:: cpp

  NT2_REGISTER_DISPATCH(tag::fibonacci_, tag::cpu_,
                     (A0)(A1)(A2),
                     (integer_<A0>)(arithmetic_<A1>)(arithmetic_<A1>)
                    )
  namespace nt2 { namespace ext
  {
    template<class Dummy>
    struct call<tag::fibonacci_(tag::integer_,
                                tag::arithmetic_,
                                tag::arithmetic_),tag::cpu_, Dummy>
    : Callable
    {
      template<class Sig> struct result;
      template<class This,class A0,class A1,class A2>
      struct result<This(A0)> :
         boost::result_of<meta::arithmetic(A1,A2)>{};
 
      NT2_FUNCTOR_CALL(3)
      {
        typedef typename NT2_RETURN_TYPE(3)::type rtype;
        rtype n0(a1),n1(a2),r;
      	if(a0==0) return n0;
        if(a0==1) return n1;
        for(A0 i=1;i<a0;++i)
        {
          r = n0+n1;
          n0 = n1;
          n1 = r;
        }
        return r;
      }
    };
  } }

In our case:

  * we specialize the dispatch in order that the first parameter has to be 
    integral (the position in the fibonacci sequence), the other initial 
    parameters being of any arithmetical types.
  
  * we also indicate to the call the tags of the parameters

  * finally we decide that the proper type to return is the arithmetic 
    promotion of the two initial values

Note that in the case where the returned type is the same as the input
one the |result_of|_ will need to use :ref:`meta_strip` to be sure we
work on the naked type and not some const qualified or reference type.

Tag Dispatching
^^^^^^^^^^^^^^^

In the previous case, we had a general implementation of the function. If one
wants to provide a different implementation of ``fibonacci`` for real numbers. This
implementation could be simply written by creating a new dispatch and a new call using
``real_`` for tagging ``A1`` and ``A2``. 

|nt2| provides :ref:`functor_hierarchy` to help simplifying the
dispatch of function calls over type or set if types. This dispatching
reduce the amount of code one need to replicate between variations
thanks to :ref:`functor_call_macro`.  The ``call`` code is then
modified accordingly.

.. code-block:: cpp

  NT2_REGISTER_DISPATCH(tag::fibonacci_, tag::cpu_,
                     (A0)(A1)(A2),
                     (integer_<A0>)(real_<A1>)(real_<A1>)
                    )
  namespace nt2 { namespace ext
  {
    template<class Dummy>
    struct call<tag::fibonacci_(tag::integer_,
                                tag::real_,
                                tag::real_),tag::cpu_, Dummy>
    : Callable
    {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> :
         boost::result_of<meta::arithmetic(A1,A2)>{};
 
      NT2_FUNCTOR_CALL(3)
      {
        typedef typename NT2_RETURN_TYPE(3)::type rtype;
        rtype n0(a1),n1(a2),r;
        r = special_algo_for_reals(a0,n0,n1);
        return r;
      }
    };
  } }

This new implementation is independant of the preceding one and can be put
in the same header file or in another one, as needed.