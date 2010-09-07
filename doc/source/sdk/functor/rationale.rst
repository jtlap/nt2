.. _functors_rationale:

Design Notes
============

Objectives
^^^^^^^^^^
|nt2| provides hundred of functions ranging from simple arithmetic operations to
high level mathematical transformation. All those functions are bound to be called
on a large spectrum of types. It is then critical to be able to both control which
types a function can handle, emit graceful error messages in case of type mismatch
and to allow developers to extends those functions by adding types support or
creating entirely new functions. This section describes the technical choices made
to handle those constraints in |nt2|.

.. note::
  An in-depth tutorial on how to define a custom function is available and cover
  some implementation details that we omit here for clarity.

  See: :ref:`howto_custom_function`

Handling function overload
^^^^^^^^^^^^^^^^^^^^^^^^^^
Considering the amount of functions and potential types they may be applied,
manually enumerating function overload combinations ends up as a quadratic process.
Specifying partial overload using some template arguments helps reducing this amount
but fails to provide a clean, non-ambiguous discrimination. Our idea is to provide
only one function with a full-blown template prototype and to use :term:`Tag Dispatching`
internally to forward arguments to the proper implementation of said function.

Function tags
-------------
The first task is to be able to discriminate functions by an unique type identifier
throughout the various possible overloads and to be able to use this identifier as
a rapid way to call said implementation. The idea is to define a simple structure
which name can be used in a generalized functor class (see :ref:`functor`). For
example, the square root function will be registered via:

.. code-block:: cpp

  struct sqrt_ {};

The associated generic function, called ``sqrt``, will simply take one argument
and forward it to the proper functor implementation.

.. code-block:: cpp

  template<class T>  typename boost::result_of<functor<sqrt_>(T)>::type sqrt( T const& v )
  {
    functor<sqrt_> callee;  // instantiate the polymorphic sqrt functor
    return callee(v);        // call said functor
  }

:ref:`functor`, being a |pfo|_ provides, via the |result_of|_, the actual result
type of the function with respect to its arguments type. As the implementation,
and therefore the semantic, of the function is actually bound to the tag and not
the function itself, one can create various functions with different  names - for
following coding style or domain-specific nomenclature - that uses the same function
implementation.

.. note::
  We use functions instead of const instances of the functor class itself due
  to scalability concern. Templates functions are only compiled if actually called, thus limiting
  the binary size and the compilation time. Benchmarks show that, for the same amount of function
  calls, the instance based version of the same code compiles in a linear time
  with respect to number of functors, while the function version compiles in constant
  time.

Specializable call point
------------------------
Once a function has been declared, one has to define its implementation. This is done by specializing the
:ref:`functor_call` class which synopsis is given below.

.. code-block:: cpp

    namespace functors
    {
      template<class Function,class Category,class Info=void> struct call
      {
        template<class Sig> struct result;

        template<class Args...> inline
        typename result<call(Args...)>::type operator()( Args... const& ) const;
      };
    }

:ref:`functor_call` is a simple |pfo|_ itself which goal is to externalize the
various specializations of any given function with respect to its arguments type
category and, for a given category, for its different argument types themselves.

As an example, here is a possible implementation of ``sqrt`` for arithmetic
scalar types.

.. code-block:: cpp

    template<class Info> struct call<sqrt_, tag::scalar(tag::arithmetic), Info>
    {
      template<class Sig> struct result;
      template<class This,class A>  struct result<This(A)>
      {
        typedef typename meta::as_real<A>::type type
      };

      NT2_FUNCTOR_CALL(1)
      {
        typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
        return std::sqrt(type(a0));
      }
    };

.. seealso::
  :ref:`functor_call`,
  :ref:`functor_call_macro`,
  :ref:`functor_hierarchy` and
  :ref:`meta_belong_to`


Tag Dispatching Strategy
------------------------
|nt2| functions are inherently polymorphic as they can be (except with specific
validation clause) called with any types. To be able to discriminate parameters
types and choose the proper implementation, we rely on a type categorization
system in which types are sorted based on their **rank**. The **rank** is a
32 bits numerical values that uniquely identify a type among all others.

Determining which :ref:`functor_call` specialization to call is done by ordering
all argument types their **rank**. This is done internally via the :ref:`meta_dominant`
meta-function which computes such a type from a type list. The so-called **dominant**
argument type is then used to compute the category using the :ref:`meta_category_of` meta-function.
This category will then be used by :ref:`functor_call` to select the proper implementation.

.. seealso::
  :ref:`meta_category` and
  :ref:`meta_dominant`

Restricting function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^
Restricting function domain naturally relies on the :term:`SFINAE` principle which allow template function to be pulled out of potential
overload set if their return type is ill-formed. To manage the potentially large number of types category to handle, this compile-time
check is done by the :ref:`functor_validate` class which can be overloaded for any given tag and any given type category.

Here is the synopsis of :ref:`functor_validate`:

.. code-block:: cpp

  namespace functors
  {
    template<class Function,class Category,class Dummy=void> struct validate
    {
      template<class Sig> struct result;
    };
  }

Let's say we want to prevent the function ``sqrt`` , associated to the tag ``sqrt_``, to be called on non-real scalar types.
:ref:`functor_validate` has to be overloaded as such:

.. code-block:: cpp

  template<class Dummy,class T> struct validate< sqrt_, scalar<T>, Dummy >
  {
      template<class Sig> struct result;
      template<class This,class A0> struct result : boost::is_floating_points<A0> {};

      template<class A0> inline typename result<validate(A0)>::type
      operator()(A0 const&) const
      {
        return typename result<validate(A0)>::type();
      }
  };

Advantages of this approach is that the fine tuning of which types or family of
types are allowed to be used with any specific function is completely externalized
with respect to the actual :ref:`functor` class. Note that the flexibility of the
:ref:`meta_category` mechanism helps the specification process by allowing wide
or narrow type category selection.

In our example, the ``sqrt`` function then takes this final form:

.. code-block:: cpp

  template<class T>
  // SFINAE through boost::enable_if
  typename boost::lazy_enable_if_c< boost::result_of<typename functor<sqrt_>::validate(T)>::type::value
                                  , boost::result_of<functor<sqrt_>(T)>
                                  >::type
  sqrt( T const& v )
  {
    nt2::functors::functor<sqrt_> callee;  // instantiate the polymorphic sqrt functor
    return callee(v);                       // call said functor
  }

By default, :ref:`functor_validate` is defined so it checks if, for a given set of argument types, calling
the corresponding :ref:`functor_call` specialization is well-defined. This means that the signature
of the function call operator of the :ref:`functor_call` function can also helps refining validation process.
A striking example is how the :term:`SIMD` function overload are defined. Most of them don't provide
any special validation even if they can't be called with two different vector types. The following
code sample shows how it is achieved.

.. code-block:: cpp

  template<class T> struct call< plus_, simd<T> >
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> { typedef A type; };

    NT2_FUNCTION_CALL(2) { /* specific SIMD code */ }
  };

In this case, any attempt to check if, for example, ``plus_(simd::vector<int>, simd::vector<float>)``
will fail as no such signature is matched by any of the ``result`` signature of ``call<plus_,simd<T> >``.

.. seealso::
  :ref:`functor` and
  :ref:`functor_macro`
