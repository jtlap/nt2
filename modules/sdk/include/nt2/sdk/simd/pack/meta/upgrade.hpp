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
                , class Dummy 
                >
        struct upgrade< nt2::simd::pack<Type, Cardinal, Dummy>, Type >
        {
            typedef nt2::simd::pack<Type, Cardinal, Dummy> type;
        };
        
        template< class Type
                , std::size_t Cardinal
                , class Dummy 
                , class UpType
                >
        struct upgrade< nt2::simd::pack<Type, Cardinal, Dummy>, UpType >
        {
            typedef nt2::simd::pack<UpType, Cardinal/2, Dummy> type;
        };
    } }
    
    namespace meta
    {
        template< class Type
                , std::size_t Cardinal
                , class Dummy 
                >
        struct upgrade< simd::pack<Type, Cardinal, Dummy> >
        {
            typedef typename nt2::details::simd::upgrade<
                simd::pack<Type, Cardinal, Dummy>
              , typename upgrade<Type>::type
            >::type type;
        };
    }
}

#endif
