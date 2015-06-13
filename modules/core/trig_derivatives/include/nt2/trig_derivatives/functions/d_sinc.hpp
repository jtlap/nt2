//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_D_SINC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_D_SINC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_sinc generic tag

     Represents the d_sinc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_sinc_ : ext::elementwise_<d_sinc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_sinc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_sinc_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_sinc_, Site> dispatching_d_sinc_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_sinc_, Site>();
   }
   template<class... Args>
   struct impl_d_sinc_;
  }
  /*!
    Compute the cardinal sine.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_sinc(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(x)/x;
    @endcode

    @see @funcref{d_sincpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_sinc_, d_sinc, 1)
}

#endif


