//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D_CBRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D_CBRT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_cbrt generic tag

     Represents the d_cbrt function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_cbrt_ : ext::elementwise_<d_cbrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_cbrt_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_cbrt_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_cbrt_, Site> dispatching_d_cbrt_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_cbrt_, Site>();
   }
   template<class... Args>
   struct impl_d_cbrt_;
  }
  /*!
    Compute the derivative of cbrt at x
    @see @funcref{cbrt}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_cbrt_, d_cbrt, 1)
}

#endif

