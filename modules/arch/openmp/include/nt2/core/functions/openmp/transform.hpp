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
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/openmp/openmp.hpp>
#include <cstddef>
#include <cstdio>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2 { namespace ext
{
  //============================================================================
  // Global openMP elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::openmp_<Site>
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
  // Partial openMP elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::openmp_<Site>
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
#endif

      std::size_t top_cache_line_size = config::top_cache_size()/sizeof(typename A0::value_type);
      std::size_t nblocks  = sz / top_cache_line_size;
      std::size_t leftover = sz % top_cache_line_size;

      #pragma omp parallel firstprivate(top_cache_line_size, nblocks, leftover)
      {
        // Local transform
        nt2::functor<tag::transform_,Site> transformer;

        // Dispatch group of blocks over each threads
        #pragma omp for schedule(dynamic) nowait
        for(std::ptrdiff_t n=0;n<nblocks;++n)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            // Call transform over the sub-architecture in the memory hierachy
            transformer(a0,a1,it+n*top_cache_line_size,top_cache_line_size);

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            #pragma omp critical
            exception = boost::current_exception();
          }
#endif
        }
        #pragma omp single nowait
        {
         if(leftover) transformer(a0,a1,it+nblocks*top_cache_line_size,leftover);
        }
      }
#ifndef BOOST_NO_EXCEPTIONS
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };
} }
#endif

#endif
