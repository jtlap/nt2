//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_PROD_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_PROD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/constant/constants/one.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief prod generic tag

     Represents the prod function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct prod_ : ext::reduction_<prod_, tag::multiplies_, tag::One>
    {
      /// @brief Parent hierarchy
      typedef ext::reduction_<prod_, tag::multiplies_, tag::One> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_prod_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::prod_, Site> dispatching_prod_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::prod_, Site>();
   }
   template<class... Args>
   struct impl_prod_;
  }
  /*!
    Returns the product of the elements of the SIMD vector

    @par Semantic:

    For every parameter of type T0

    @code
    scalar<T0> r = prod(a0);
    @endcode

    is similar to:

    @code
    scalar<T0> r = One;
    for(result_type i = 0; i != cardinal_of<T0>; ++i)
      r *= a0[i];
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::prod_, prod, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::prod_, prod, 2)
} }
#endif

