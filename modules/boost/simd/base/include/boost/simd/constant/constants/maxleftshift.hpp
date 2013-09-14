//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/meta/int_c.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxleftshift generic tag

     Represents the Maxleftshift constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct Maxleftshift : ext::pure_constant_<Maxleftshift>
    {
      typedef double default_type;
      typedef ext::pure_constant_<Maxleftshift> parent;

      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename dispatch::meta::
                                     as_integer < typename Target::type
                                                , signed
                                                >::type
                          , sizeof(typename Target::type)*CHAR_BIT-1
                          > {};
    };
  }
  /*!
    Constant Maxleftshift
    It is senseless to shift a value of more bits than the number of bits - 1
    of the value type: this is that number.
    \par
    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Maxleftshift<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxleftshift, Maxleftshift)
} }

#include <boost/simd/constant/common.hpp>

#endif
