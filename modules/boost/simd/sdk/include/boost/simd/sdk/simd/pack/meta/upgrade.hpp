/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED

#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/mpl/if.hpp>


namespace boost { namespace dispatch
{
    namespace details { namespace simd
    {
        template<typename T, typename U>
        struct upgrade;
        
        template< class Type
                , std::size_t Cardinal
                >
        struct upgrade< boost::simd::pack<Type, Cardinal>, Type >
        {
            typedef boost::simd::pack<Type, Cardinal> type;
        };
        
        template< class Type
                , std::size_t Cardinal
                , class UpType
                >
        struct upgrade< boost::simd::pack<Type, Cardinal>, UpType >
        {  
          typedef boost::simd::pack<UpType, Cardinal/2> type;
        };
    } }
    
    namespace meta
    {
        template< class Type
                , std::size_t Cardinal
                >
        struct upgrade< boost::simd::pack<Type, Cardinal> >
        {
          typedef typename upgrade<Type>::type uT;

          typedef typename
          boost::mpl::if_< typename 
                           simd::meta::is_vectorizable<uT,BOOST_SIMD_DEFAULT_EXTENSION>::type
                           , typename boost::dispatch::details::simd::upgrade<
                                          boost::simd::pack<Type, Cardinal>
                                        , uT>::type
                           , typename boost::simd::pack<Type, Cardinal>
                           >::type type;
        };
    }
  
} }


#endif
