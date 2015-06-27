//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_CONSTANTS_DERIVINC_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_CONSTANTS_DERIVINC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Derivinc generic tag

     Represents the Derivinc constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Derivinc, double, 1
                                , 0x39800000, 0x3e5000000000000dll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Derivinc, Site>
   dispatching_Derivinc(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Derivinc, Site>();
   }
   template<class... Args>
   struct impl_Derivinc;
  }
  /*!
    Generate an increment for finite difference for derivative approximation

    @par Semantic:

    @code
    T r = Derivinc<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-26);
    else if T is float
      r =  pow(2,-12);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Derivinc, Derivinc)
}

#include <boost/simd/constant/common.hpp>

#endif
