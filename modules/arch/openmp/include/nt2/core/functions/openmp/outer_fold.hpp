//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
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
#include <boost/simd/memory/align_under.hpp>
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
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::outer_fold_, nt2::tag::openmp_<Site>
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
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& ) const
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
      std::size_t nblocs   = obound / grain;
      std::size_t leftover = obound - nblocs*grain;

      nt2::worker<tag::outer_fold_,tag::openmp_<Site>,A0,A1,A2,A3>
      vecworker( out, in, neutral, bop);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

#pragma omp parallel
      {

        #pragma omp for schedule(static)
        for(std::size_t n=0;n<nblocs;++n)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif

            vecworker((std::size_t)n*grain,grain);

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            #pragma omp critical
            // Store exception for late rethrow
            exception = boost::current_exception();
          }
#endif
        }

        #pragma omp single nowait
        {
          if(leftover) vecworker(nblocs*grain,leftover);
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
    typedef void                                                    result_type;
    typedef typename A0::value_type                                 value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type extent_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
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
