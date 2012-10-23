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

      #pragma omp parallel
      {
        // Local transform
        nt2::functor<tag::transform_,Site> transformer;

        // Current number of threads
        std::ptrdiff_t threads(omp_get_num_threads());

        // How many inner block to process & dispatch w/r to "thinness"
        std::size_t    local_size     = sz / threads;
        std::ptrdiff_t local_leftover = sz % threads;

        // Dispatch group of blocks over each threads
        #pragma omp for schedule(static)
        for(std::ptrdiff_t p=0;p<threads;++p)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            // Move forward starts of each block
            std::ptrdiff_t offset = local_size*p + std::min(local_leftover,p);

            // Adjust number of elements to process w/r to leftovers
            local_size += local_leftover ? ((local_leftover > p) ? 1 : 0) : 0;

            // Call transform over the sub-architecture in the memory hierachy
            transformer(a0,a1,it+offset,local_size);
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
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };
} }
#endif

#endif
