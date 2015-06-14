//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D_REALSQRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D_REALSQRT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_realsqrt generic tag

     Represents the d_realsqrt function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_realsqrt_ : ext::elementwise_<d_realsqrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_realsqrt_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_realsqrt_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_realsqrt_, Site> dispatching_d_realsqrt_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_realsqrt_, Site>();
   }
   template<class... Args>
   struct impl_d_realsqrt_;
  }
  /*!
    Compute the derivative of realsqrt at x
    @see @funcref{realsqrt}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_realsqrt_, d_realsqrt, 1)
}

#endif
