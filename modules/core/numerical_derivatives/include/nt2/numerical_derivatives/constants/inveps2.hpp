//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_CONSTANTS_INVEPS2_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_CONSTANTS_INVEPS2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Inveps2 generic tag

     Represents the Inveps2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Inveps2, double, 1
                                , 0x56800000, 0x4670000000000007ll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Inveps2, Site>
   dispatching_Inveps2(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Inveps2, Site>();
   }
   template<class... Args>
   struct impl_Inveps2;
  }
  /*!
    inverse of machine precision to avoid dividing by eps

    @par Semantic:

    @code
    T r = Inveps2<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,104);
    else if T is float
      r =  pow(2,56);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Inveps2, Inveps2)
}

#include <boost/simd/constant/common.hpp>

#endif
