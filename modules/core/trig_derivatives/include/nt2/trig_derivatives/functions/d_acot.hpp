//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_ACOT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_ACOT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_acot generic tag

     Represents the d_acot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_acot_ : ext::elementwise_<d_acot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_acot_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_acot_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_acot_, Site> dispatching_d_acot_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_acot_, Site>();
   }
   template<class... Args>
   struct impl_d_acot_;
  }
  /*!
    derivative of inverse cotangent.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_acot(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, \pi[\f$ such that <tt>cot(r) == x</tt>.

    @see @funcref{d_acotd}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_acot_, d_acot, 1)
}

#endif

