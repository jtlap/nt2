//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_FUTURE_FUTURE_HPP_INCLUDED
#define NT2_SDK_HPX_FUTURE_FUTURE_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <hpx/include/lcos.hpp>
#include <hpx/include/util.hpp>

#include <nt2/sdk/shared_memory/future.hpp>

#include <type_traits>
#include <utility>

namespace nt2
{
    namespace tag
    {
        template<class T> struct hpx_;
    }

    template<class Site, class result_type>
    struct make_future<tag::hpx_<Site> , result_type>
    {
        typedef typename hpx::lcos::shared_future<result_type> type;
    };

    template< class Site, class result_type>
    struct make_ready_future_impl< tag::hpx_<Site>, result_type>
    {
        inline hpx::lcos::shared_future<result_type>
        call(result_type && value)
        {
            return  hpx::make_ready_future(value);
        }
    };

    template<class Site>
    struct async_impl< tag::hpx_<Site> >
    {
        template< typename F, typename ... A >
        inline typename make_future< tag::hpx_<Site>
                                   , typename std::result_of< F(A...) >::type
                                   >::type
        call(F && f, A && ... a)
        {
            return hpx::async( std::forward<F>(f)
                             , std::forward<A>(a) ...
                             );
        }
    };
}

#endif
#endif
