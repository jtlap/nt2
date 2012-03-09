//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_OPENMP_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_OPENMP_RUN_HPP_INCLUDED
#ifdef _OPENMP

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/openmp/openmp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <cstddef>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  // nD element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, nt2::tag::openmp_<Site>
                            , (A0)(S0)(T0)(N0)(A1)(T1)(N1)(Site)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , T0
                                     , N0
                                     >
                              ))
                              ((node_<A1, elementwise_<T1>, N1>))
                            )
  {
    typedef A0&                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      typename meta::call<tag::assign_(A0&, A1&)>::type
      assigned = nt2::assign(a0, a1);

      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      a0.resize(assigned.extent());

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      typename A0::index_type::type bs;
      #pragma omp parallel
      {
        std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
        std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
        std::ptrdiff_t bound  = boost::fusion::at_c<0>(assigned.extent()) + ilow;
        std::ptrdiff_t ibound = ilow + boost::fusion::at_c<0>(assigned.extent())/N*N;
        std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(assigned.extent()));

        #pragma omp for
        for(std::ptrdiff_t j=olow; j<obound; ++j)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            for(std::ptrdiff_t i=ilow; i<ibound; i+=N)
              nt2::run_assign(a0, a1, boost::fusion::vector_tie(i,j), meta::as_<target_type>());

            for(std::ptrdiff_t i=ibound; i<bound; ++i)
              nt2::run_assign(a0, a1, boost::fusion::vector_tie(i,j), meta::as_<stype>());
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

      return a0;
    }
  };

  // 1D element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::run_assign_, nt2::tag::openmp_<Site>
                            , (class A0)(class Shape)(class StorageKind)(std::ptrdiff_t Sz)(class T0)(class N0)
                              (class A1)(class T1)(class N1)
                              (class Site)
                            , ((expr_< table_< unspecified_<A0>, nt2::settings(nt2::of_size_<Sz>, Shape, StorageKind) >
                                     , T0
                                     , N0
                                     >
                              ))
                              ((node_<A1, elementwise_<T1>, N1>))
                            )
  {
    typedef A0&                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      typename meta::call<tag::assign_(A0&, A1&)>::type
      assigned = nt2::assign(a0, a1);

      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      a0.resize(assigned.extent());

      typename A0::index_type::type bs;
      std::ptrdiff_t low   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t bound = boost::fusion::at_c<0>(assigned.extent()) + low;
      std::ptrdiff_t aligned_bound  = low + boost::fusion::at_c<0>(assigned.extent())/N*N;

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      #pragma omp parallel for
      for(std::ptrdiff_t i=low; i<aligned_bound; i+=N)
      {
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          nt2::run_assign(a0, a1, boost::fusion::vector_tie(i), meta::as_<target_type>());
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

      for(std::ptrdiff_t i=aligned_bound; i<bound; ++i)
        nt2::run_assign(a0, a1, boost::fusion::vector_tie(i), meta::as_<stype>());

      return a0;
    }
  };

} }
#else
namespace nt2 { namespace ext
{
  // nD element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, nt2::tag::openmp_<Site>
                            , (A0)(S0)(T0)(N0)(A1)(T1)(N1)(Site)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , T0
                                     , N0
                                     >
                              ))
                              ((node_<A1, elementwise_<T1>, N1>))
                            )
  {
    typedef A0&                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      typename meta::call<tag::assign_(A0&, A1&)>::type
      assigned = nt2::assign(a0, a1);

      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      a0.resize(assigned.extent());

      typename A0::index_type::type bs;

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      #pragma omp parallel
      {
        std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
        std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
        std::ptrdiff_t bound  = boost::fusion::at_c<0>(assigned.extent()) + ilow;
        std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(assigned.extent()));

        #pragma omp for
        for(std::ptrdiff_t j=olow; j<obound; ++j)
        {
          for(std::ptrdiff_t i=ilow; i<bound; ++i)
          {
#ifndef BOOST_NO_EXCEPTIONS
            try
            {
#endif
              nt2::run_assign(a0, a1, boost::fusion::vector_tie(i,j), meta::as_<target_type>());
#ifndef BOOST_NO_EXCEPTIONS
            }
            catch(...)
            {
              exception = boost::current_exception();
            }
#endif
          }
        }
      }
#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif

      return a0;
    }
  };

  // 1D element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::run_, nt2::tag::openmp_<Site>
                            , (class A0)(class Shape)(class StorageKind)(std::ptrdiff_t Sz)(class T0)(class N0)
                              (class A1)(class T1)(class N1)
                              (class Site)
                            , ((expr_< table_< unspecified_<A0>, nt2::settings(nt2::of_size_<Sz>, Shape, StorageKind) >
                                     , T0
                                     , N0
                                     >
                              ))
                              ((node_<A1, elementwise_<T1>, N1>))
                            )
  {
    typedef A0&                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      typename meta::call<tag::assign_(A0&, A1&)>::type
      assigned = nt2::assign(a0, a1);

      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      a0.resize(assigned.extent());

      typename A0::index_type::type bs;
      std::ptrdiff_t low   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t bound = boost::fusion::at_c<0>(assigned.extent()) + low;

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      #pragma omp parallel for
      for(std::ptrdiff_t i=low; i<bound; ++i)
      {
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          nt2::run_assign(a0, a1, boost::fusion::vector_tie(i), meta::as_<target_type>());
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

      return a0;
    }
  };

} }
#endif

#endif
#endif
