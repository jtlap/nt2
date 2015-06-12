//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_TAN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_TAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_tan generic tag

     Represents the d_tan function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_tan_ : ext::elementwise_<d_tan_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_tan_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_tan_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_tan_, Site> dispatching_d_tan_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_tan_, Site>();
   }
   template<class... Args>
   struct impl_d_tan_;
  }
  /*!
    d_tangent of the input in radians.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_tan(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(x)/cos(x);
    @endcode

    @see @funcref{d_tangent}, @funcref{d_tan}, @funcref{d_tand}, @funcref{d_tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_tan_, d_tan, 1)
}

#endif

