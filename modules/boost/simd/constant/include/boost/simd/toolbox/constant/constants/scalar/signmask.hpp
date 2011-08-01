//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_SIGNMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_SIGNMASK_HPP_INCLUDED

#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

BOOST_SIMD_STD_CONSTANT_TAG(Signmask)
BOOST_SIMD_STD_CONSTANT_DEF(Signmask)

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::Signmask,tag::cpu_
                            , (A0), (target_< scalar_< double_<A0> > >)
                            )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return splat<result_type>(bitwise_cast<result_type>(0x8000000000000000ll)); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::Signmask,tag::cpu_
                            , (A0), (target_< scalar_< float_<A0> > > ) )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return splat<result_type>(bitwise_cast<result_type>(0x80000000)); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::Signmask,tag::cpu_
                            , (A0), (target_< scalar_< unsigned_<A0> > > )
                            )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return boost::simd::splat<result_type>(0);
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::Signmask,tag::cpu_
                            , (A0), (target_< scalar_< signed_<A0> > > )
                            )
  {
    typedef typename A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename dispatch::meta::as_unsigned<result_type>::type base;
      BOOST_STATIC_CONSTANT(base, value = base(1) << (sizeof(base)*CHAR_BIT-1) );
      return boost::simd::splat<result_type>(base(value));
    }
  };
} } }

#endif
