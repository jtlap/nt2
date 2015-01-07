//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#if !BOOST_PP_IS_ITERATING
#ifndef NT2_SDK_OPENMP_FUTURE_WHEN_ALL_HPP_INCLUDED
#define NT2_SDK_OPENMP_FUTURE_WHEN_ALL_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 201307 /* OpenMP 4.0 */

#include <omp.h>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <nt2/sdk/shared_memory/future.hpp>
#include <nt2/sdk/openmp/future/details/openmp_future.hpp>

#include <vector>

namespace nt2
{
  template<class Site>
  struct when_all_impl< tag::openmp_<Site> >
  {
    template <typename Future>
    details::openmp_future<int>
    call( std::vector<Future> && lazy_values )
    {
      typedef typename details::openmp_future<int> future;

      std::size_t size( lazy_values.size() );

      future future_res;
      bool * next( future_res.ready_.get() );
      bool * deps[size];

      for (std::size_t i=0; i<size; i++)
      {
        future_res.attach_previous_future(lazy_values[i]);
        deps[i] = lazy_values[i].ready_.get();
      }

      #pragma omp task \
      firstprivate(future_res, next, deps) \
      depend( in : deps[0:size] ) \
      depend( out : next )
      {
        *(future_res.res_) = 1;
        *next = true;
      }

      return future_res;
    }

#define BOOST_PP_ITERATION_PARAMS_1 (3, \
    ( 1, BOOST_DISPATCH_MAX_ARITY, \
      "nt2/sdk/openmp/future/when_all.hpp") \
    )

#include BOOST_PP_ITERATE()
};
}

#endif
#endif

#else

#define N BOOST_PP_ITERATION()

#define POINT(a,b) a.b

#define NT2_FUTURE_FORWARD_ARGS(z,n,t) details::openmp_future<A##n> const & a##n
#define NT2_FUTURE_FORWARD_ARGS1(z,n,t) bool * r##n = POINT(a##n,ready_).get();
#define NT2_FUTURE_FORWARD_ARGS2(z,n,t) future_res.attach_previous_future( a##n );
#define NT2_FUTURE_FORWARD_ARGS3(z,n,t) boost::ignore_unused(r##n);

    template< BOOST_PP_ENUM_PARAMS(N, typename A) >
    details::openmp_future<int> call( BOOST_PP_ENUM(N,NT2_FUTURE_FORWARD_ARGS, ~) )
    {
      details::openmp_future<int> future_res;

      bool * next( future_res.ready_.get() );

      BOOST_PP_REPEAT(N, NT2_FUTURE_FORWARD_ARGS1, ~)
      BOOST_PP_REPEAT(N, NT2_FUTURE_FORWARD_ARGS2, ~)
      BOOST_PP_REPEAT(N, NT2_FUTURE_FORWARD_ARGS3, ~)

      #pragma omp task \
      firstprivate(future_res, next, BOOST_PP_ENUM_PARAMS(N,r) ) \
      depend( in : BOOST_PP_ENUM_PARAMS(N,r) ) \
      depend( out : next )
      {
        *(future_res.res_) = 1;
        *next = true;
      }

      return future_res;
    }

#undef NT2_FUTURE_FORWARD_ARGS
#undef NT2_FUTURE_FORWARD_ARGS1
#undef NT2_FUTURE_FORWARD_ARGS2
#undef NT2_FUTURE_FORWARD_ARGS3
#undef POINT
#undef N

#endif
