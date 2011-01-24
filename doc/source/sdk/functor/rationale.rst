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

Global Design Overview
^^^^^^^^^^^^^^^^^^^^^^
Considering the amount of functions and potential types they may be applied,
manually enumerating function overload combinations ends up as a quadratic process.
Specifying partial overload using some template arguments helps reducing this amount
but fails to provide a clean, non-ambiguous discrimination. Our idea is to provide
only one function with a full-blown template prototype and to use :term:`Tag Dispatching`
internally to forward arguments to the proper implementation of said function.

The main idea was to see if how much defining function overload with complex
dispatching is similar to the **expression problem** [#]_ which refers to a
fundamental dilemma of programming: To which degree can an application be structured
in such a way that both the data model and the set of operations over it can be
extended without the need to modify existing code, without the need for code
repetition and without runtime type errors. From this analysis, we propose a system
for defining function with a rich dispatching and specialization system relying on
meta-programming for categorizing, selecting and calling a given function
implementation for any arbitrary aggregate of input parameters. This lead to define
a function call process made of five steps: :ref:`functors_rationale_identify`,
:ref:`functors_rationale_categorize`, :ref:`functors_rationale_validate` ,
:ref:`functors_rationale_dispatch` and :ref:`functors_rationale_call`.

.. _functors_rationale_identify:

Identifying functions
^^^^^^^^^^^^^^^^^^^^^
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

  template<class A0> inline
  typename boost::result_of<functor<sqrt_>(A0 const&)>::type sqrt( A0 const& a0 )
  {
    functor<sqrt_> callee;  // instantiate the polymorphic sqrt functor
    return callee(a0);      // call said functor
  }

:ref:`functor`, being a |pfo|_ provides, via the |result_of|_, the actual result
type of the function with respect to its arguments type. As the implementation,
and therefore the semantic, of the function is actually bound to the tag and not
the function itself, one can create various functions with different  names - for
following coding style or domain-specific nomenclature - that uses the same function
implementation.

.. note::
  We use functions instead of constant instances of the functor class itself due
  to scalability concern. Templates functions are only compiled if actually called,
  thus limiting the binary size and the compilation time. Benchmarks show that,
  for the same amount of function calls, the instance based version of the same
  code compiles in a linear time with respect to number of functors, while the
  function version compiles in constant time.

.. _functors_rationale_categorize:

Categorizing the function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
|nt2| functions are inherently polymorphic as they can be (except with specific
validation clause) called with any types. To be able to discriminate parameters
types and choose the proper implementation, we rely on a type categorization
system which is able to discriminate scalar types SIMD types, container and container
expressions types for example. Every type handled by |nt2| has an associated so-called
``category`` tag which identify it by specifying which kind of type it belongs to.

Categories in |nt2| are partially ordered and can be easily defined for new type
famillies or extended by adding new variations of a given category. The :ref:`functor_categorize`
meta-function is able to take a list of parameters type and find the best category
fitting this types list. Change in this behavior can be done at a function tag level
by specializing the :ref:`functor_categorize` meta-function.

Here is the synopsis of :ref:`functor_validate`:

.. code-block:: cpp

  namespace meta
  {
    template<class Tag, class Site, class... Args> struct  categorize;
  }

By default, this is done by using :ref:`meta_dominant` meta-function which computes.
The so-called **dominant** argument type is then used to compute the category
using the :ref:`meta_category_of` meta-function. This category will then be used
by :ref:`functor_call` to select the proper implementation. Example of :ref:`functor_categorize`
overload includes function requiring to purposely ignore the category of some
non-numerical or unregistered types in its call like :ref:`load` which don't need
to categorize its iterator argument nor its memory offset but use its target type as a category enabler.

As an example, the category of ``double`` is ``nt2::functors::scalar_<nt2::tag::arithmetic_,1>``
and its associated tag is ``nt2::tag::scalar_(nt2::tag::arithmetic_)``. In a similar way,
the category of ``std::complex<T>`` is ``nt2::functors::scalar_<nt2::tag::complex_,10>``
and its associated tag is ``nt2::tag::scalar_(nt2::tag::complex_)``. Both types
are scalar types but have different sub-category (``arithmetic_`` versus ``complex_``).
The numeric values used to define the ``category`` type itself is used to order
them. So a function call applied on a ``double`` and a ``std::complex<double>``
will, by default, categorize its parameters as being member of the ``nt2::functors::scalar_<nt2::tag::complex_,10>``
category and use the ``nt2::tag::scalar_(nt2::tag::complex_)`` to select its
proper implementation. When a type without category is found in any function call,
its category is set to :ref:`tag_unknown` which category value is higher than all
others. Call to any :ref:`tag_unknown` specialization will raise :ref:`compile_time_assert`.

.. _functors_rationale_validate:

Restricting the function domain
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Restricting function domain naturally relies on the :term:`SFINAE` principle which
allow template function to be pulled out of potential overload set if their return
type is ill-formed. To manage the potentially large number of types category to
handle, this compile-time check is done by the :ref:`functor_validate` class which
can be overloaded for any given tag and any given type category.

Here is the synopsis of :ref:`functor_validate`:

.. code-block:: cpp

  namespace functors
  {
    template<class Function,class Category,class Site> struct validate
    {
      template<class Sig> struct result;
    };
  }

Let's say we want to prevent the function ``sqrt`` , associated to the tag ``sqrt_``,
to be called on non-real scalar types. :ref:`functor_validate` has to be overloaded as such:

.. code-block:: cpp

  template<class Dummy,class Category> struct validate< sqrt_, tag::scalar(Category), Dummy >
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result : boost::is_floating_points<typename meta::strip<A0>::type> {};
  };

