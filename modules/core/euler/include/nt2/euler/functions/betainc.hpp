//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_BETAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_BETAINC_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief betainc generic tag

     Represents the betainc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct betainc_ : ext::elementwise_<betainc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<betainc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_betainc_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::betainc_, Site> dispatching_betainc_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::betainc_, Site>();
   }
   template<class... Args>
   struct impl_betainc_;
  }
  /*!
    Computes the icomplete beta function :
        \f$ B(x,a_0,a_1)=\int_0^x t^{a_0-1}(1-t)^{a_1-1}\mbox{d}t\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = betainc(x,a0,a1);
    @endcode

    @see @funcref{gamma}
    @param x
    @param a0
    @param a1

    @return a value of the same type as the parameters
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::betainc_, betainc, 3)
}

#endif
