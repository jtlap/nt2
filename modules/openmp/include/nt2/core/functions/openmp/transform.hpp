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
#include <nt2/sdk/openmp/openmp.hpp>
#include <cstddef>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/pop_front.hpp>

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
                            , (ast_<A0>)
                              (ast_<A1>)
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
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      #pragma omp parallel
      {
        // Local transform
        nt2::functor<tag::transform_,Site> transformer;

        // External and internal size
        typename A0::extent_type e = a0.extent();
        std::ptrdiff_t inner = boost::fusion::at_c<0>(e);
        std::ptrdiff_t outer = nt2::numel(boost::fusion::pop_front(e));

        // Current number of threads
        std::ptrdiff_t threads(omp_get_num_threads());

        // A table is "thin" if its outer dimension is at least twice as small
        // as its inner dimension or less than available threads
        // TODO: see if we shouldn't be less dogmatic here
        bool  is_thin( (inner > 2*outer) || (threads > outer));

        // How many inner block to process & dispatch w/r to "thinness"
        std::ptrdiff_t inner_block    = inner / (is_thin ? threads : 1);
        std::ptrdiff_t inner_leftover = inner % (is_thin ? threads : 1);

        // How many outer block to process & dispatch w/r to "thinness"
        std::ptrdiff_t outer_block    = outer / (is_thin ? 1 : threads);
        std::ptrdiff_t outer_leftover = outer % (is_thin ? 1 : threads);

#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          // Dispatch group of blocks over each threads
          #pragma omp for schedule(static)
          for(std::ptrdiff_t p=0;p<threads;++p)
          {
            // Perform laod balance of remaining elements per threads
            std::ptrdiff_t c_outer = outer_block*p + std::min(outer_leftover,p);
            std::ptrdiff_t c_inner = inner_block*p + std::min(inner_leftover,p);

            outer_block += outer_leftover ? ((outer_leftover > p) ? 1 : 0) : 0;
            inner_block += inner_leftover ? ((inner_leftover > p) ? 1 : 0) : 0;

            // Move forward starts of each block
            std::size_t i = is_thin ? c_inner*outer : c_outer*inner;

            // Call transform over the sub-architecture in the memory hierachy
            transformer(a0,a1,i,inner_block,outer_block);
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
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };

  //============================================================================
  // Partial openMP elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::openmp_<Site>
                            , (A0)(A1)(Site)(A2)(A3)(A4)
                            , (ast_<A0>)
                              (ast_<A1>)
                              (scalar_< integer_<A2> >)
                              (scalar_< integer_<A3> >)
                              (scalar_< integer_<A4> >)
                            )
  {
    typedef void                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, A2 it, A3 in, A4 out) const
    {
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      #pragma omp parallel
      {
        // Local transform
        nt2::functor<tag::transform_,Site> transformer;

        // External and internal size
        typename A0::extent_type e = a0.extent();
        std::ptrdiff_t inner = in;
        std::ptrdiff_t outer = out;

        // Current number of threads
        std::ptrdiff_t threads(omp_get_num_threads());

        // A table is "thin" if its outer dimension is at least twice as small
        // as its inner dimension or less than available threads
        // TODO: see if we shouldn't be less dogmatic here
        bool  is_thin( (inner > 2*outer) || (threads > outer));

        // How many inner block to process & dispatch w/r to "thinness"
        std::ptrdiff_t inner_block    = inner / (is_thin ? threads : 1);
        std::ptrdiff_t inner_leftover = inner % (is_thin ? threads : 1);

        // How many outer block to process & dispatch w/r to "thinness"
        std::ptrdiff_t outer_block    = outer / (is_thin ? 1 : threads);
        std::ptrdiff_t outer_leftover = outer % (is_thin ? 1 : threads);

#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          // Dispatch group of blocks over each threads
          #pragma omp for schedule(static)
          for(std::ptrdiff_t p=0;p<threads;++p)
          {
            // Perform load balance of remaining elements per threads
            std::ptrdiff_t c_outer = outer_block*p + std::min(outer_leftover,p);
            std::ptrdiff_t c_inner = inner_block*p + std::min(inner_leftover,p);

            outer_block += outer_leftover ? ((outer_leftover > p) ? 1 : 0) : 0;
            inner_block += inner_leftover ? ((inner_leftover > p) ? 1 : 0) : 0;

            // Move forward starts of each block
            std::size_t i = it + (is_thin ? c_inner*outer : c_outer*inner);

            // Call transform over the sub-architecture in the memory hierachy
            transformer(a0,a1,i,inner_block,outer_block);
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
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };
} }
#endif

#endif
