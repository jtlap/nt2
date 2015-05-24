//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_CONSTANTS_DERIVINCC_HPP_INCLUDED
#define NT2_DERIVATION_CONSTANTS_DERIVINCC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Derivincc generic tag

     Represents the Derivincc constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Derivincc, double, 1
                                , 0x39000000, 0x3dc0000000000000ll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Derivincc, Site>
   dispatching_Derivincc(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Derivincc, Site>();
   }
   template<class... Args>
   struct impl_Derivincc;
  }
  /*!
    Generate an increment for centered finite difference for derivative approximation

    @par Semantic:

    @code
    T r = Derivincc<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-35);
    else if T is float
      r =  pow(2,-14);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Derivincc, Derivincc)
}

#include <boost/simd/constant/common.hpp>

#endif
