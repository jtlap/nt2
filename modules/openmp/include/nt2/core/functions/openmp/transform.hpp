//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OPENMP_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OPENMP_TRANSFORM_HPP_INCLUDED
#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/openmp/openmp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <cstddef>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  // nD element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::openmp_<Site>
                            , (A0)(A1)(S1)(T1)(N1)(Site)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, S1 >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      const std::size_t chunk    = config::shared_cache_line_size()/sizeof(stype);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      typename A0::index_type::type bs;
      #pragma omp parallel
      {
        const std::size_t in_sz     = boost::fusion::at_c<0>(a0.extent());
        const std::size_t in_sz_bnd = (in_sz/N)*N;
        const std::size_t outer_sz  = nt2::numel(boost::fusion::pop_front(a0.extent()));

        std::size_t it = 0;
        #pragma omp for schedule(dynamic,chunk)
        for(std::size_t j=0; j<outer_sz; ++j)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            for(std::size_t i=0; i < in_sz_bnd; i+=N, it+=N)
              nt2::run(a0, it, nt2::run(a1, it, meta::as_<target_type>()));

            for(std::size_t i=in_sz_bnd; i < in_sz; ++i, ++it)
              nt2::run(a0, it, nt2::run(a1, it, meta::as_<stype>()));
#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            exception = boost::current_exception();
          }
#endif
        }
      }
#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif
    }
  };

  // 1D element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::transform_, nt2::tag::openmp_<Site>
                            , (class A0)(class A1)(class Shape)(class StorageKind)(std::ptrdiff_t Sz)(class T1)(class N1)
                              (class Site)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, nt2::settings(nt2::of_size_<Sz>, Shape, StorageKind) >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      const std::size_t chunk    = config::shared_cache_line_size()/sizeof(stype);

      std::size_t bound = boost::fusion::at_c<0>(a0.extent());
      std::size_t aligned_bound  = (bound/N)*N;

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      #pragma omp parallel for schedule(dynamic,chunk)
      for(std::size_t i=0; i<aligned_bound; i+=N)
      {
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          nt2::run(a0, i, nt2::run(a1, i, meta::as_<target_type>()));
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

      for(std::size_t i=aligned_bound; i<bound; ++i)
        nt2::run(a0, i, nt2::run(a1, i, meta::as_<stype>()));
    }
  };

} }
#else
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::openmp_<Site>
                            , (A0)(A1)(S1)(T1)(N1)(Site)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, S1 >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      std::size_t bound       = boost::fusion::at_c<0>(a0.extent());
      const std::size_t chunk = config::shared_cache_line_size()/sizeof(stype);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      #pragma omp parallel for schedule(dynamic,chunk)
      for(std::size_t i=0; i<bound; ++i)
      {
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          nt2::run(a0, i, nt2::run(a1, i, meta::as_<target_type>()));
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
