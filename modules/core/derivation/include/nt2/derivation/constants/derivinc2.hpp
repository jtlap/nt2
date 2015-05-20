//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_CONSTANTS_DERIVINC2_HPP_INCLUDED
#define NT2_DERIVATION_CONSTANTS_DERIVINC2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief Derivinc2 generic tag

     Represents the Derivinc2 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Derivinc2, double, 1
                                , 0x3d000000, 0x3f30000000000000ll
                                )
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Derivinc2, Site>
   dispatching_Derivinc2(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Derivinc2, Site>();
   }
   template<class... Args>
   struct impl_Derivinc2;
  }
  /*!
    Generate an increment for finite difference for second
    derivative approximation

    @par Semantic:

    @code
    T r = Derivinc2<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-12);
    else if T is float
      r =  pow(2,-5);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Derivinc2, Derivinc2)
}

#include <boost/simd/constant/common.hpp>

#endif
