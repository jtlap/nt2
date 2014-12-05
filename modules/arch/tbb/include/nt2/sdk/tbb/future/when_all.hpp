//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_WHEN_ALL_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_WHEN_ALL_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <nt2/sdk/shared_memory/future.hpp>

#include <nt2/sdk/tbb/future/details/tbb_future.hpp>
#include <nt2/sdk/tbb/future/details/empty_body.hpp>

#include <cstdio>

namespace nt2
{

    namespace details
    {
        struct empty_functor
        {
            typedef int result_type;

            int operator()() const
            {
              return 0;
            }
        };
    }

    template<class Site>
    struct when_all_impl< tag::tbb_<Site> >
    {
       typedef typename tbb::flow::continue_node<\
       tbb::flow::continue_msg> node_type;

        template <typename Future>
        details::tbb_future< int >
        call( std::vector<Future> & lazy_values )
        {
           typedef typename details::tbb_future<int> future;

           future future_res;

           node_type * c = new node_type( *(future_res.getWork()),
             details::tbb_task_wrapper<details::empty_functor,future>
               (details::empty_functor(), future_res)
             );

           future_res.getTaskQueue()->push_back(c);

           for (std::size_t i=0; i<lazy_values.size(); i++)
           {
             future_res.attach_previous_future(lazy_values[i]);
             tbb::flow::make_edge(*(lazy_values[i].node_),*c);
           }

           future_res.attach_task(c);
           return future_res;
        }

        template< typename ... A >
        details::tbb_future<int>
        call( details::tbb_future<A> const & a ... )
        {
            typedef typename details::tbb_future<int> future;

            future future_res;

            node_type * c = new node_type( *future_res.getWork(),
              details::tbb_task_wrapper0<details::empty_functor,future>
                (details::empty_functor(), future_res)
              );

            future_res.getTaskQueue()->push_back(c);

            tbb::flow::make_edge(*(a.node_),*c) ... ;
            future_res.attach_previous_future( a ) ... ;

            future_res.attach_task(c);

            return future_res;
         }
    };
}

#endif
#endif
