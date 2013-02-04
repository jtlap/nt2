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

#include <nt2/core/functions/outer_fold.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
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
namespace nt2
{
  namespace details
  {
    // Create the correct functor for tbb::parallel reduce according to the
    // requested Site.
    template<class A0, class A1, class A2, class A3, class Target, class Value>
    struct outer_reduce_simd
    {
      typedef Target target_type;
      typedef Value   value_type;

      outer_reduce_simd( A0& out, A1& in, A2 const& n, A3 const& bop
                       , std::size_t const&  bound, std::size_t const& ibound
                       , std::size_t const& obound, std::size_t const& mbound
                       , std::size_t const& cache_bound, std::size_t const& nb_vec
                       )
      : out_(out), in_(in), neutral_(n), bop_(bop), bound_(bound)
      , ibound_(ibound), obound_(obound), mbound_(mbound), cache_bound_(cache_bound)
      , nb_vec_(nb_vec)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
        std::size_t id_;

        for(std::ptrdiff_t o = r.begin(); o < r.end(); ++o)
        {
          std::size_t o_ = o*ibound_;
          for(std::size_t i = 0; i < bound_; i+=cache_bound_)
          {
            id_ = i+o_;

            for (std::size_t k = 0, k_ = id_; k < nb_vec_; ++k, k_+=N)
              nt2::run(out_, k_, neutral_(nt2::meta::as_<target_type>()));

            for(std::size_t m = 0; m < mbound_; ++m)
            {
              std::size_t m_ = m*ibound_;
              for (std::size_t k = 0, k_ = id_; k < nb_vec_; ++k, k_+=N)
                nt2::run( out_, k_
                        , bop_( nt2::run(out_, k_   , meta::as_<target_type>())
                              , nt2::run(in_ , k_+m_, meta::as_<target_type>())
                              )
                        );
            }
          }

          // scalar part
          for(std::size_t i = bound_; i < ibound_; ++i)
          {
            id_ = i+o_;
            nt2::run(out_, id_, neutral_(nt2::meta::as_<value_type>()));
            for(std::size_t m = 0, m_ = 0; m < mbound_; ++m, m_+=ibound_)
            {
              nt2::run( out_, id_
                      , bop_( nt2::run(out_, id_   , meta::as_<value_type>())
                            , nt2::run(in_ , id_+m_, meta::as_<value_type>())
                            )
                      );
            }
          }
        }
      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      std::size_t           bound_;
      std::size_t          ibound_;
      std::size_t          obound_;
      std::size_t          mbound_;
      std::size_t     cache_bound_;
      std::size_t          nb_vec_;
    };
  }

  namespace ext
  {
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::outer_fold_, nt2::tag::tbb_<Site>
                               , (A0)(S0)(A1)(A2)(A3)(A4)(Site)
                               , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((expr_< table_< unspecified_<A0>, S0 >
                                        , nt2::tag::terminal_
                                        , boost::mpl::long_<0>
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
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t mbound =  boost::fusion::at_c<1>(ext);
      std::ptrdiff_t obound = boost::fusion::at_c<2>(ext);
      const std::size_t grain = obound/tbb::task_scheduler_init::default_num_threads();

      std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
      std::size_t nb_vec = cache_line_size/(sizeof(value_type)*N);
      std::size_t cache_bound = (nb_vec)*N;
      std::size_t bound = ((ibound)/cache_bound) * cache_bound;
      details::outer_reduce_simd< A0,A1,A2,A3
                                , target_type
                                , value_type> ored( out, in, neutral, bop
                                                  , bound, ibound,obound
                                                  , mbound, cache_bound
                                                  , nb_vec);

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
