//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MINDENORMAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MINDENORMAL_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/double.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/sdk/config.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mindenormal generic tag

     Represents the Mindenormal constant in generic contexts.

     @par Models:
        Hierarchy
   **/

    #ifdef BOOST_SIMD_NO_DENORMALS
    struct Smallestposval;
    typedef Smallestposval Mindenormal;
    #else
    struct Mindenormal : ext::pure_constant_<Mindenormal>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Mindenormal> parent;

      /// INTERNAL ONLY
      template<class Target, class Dummy=void>
      struct apply : meta::int_c<typename Target::type,1> {};
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_Mindenormal( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Mindenormal::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<1> {};

    /// INTERNAL ONLY
    template<class T, class Dummy>
    struct  Mindenormal::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<1> {};
    #endif
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::Mindenormal, Site> dispatching_Mindenormal(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::Mindenormal, Site>();
   }
   template<class... Args>
   struct impl_Mindenormal;
  }
  /*!
    Constant Mindenormal : the least of all non zero positive value

    @par Semantic:

    @code
    T r = Mindenormal<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(1)
    else if T is double
      r =  4.940656458412465e-324;
    else if T is float
      r = 1.4012985e-45;
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mindenormal, Mindenormal)
} }

#ifdef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/constant/constants/smallestposval.hpp>
#endif

#include <boost/simd/constant/common.hpp>

#endif
