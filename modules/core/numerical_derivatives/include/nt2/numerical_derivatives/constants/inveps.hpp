//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_CONSTANTS_INVEPS_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_CONSTANTS_INVEPS_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Inveps generic tag

     Represents the Inveps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Inveps, double, 1
                                , 0x4b000000, 0x4330000000000000ll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Inveps, Site>
   dispatching_Inveps(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Inveps, Site>();
   }
   template<class... Args>
   struct impl_Inveps;
  }
  /*!
    inverse of machine precision to avoid dividing by eps

    @par Semantic:

    @code
    T r = Inveps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,52);
    else if T is float
      r =  pow(2,23);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Inveps, Inveps)
}

#include <boost/simd/constant/common.hpp>

#endif
