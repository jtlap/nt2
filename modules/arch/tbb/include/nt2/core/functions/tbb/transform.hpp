//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_TRANSFORM_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/include/functions/transform.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/tbb/tbb.hpp>
#include <nt2/sdk/tbb/blocked_range.hpp>
#include <nt2/sdk/tbb/worker.hpp>
#include <nt2/sdk/meta/display_type.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <cstddef>
#include <cstdio>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2 { namespace ext
{
  //============================================================================
  // Global tbb elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::tbb_<Site>
                            , (A0)(A1)(Site)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef void                                            result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      nt2::transform(a0,a1,0,nt2::numel(a0.extent()));
    }
  };

  //============================================================================
  // Partial tbb elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::tbb_<Site>
                            , (A0)(A1)(Site)(A2)(A3)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< integer_<A2> >)
                              (scalar_< integer_<A3> >)
                            )
  {
    typedef void                                            result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, A2 it, A3 sz) const
    {
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;

      std::size_t top_cache_line_size = config::top_cache_size()/sizeof(typename A0::value_type);
      std::size_t leftover = sz % top_cache_line_size;
      std::size_t ibound = (sz / top_cache_line_size)*top_cache_line_size;

       nt2::worker<tag::transform_,nt2::tag::tbb_<Site>,A0,A1> worker_(a0,a1);

      try
      {
#endif

        tbb::parallel_for( nt2::blocked_range<std::size_t>(it,it+ibound,top_cache_line_size)
                          ,worker_);

        if(leftover) worker_.work(a0,a1,it+ibound,leftover);



#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
#endif

#ifndef BOOST_NO_EXCEPTIONS
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };
} }

#endif
#endif
