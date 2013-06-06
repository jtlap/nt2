//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUPS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUPS_HPP_INCLUDED

#include <boost/simd/swar/functions/groups.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/functions/simd/saturate.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is downgradable
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::groups_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::downgrade<A0>::type> >),
                          ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                        )
  {

    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return group(saturate<result_type>(a0), saturate<result_type>(a1));
    }
  };
} } }
#endif
