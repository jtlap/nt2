//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_CONSTANTS_DERIVINCGM_HPP_INCLUDED
#define NT2_DERIVATION_CONSTANTS_DERIVINCGM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Derivincgm generic tag

     Represents the Derivincgm constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Derivincgm, double, 1
                                , 0x3b000000, 0x3ed0000000000000ll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Derivincgm, Site>
   dispatching_Derivincgm(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Derivincgm, Site>();
   }
   template<class... Args>
   struct impl_Derivincgm;
  }
  /*!
    Generate an increment for finite difference for second
    derivative approximation

    @par Semantic:

    @code
    T r = Derivincgm<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-18);
    else if T is float
      r =  pow(2,-9);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Derivincgm, Derivincgm)
}

#include <boost/simd/constant/common.hpp>

#endif
