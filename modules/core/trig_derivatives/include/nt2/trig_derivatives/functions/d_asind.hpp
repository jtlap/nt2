//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_D_ASIND_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_D_ASIND_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief d_asind generic tag

     Represents the d_asind function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct d_asind_ : ext::elementwise_<d_asind_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<d_asind_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_d_asind_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::d_asind_, Site> dispatching_d_asind_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::d_asind_, Site>();
   }
   template<class... Args>
   struct impl_d_asind_;
  }
  /*!
    inverse sine in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = d_asind(a0);
    @endcode

    Returns the arc @c r in the interval
    \f$[-90, 90[\f$ such that <tt>sin(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::d_asind_, d_asind, 1)
}

#endif


