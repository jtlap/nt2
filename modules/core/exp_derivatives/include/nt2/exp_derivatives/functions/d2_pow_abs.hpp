//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D2_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D2_POW_ABS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d2_pow_abs generic tag

     Represents the d2_pow_abs function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d2_pow_abs_ : ext::elementwise_<d2_pow_abs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d2_pow_abs_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d2_pow_abs_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d2_pow_abs_, Site> dispatching_d2_pow_abs_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d2_pow_abs_, Site>();
   }
   template<class... Args>
   struct impl_d2_pow_abs_;
  }
  /*!
    @brief  Compute the derivative of y -> pow_abs(x, y)
    @see @funcref{pow_abs_add}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d2_pow_abs_, d2_pow_abs, 2)
}

#endif

