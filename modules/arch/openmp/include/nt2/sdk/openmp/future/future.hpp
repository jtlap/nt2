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
#ifndef NT2_SDK_OPENMP_FUTURE_FUTURE_HPP_INCLUDED
#define NT2_SDK_OPENMP_FUTURE_FUTURE_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 201307 /* OpenMP 4.0 */

#include <omp.h>
#include <unistd.h>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <nt2/sdk/shared_memory/future.hpp>
#include <nt2/sdk/openmp/future/details/openmp_future.hpp>

#include <type_traits>

namespace nt2
{
  namespace tag
  {
    template<class T> struct openmp_;
  }

  template<class Site, class result_type>
  struct make_future<tag::openmp_<Site> , result_type>
  {
    typedef typename nt2::details::openmp_future<result_type> type;
  };

  template< class Site, class result_type>
  struct make_ready_future_impl< tag::openmp_<Site>, result_type>
  {
    inline details::openmp_future<result_type>
    call(result_type value)
    {
      details::openmp_future<result_type> future_res;
      bool * next( future_res.ready_.get() );

      #pragma omp task \
      firstprivate(future_res,next,value) \
      depend(out: next)
      {
        *(future_res.res_) = value;
        *next = true;
      }

      return future_res;
    }
  };

  template<class Site>
  struct async_impl< tag::openmp_<Site> >
  {
#define BOOST_PP_ITERATION_PARAMS_1 (3, \
    ( 0, 10, "nt2/sdk/openmp/future/future.hpp") \
    )
#include BOOST_PP_ITERATE()
};
}

#endif
#endif

#else

#define N BOOST_PP_ITERATION()

#define NT2_FUTURE_FORWARD_ARGS(z,n,t) A##n && a##n##_
#define NT2_FUTURE_FORWARD_ARGS1(z,n,t) A##n a##n ( std::forward<A##n> (a##n##_) );

    template< typename F
    BOOST_PP_COMMA_IF(N)
    BOOST_PP_ENUM_PARAMS(N, typename A)
    >
    inline typename make_future< tag::openmp_<Site>
                               , typename std::result_of<
                                 F(BOOST_PP_ENUM_PARAMS(N, A))
                                 >::type
                               >::type
    call(F && f
      BOOST_PP_COMMA_IF(N)
      BOOST_PP_ENUM(N,NT2_FUTURE_FORWARD_ARGS, ~)
      )
    {
      typedef typename std::result_of<F(BOOST_PP_ENUM_PARAMS(N, A))>::type result_type;

      details::openmp_future<result_type> future_res;
      F f_( std::forward<F> (f) );

      BOOST_PP_REPEAT(N, NT2_FUTURE_FORWARD_ARGS1, ~)

      bool * next( future_res.ready_.get() );

      #pragma omp task \
      firstprivate(future_res,next,f_ \
      BOOST_PP_COMMA_IF(N) \
      BOOST_PP_ENUM_PARAMS(N, a) \
      ) \
      depend(out: next)
      {
        *(future_res.res_) = f_(BOOST_PP_ENUM_PARAMS(N, a));
        *next = true;
      }

      return future_res;
    }

#undef NT2_FUTURE_FORWARD_ARGS
#undef NT2_FUTURE_FORWARD_ARGS1
#undef N

#endif
