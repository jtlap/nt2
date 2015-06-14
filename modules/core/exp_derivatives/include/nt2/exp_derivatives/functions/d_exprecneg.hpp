//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_D_EXPRECNEG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_D_EXPRECNEG_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag {
    /*!
      @brief d_exprecneg generic tag

      Represents the d_exprecneg function in generic contexts.

      @par Models:
         Hierarchy
    **/
    struct d_exprecneg_ : ext::elementwise_<d_exprecneg_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_exprecneg_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&& ... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_exprecneg_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::d_exprecneg_, Site>
    dispatching_d_exprecneg_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::d_exprecneg_, Site>();
    }
    template<class... Args>
    struct impl_d_exprecneg_;
  }
  /*!
    Compute the derivative of exprecneg at x
    @see @funcref{exprecneg}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_exprecneg_, d_exprecneg, 1)
}

#endif

