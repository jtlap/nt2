//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OPENMP_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OPENMP_OUTER_FOLD_HPP_INCLUDED
#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <nt2/core/functions/outer_fold.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/openmp/openmp.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD
//==============================================================================
// openMP + SIMD
//==============================================================================
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::outer_fold_, nt2::tag::openmp_<Site>
                               , (A0)(S0)(T0)(N0)(A1)(A2)(A3)(A4)(Site)
                               , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((expr_< table_< unspecified_<A0>, S0 >
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
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t mbound =  boost::fusion::at_c<1>(ext);
      std::ptrdiff_t obound = boost::fusion::at_c<2>(ext);
      std::size_t id;

      std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
      std::size_t nb_vec = cache_line_size/(sizeof(value_type)*N);
      std::size_t cache_bound = (nb_vec)*N;
      std::size_t bound = ((ibound)/cache_bound) * cache_bound;

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

#pragma omp parallel
      {
#pragma omp for schedule(static) private(id)
        for(std::ptrdiff_t o = 0; o < obound; ++o)
        {
          std::size_t o_ = o*ibound;
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            for(std::size_t i = 0; i < bound; i+=cache_bound)
            {
              id = i+o_;

              for (std::size_t k = 0, k_ = id; k < nb_vec; ++k, k_+=N)
                nt2::run(out, k_, neutral(nt2::meta::as_<target_type>()));

              for(std::size_t m = 0; m < mbound; ++m)
              {
                std::size_t m_ = m*ibound;
                for (std::size_t k = 0, k_ = id; k < nb_vec; ++k, k_+=N)
                  nt2::run( out, k_
                          , bop( nt2::run(out, k_, meta::as_<target_type>())
                               , nt2::run(in, k_+m_, meta::as_<target_type>())
                               )
                          );
              }
            }
#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            // Store exception for late rethrow
            exception = boost::current_exception();
          }
#endif
          // scalar part
          for(std::size_t i = bound; i < ibound; ++i)
          {
            id = i+o_;
            nt2::run(out, id, neutral(nt2::meta::as_<value_type>()));
            for(std::size_t m = 0, m_ = 0; m < mbound; ++m, m_+=ibound)
            {
              nt2::run( out, id
                      , bop( nt2::run(out, id,meta::as_<value_type>())
                           , nt2::run(in, id+m_,meta::as_<value_type>())
                           )
                      );
            }
          }
        }
#ifndef BOOST_NO_EXCEPTIONS
        if(exception)
          boost::rethrow_exception(exception);
#endif
      }
    }
  };

} }
#else
namespace nt2 { namespace details
{
  template <class X, class N, class B, class U>
  BOOST_FORCEINLINE typename X::value_type
  outer_fold_step(X const& in, const std::size_t& p, const std::size_t& mbound, N const& neutral, B const& bop, U const& uop);

}}

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_fold_, nt2::tag::openmp_<Site>
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
      std::size_t id;
      const std::size_t chunk = config::top_cache_line_size()/sizeof(value_type);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      // - 1D loop nest as no epilogue or special cases occur
      // - static schedule is set on using cache line sized chunks to limit
      // effects of false sharing.
#pragma omp parallel for schedule(static,chunk)
      for(std::ptrdiff_t o = 0; o < obound; ++o)
      {
        std::size_t o_ = o*ibound;
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          for(std::size_t i = 0; i < ibound; ++i)
          {
            id = i+o_;
            nt2::run(out, id, details::outer_fold_step(in,id,mbound,neutral,bop,uop));
          }
#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          exception = boost::current_exception();
        }
#endif
      }
#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif
    }
  };

} }

#endif
#endif
#endif
