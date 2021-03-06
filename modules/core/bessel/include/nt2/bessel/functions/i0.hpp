//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_I0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_I0_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief i0 generic tag

     Represents the i0 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct i0_ : ext::elementwise_<i0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<i0_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_i0_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::i0_, Site> dispatching_i0_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::i0_, Site>();
   }
   template<class... Args>
   struct impl_i0_;
  }
  /*!
    Modified Bessel function of the first kind of order 0.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = i0(a0);
    @endcode

    Computes \f$\displaystyle \sum_0^\infty \frac{(x^2/4)^k}{(k!)^2}\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::i0_, i0, 1)
}

#endif

