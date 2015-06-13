//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_COT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_COT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_cot generic tag

     Represents the d_cot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_cot_ : ext::elementwise_<d_cot_>
    {
      /// @brief Parent hierarchy
       typedef ext::elementwise_<d_cot_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_cot_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_cot_, Site> dispatching_d_cot_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_cot_, Site>();
   }
   template<class... Args>
   struct impl_d_cot_;
  }
  /*!
    d_cotangent of the input in radian.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_cot(x);
    @endcode

    is similar to:

    @code
    T0 r = cos(x)/sin(x);
    @endcode

    @see @funcref{d_cotangent}, @funcref{fast_d_cot}, @funcref{d_cotd}, @funcref{d_cotpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_cot_, d_cot, 1)
}

#endif

