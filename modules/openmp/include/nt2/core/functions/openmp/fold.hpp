//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OPENMP_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OPENMP_FOLD_HPP_INCLUDED
#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <nt2/core/functions/fold.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
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
  // Generates fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fold_, nt2::tag::openmp_<Site>
                              , (A1)(A2)(A3)(A4)(Site)
                              , ((ast_< A1>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;
    typedef typename boost::remove_reference<A1>::type::value_type             result_type;
    typedef boost::simd::native<result_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t aligned_bound = (boost::fusion::at_c<0>(ext)/N) * N;


      result_type out = neutral(nt2::meta::as_<result_type>());
      target_type gvec_out = neutral(nt2::meta::as_<target_type>());


      if( N <= (aligned_bound)){

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
        #pragma omp parallel 
        {
          target_type vec_out = neutral(nt2::meta::as_<target_type>());

          #pragma omp for schedule(static)
          for(std::size_t i =0; i < aligned_bound; i+=N)
          {

#ifndef BOOST_NO_EXCEPTIONS
            try
            {
#endif

              vec_out = bop(vec_out, nt2::run(in, i, meta::as_<target_type>()));

#ifndef BOOST_NO_EXCEPTIONS
            }
            catch(...)
            {
              // Store exception for late rethrow
              exception = boost::current_exception();
            }
#endif
           }

           #pragma omp critical
          gvec_out = bop(gvec_out, vec_out);
        }

#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif

        out = uop(gvec_out);

        // Process the scalar epilogue
        for(std::size_t i = aligned_bound; i < bound; ++i)
          out = bop(out, nt2::run(in, i, meta::as_<result_type>()));

      }
      else{
        //Use scalar version
        for(std::size_t i = 0 ; i < bound; ++i){
          out = bop(out, nt2::run(in, i, meta::as_<result_type>()));
        }
      }
      return out;     

    }
  };

} }

#else 
//==============================================================================
// openMP + no SIMD
//==============================================================================

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fold_, nt2::tag::openmp_<Site>
                              , (A1)(A2)(A3)(A4)(Site)
                              , ((ast_< A1>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;
    typedef typename boost::remove_reference<A1>::type::value_type             result_type;

    BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      std::size_t bound       = boost::fusion::at_c<0>(in.extent());
      result_type gout = neutral(nt2::meta::as_<result_type>());
      const std::size_t chunk = config::shared_cache_line_size()/sizeof(result_type);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      // - 1D loop nest as no epilogue or special cases occur
      // - static schedule is set on using cache line sized chunks to limit
      // effects of false sharing.
      #pragma omp parallel 
      {
        result_type out = neutral(nt2::meta::as_<result_type>());

        #pragma omp for schedule(static,chunk)
        for(std::size_t i = 0; i < bound; ++i){
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            out = bop(out, nt2::run(in, i, meta::as_<result_type>()));

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            exception = boost::current_exception();
          }
#endif
        }

        #pragma omp critical
        gout = bop(gout, out);

      }


#ifndef BOOST_NO_EXCEPTIONS
        if(exception)
          boost::rethrow_exception(exception);
#endif
        return gout;
        
      }
    
  };

} }

#endif
#endif
#endif
