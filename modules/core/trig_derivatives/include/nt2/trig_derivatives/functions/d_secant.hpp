//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_SECANT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_SECANT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_secant generic tag

     Represents the d_secant function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T> struct d_secant_ : ext::elementwise_< d_secant_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< d_secant_<T> > parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_HEADER( dispatching( ext::adl_helper(), *(d_secant_*)0, static_cast<Args&&>(args)... ) )
      {
        return dispatching( ext::adl_helper(), d_secant_(), static_cast<Args&&>(args)... );
      }
    };
  }
  /*!
    TODO Put description here

    @par Semantic:

    For every parameters of floating types respectively T0:

    @code
    T0 r = d_secant<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r = d_secant(x);
    @endcode

    but with the limitations and speed-up than can be implied
    by the @c Range choice (see cosine for details)

    @see @funcref{secd}, @funcref{secpi}, @funcref{sec},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::d_secant_<A0> , d_secant, (A1 const&), 2)
}

#endif


