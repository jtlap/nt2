//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_BETAINCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_BETAINCINV_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag {
    /*!
      @brief betaincinv generic tag

      Represents the betaincinv function in generic contexts.

      @par Models:
         Hierarchy
    **/
    struct betaincinv_ : ext::elementwise_<betaincinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<betaincinv_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_betaincinv_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::betaincinv_, Site>
    dispatching_betaincinv_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::betaincinv_, Site>();
    }
    template<class... Args>
    struct impl_betaincinv_;
  }
  /*!
    Computes betaincinv(p, a, b) is the inverse of the betainc function :
    it returns x where

        \f$ p = B(x, a_0,a_1)=\int_0^x t^{a_0-1}(1-t)^{a_1-1}\mbox{d}t\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 x = betaincinv(p, a, b );
    @endcode

    @see @funcref{betainc}
    @param p between 0 and 1
    @param a
    @param b

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::betaincinv_, betaincinv, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::betaincinv_, betaincinv, 4)
}

#endif
