//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_ASEC_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_ASEC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_asec generic tag

     Represents the d_asec function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_asec_ : ext::elementwise_<d_asec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_asec_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_asec_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_asec_, Site> dispatching_d_asec_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_asec_, Site>();
   }
   template<class... Args>
   struct impl_d_asec_;
  }
  /*!
    inverse secant.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_asec(a0);
    @endcode

    is similar to:

    @code
    T0 r =  acos(rec(a0));
    @endcode

    @see @funcref{d_asecd}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_asec_, d_asec, 1)
}

#endif


