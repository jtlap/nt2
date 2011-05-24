/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_META_UPGRADE_HPP_INCLUDED

#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/simd/pack/forward.hpp>

namespace nt2
{
    namespace details { namespace simd
    {
        template<typename T, typename U>
        struct upgrade;
        
        template< class Type
                , std::size_t Cardinal
                >
        struct upgrade< nt2::simd::pack<Type, Cardinal>, Type >
        {
            typedef nt2::simd::pack<Type, Cardinal> type;
        };
        
        template< class Type
                , std::size_t Cardinal
                , class UpType
                >
        struct upgrade< nt2::simd::pack<Type, Cardinal>, UpType >
        {
            typedef nt2::simd::pack<UpType, Cardinal/2> type;
        };
    } }
    
    namespace meta
    {
        template< class Type
                , std::size_t Cardinal
                >
        struct upgrade< simd::pack<Type, Cardinal> >
        {
            typedef typename nt2::details::simd::upgrade<
                simd::pack<Type, Cardinal>
              , typename upgrade<Type>::type
            >::type type;
        };
    }
}

#endif
