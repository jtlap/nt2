//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_OUTER_FOLD_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/sdk/tbb/worker.hpp>
#include <nt2/core/functions/outer_fold.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/simd/memory/align_under.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/tbb/tbb.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD
//==============================================================================
// tbb + SIMD
//==============================================================================
namespace nt2{ namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::outer_fold_, nt2::tag::tbb_<Site>
                                , (A0)(K0)(S0)(T0)(N0)(A1)(A2)(A3)(A4)(Site)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename A0::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((expr_ < container_<K0,unspecified_<A0>,S0>
                                          , T0
                                          , N0
                                          >
                                  ))
                                  ((ast_< A1, nt2::container::domain>))
                                  (unspecified_<A2>)
                                  (unspecified_<A3>)
                                  (unspecified_<A4>)
                                )
  {
    typedef void                                                              result_type;
    typedef typename A0::value_type                                           value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const&) const
    {
      extent_type ext = in.extent();
      std::size_t obound = boost::fusion::at_c<2>(ext);
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t top_cache_line_size = config::top_cache_size(2)/sizeof(typename A0::value_type);
      if(!top_cache_line_size) top_cache_line_size = 1u;

      std::size_t a(ibound);
      std::size_t b(top_cache_line_size);
      while (b) {
        std::size_t  r = a % b;
        a = b;
        b = r;
      }

      std::size_t grain = top_cache_line_size/a;

      nt2::worker<tag::outer_fold_,tag::tbb_<Site>,A0,A1,A2,A3> vecworker( out, in, neutral, bop);


#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
      try
      {
#endif
        tbb::parallel_for( nt2::blocked_range<std::size_t>(0,obound,grain)
                         , vecworker
                         );
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        // Store exception for late rethrow
        exception = boost::current_exception();
      }
      if(exception)
        boost::rethrow_exception(exception);
#endif
    }
  };

  } }
#else
//==============================================================================
// tbb + noSIMD
//==============================================================================
namespace nt2
{
  namespace details
  {
    template <class X, class N, class B, class U>
    BOOST_FORCEINLINE typename X::value_type
    outer_fold_step(X const& in, const std::size_t& p, const std::size_t& mbound, N const& neutral, B const& bop, U const& uop);

    template<class A0, class A1, class A2, class A3, class A4>
    struct outer_reduce_scal
    {
      outer_reduce_scal( A0& out, A1& in, A2 const& n, A3 const& bop
                       , A4 const& uop, std::size_t const& ibound
                       , std::size_t const& obound, std::size_t const& mbound
                       )
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      , ibound_(ibound), obound_(obound), mbound_(mbound)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        std::size_t id_;
        std::size_t o_;

        for(std::ptrdiff_t o = r.begin(); o < r.end(); ++o)
        {
          o_  = o*ibound_;
          for(std::size_t i = 0; i < ibound_; ++i)
          {
            id_ = i+o_;
            nt2::run(out_, id_, details::outer_fold_step(in_,id_,mbound_,neutral_,bop_,uop_));
          }
        }
      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      A4                      uop_;
      std::size_t          ibound_;
      std::size_t          obound_;
      std::size_t          mbound_;
    };
  }

  namespace ext
  {
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_fold_, nt2::tag::tbb_<Site>
                              , (A0)(A1)(A2)(A3)(A4)(Site)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t mbound = boost::fusion::at_c<1>(ext);
      std::ptrdiff_t obound = boost::fusion::at_c<2>(ext);
      const std::size_t grain = obound/tbb::task_scheduler_init::default_num_threads();
      details::outer_reduce_scal< A0,A1,A2,A3,A4> ored( out, in, neutral, bop
                                                      , uop, ibound,obound
                                                      , mbound
                                                      );
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
      try
      {
#endif
        tbb::parallel_for( tbb::blocked_range<std::ptrdiff_t>(0,obound,grain)
                         , ored
                         );
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
      if(exception)
        boost::rethrow_exception(exception);
#endif
    }

  };

} }

#endif
#endif
#endif
