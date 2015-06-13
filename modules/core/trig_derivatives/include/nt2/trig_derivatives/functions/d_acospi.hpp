//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ACOSPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ACOSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag
  {
   /*!
     @brief d_acospi generic tag

     Represents the d_acospi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_acospi_ : ext::elementwise_<d_acospi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_acospi_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_acospi_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_acospi_, Site> dispatching_d_acospi_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_acospi_, Site>();
   }
   template<class... Args>
   struct impl_d_acospi_;
  }
  /*!
    derivative of inverse cosine in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_acospi(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 1[\f$ such that <tt>cospi(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see @funcref{acosd}, @funcref{acos}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_acospi_, d_acospi, 1)
}

#endif
