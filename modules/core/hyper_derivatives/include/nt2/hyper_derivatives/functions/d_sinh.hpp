//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPER_DERIVATIVES_FUNCTIONS_D_SINH_HPP_INCLUDED
#define NT2_HYPER_DERIVATIVES_FUNCTIONS_D_SINH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_sinh generic tag

     Represents the d_sinh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_sinh_ : ext::elementwise_<d_sinh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_sinh_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_sinh_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_sinh_, Site> dispatching_d_sinh_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_sinh_, Site>();
   }
   template<class... Args>
   struct impl_d_sinh_;
  }
  /*!
    @brief Derivative of sinh
    @see @funcref{sinh}

  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_sinh_, d_sinh, 1)
}

#endif

