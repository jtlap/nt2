//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_ACOSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_ACOSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_acosd generic tag

     Represents the d_acosd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_acosd_ : ext::elementwise_<d_acosd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_acosd_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_acosd_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_acosd_, Site> dispatching_d_acosd_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_acosd_, Site>();
   }
   template<class... Args>
   struct impl_d_acosd_;
  }
  /*!
    derivatives of inverse cosine in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_acosd(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 180[\f$ such that <tt>cosd(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see @funcref{acos}, @funcref{acospi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_acosd_, d_acosd, 1)
}

#endif
