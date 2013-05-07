//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace dispatch { namespace ext
{
    template< class Type
            , std::size_t Cardinal
            , class Sign
            >
    struct upgrade< boost::simd::pack<Type, Cardinal>, Sign, typename boost::enable_if_c< (sizeof(typename meta::primitive_of<Type>::type) < 8) >::type >
    {
      typedef typename upgrade<Type, Sign>::type uT;
      typedef boost::simd::pack<uT, Cardinal/2> type;
    };

} } }


#endif
