//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_DOWNGRADE_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace dispatch { namespace details
{
    template<class T>
    struct downgrade_is_smallest
         : boost::mpl::bool_< sizeof(T) == 1 >
    {
    };

    template<>
    struct downgrade_is_smallest<float>
         : boost::mpl::true_
    {
    };
} } }

namespace boost { namespace dispatch { namespace ext
{
    template< class Type
            , std::size_t Cardinal
            , class Sign
            >
    struct downgrade< boost::simd::pack<Type, Cardinal>, Sign, typename boost::disable_if< details::downgrade_is_smallest<typename meta::primitive_of<Type>::type> >::type >
    {
        typedef typename downgrade<Type, Sign>::type dT;
        typedef boost::simd::pack<dT, Cardinal*2> type;
    };
} } }

#endif
