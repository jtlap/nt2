//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMAX_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMAX_HPP_INCLUDED

#include <boost/simd/reduction/functions/posmax.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/reduction/functions/simd/common/maximum.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/repeat.hpp>
#define LOOP(z,INDEX,_)  \
if (m<extract<INDEX>(a0)) \
{                        \
  m=extract<INDEX>(a0);  \
  p=INDEX;               \
}                        \

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::posmax_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;

      result_type p = 0;
      stype m = a0[0];

      // TODO UNROLL
      /*for(size_t i=1; i < boost::simd::meta::cardinal_of<A0>::value; i++)
      {
        if (m < a0[i])
        {
          m = a0[i];
          p = i;
        }
      }*/
      BOOST_PP_REPEAT_FROM_TO(1,8,LOOP,_)
     // BOOST_PP_REPEAT(4,LOOP,DATA)
    //  BOOST_PP_REPEAT_FROM_TO(1,3,LOOP,X)
      return p;
    }
   };

} } }

#endif






/*#define BOOST_SIMD_UNROLL
p=0;
m=max(a0)
if m==a0[1];
    p=1;
    break ;
if m<a0[2];
    p=2;

if m<a0[3];
    p=3;
*/
