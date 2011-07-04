//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_VALMAX_HPP_INCLUDED

#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/as_unsigned.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::val_max_,tag::cpu_
                            , (A0), (target_< scalar_< double_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const
      that = {0x7fefffffffffffffLL};
      return splat<result_type>(that.value);
    }
  };
} } }

namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::val_max_,tag::cpu_
                            , (A0), (target_< scalar_< float_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const
      that = {0x7f7fffff};
      return splat<result_type>(that.value);
    }
  };
} } }

namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::val_max_,tag::cpu_,(A0)
                            , (target_< scalar_< unsigned_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::scalar_of<result_type>::type base;
      return splat<result_type>(static_cast<base>(~0));
    }
  };
} } }

namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::val_max_,tag::cpu_
                            , (A0), (target_< scalar_< signed_<A0> > > )
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::as_unsigned<result_type>::type base;
      BOOST_STATIC_CONSTANT(base, value = base(1) << (sizeof(base)*CHAR_BIT-1) );
      return splat<result_type>(base(~value));
    }
  };
} } }

#endif
