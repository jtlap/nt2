//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ASECD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_ASECD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_asecd generic tag

     Represents the d_asecd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_asecd_ : ext::elementwise_<d_asecd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_asecd_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_asecd_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_asecd_, Site> dispatching_d_asecd_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_asecd_, Site>();
   }
   template<class... Args>
   struct impl_d_asecd_;
  }
  /*!
     inverse secant in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_asecd(a0);
    @endcode

    is similar to:

    @code
    T0 r =  acosd(rec(a0));;
    @endcode

    @see @funcref{asec}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_asecd_, d_asecd, 1)
}

#endif


