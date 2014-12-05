//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_FUTURE_DETAILS_TBB_TASK_WRAPPER_HPP_INCLUDED
#define NT2_SDK_TBB_FUTURE_DETAILS_TBB_TASK_WRAPPER_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <tuple>

namespace nt2
{
    namespace details
    {
      template< class F, typename future_type, typename ... A>
      struct tbb_task_wrapper
      {
          tbb_task_wrapper( F && f, future_type && future_result, A&& ... a)
          : f_(std::forward<F>(f))
          , future_result_(std::forward<future_type>(future_result))
          , a_( std::make_tuple(std::forward<A>(a) ...) )
          {}

          template < std::size_t N >
          struct apply_tuple_func
          {
          };

          void operator()(const tbb::flow::continue_msg )
          {
              tbb::mutex::scoped_lock lock(future_result_.mutex_);

              *(future_result_.res_) = f_( a_ ... );

              *(future_result_.ready_) = true;
          }

          F f_;
          future_type future_result_;
          std::tuple < A ... > a_;
      };

    }
}

#endif
#endif
