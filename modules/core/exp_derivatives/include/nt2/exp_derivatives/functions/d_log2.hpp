//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D_LOG2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D_LOG2_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief d_log2 generic tag

     Represents the d_log2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_log2_ : ext::elementwise_<d_log2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_log2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_log2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_log2_, Site> dispatching_d_log2_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_log2_, Site>();
   }
   template<class... Args>
   struct impl_d_log2_;
  }
  /*!
    Compute the derivative of log2(x) at x
    @see @funcref{log2}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_log2_, d_log2, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::d_log2_, d_log2,(A0 const&)(A1&),2)

}


#endif

