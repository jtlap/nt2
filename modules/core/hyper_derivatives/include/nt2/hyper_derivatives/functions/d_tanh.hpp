//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPER_DERIVATIVES_FUNCTIONS_D_TANH_HPP_INCLUDED
#define NT2_HYPER_DERIVATIVES_FUNCTIONS_D_TANH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_tanh generic tag

     Represents the d_tanh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_tanh_ : ext::elementwise_<d_tanh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_tanh_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_tanh_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_tanh_, Site> dispatching_d_tanh_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_tanh_, Site>();
   }
   template<class... Args>
   struct impl_d_tanh_;
  }
  /*!
    @brief Derivative of tanh
    @see @funcref{tanh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_tanh_, d_tanh, 1)
}

#endif