Advantages of this approach is that the fine tuning of which types or family of
types are allowed to be used with any specific function is completely externalized
with respect to the actual :ref:`functor` class. Note that the flexibility of the
:ref:`meta_category` mechanism helps the specification process by allowing wide
or narrow type category selection.

In our example, the ``sqrt`` function then takes this final form, introducing the
:ref:`enable_call` helper which uses :ref:`functor_validate` to trigger :term:`SFINAE`
on any function:

.. code-block:: cpp

  template<class A0> typename enable_call<sqrt_(A0 const&)>::type sqrt( A0 const& a0 )
  {
    nt2::functors::functor<sqrt_> callee;  // instantiate the polymorphic sqrt functor
    return callee(a0);                     // call said functor
  }

By default, :ref:`functor_validate` is defined so it checks if, for a given set
of argument types, calling the corresponding :ref:`functor_call` specialization
is well-defined. This means that the signature of the function call operator of
the :ref:`functor_call` function can also helps refining validation process.

.. _functors_rationale_dispatch:

Dispatching the call
^^^^^^^^^^^^^^^^^^^^
At this point, we know that the current function is valid, we know on which category
of types it applies on. We're ready to select which implementation to use. Traditionnaly,
we may need to specialize a function implementation for each and every type supported
by said function. However, experience shows that some function implementation can
be factorized into generic code for non trivial types familly, leading to a very
few concrete type specialization. For example, we may have a specialization of
``sqrt`` for all integral types, one for ``double`` and one for ``float``.
|nt2| provides a partially ordered set of :ref:`functor_hierarchy` to handle such
use cases. Type hierarchies define a weak ordered relation between sets of atomic
types so that discriminting a types over some of its properties (size in bytes,
integral or real quality, etc ...).

In the same way that finding a types set category is non-trivial, computing the
dispatching target of such a type set is done by an overloadable lambda meta-function
called :ref:`functor_dispatch`.

Here is the synopsis of :ref:`functor_dispatch`:

.. code-block:: cpp

  namespace functors
  {
    template<class Tag,class Category,class Site> struct dispatch;
  }

Based on a function tag and a type category, :ref:`functor_dispatch` provides
a lambda meta-function which select which type in the parameters type list to
use to compute type hierarchy. By default, :ref:`functor_dispatch` is equivalent
to ``boost::mpl::_1`` but it is usually overloaded to select either another
type in a parameter types list or to apply any given transformation on said type
before hierarichizing it.

.. _functors_rationale_call:

Perfoming the actual function call
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Once a function has been declared, one has to define its implementation. This is
done by specializing the :ref:`functor_call` class which synopsis is given below.

.. code-block:: cpp

    namespace functors
    {
      template<class Function,class Category,class Hierarchy,class Site> struct call
      {
        template<class Sig> struct result;

        template<class Args...> inline
        typename result<call(Args...)>::type operator()( Args... const& ) const;
      };
    }

:ref:`functor_call` is a simple |pfo|_ itself which goal is to externalize the
various specializations of any given function with respect to its arguments type
category, hierarchy and execution site.

As an example, here is a possible implementation of ``sqrt`` for any arithmetic scalar type.

.. code-block:: cpp

    template<class Site> struct call<sqrt_, tag::scalar(tag::arithmetic), fundamental_, Site>
    {
      template<class Sig> struct result;
      template<class This,class A>
      struct result<This(A)> : meta::as_real<typename meta::strip<A>::type> {};

      NT2_FUNCTOR_CALL(1)
      {
        typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
        return std::sqrt(type(a0));
      }
    };

The :ref:`functor` system behaves by default so everything is intuitively valdiated
and dispatched to the proper :ref:`functor_call` specialization. Contributor work
is mainly to provide :ref:`functor_call` specialization of a given function for
a specific type set or architecture. As an example, one may want to use ``::sqrtf``
on ``float`` instead of ``std::sqrt``. This is done trivially by definign such a
:ref:`functor_call` overload.

.. code-block:: cpp

    template<class Site> struct call<sqrt_, tag::scalar(tag::arithmetic), float, Site>
    {
      template<class Sig> struct result;
      template<class This,class A> struct result<This(A)> : meta::strip<A> {};

      NT2_FUNCTOR_CALL(1)
      {
        return ::sqrtf(a0);
      }
    };

Now, calling ``sqrt`` on float will found out that dispatching on ``float`` is
preferred to dispatchign on the broader ``fundamental_`` hierarchy and thus
select the proper specialization. Any number of such specializations, beign narrow
or broad, can be added through this system.

------------

.. [#] Mads Torgersen, `The Expression Problem Revisited <http://www.daimi.au.dk/~madst/ecoop04/main.pdf>`_

