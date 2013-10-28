//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/openmp/openmp.hpp>

#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <nt2/sdk/shared_memory/spawner/spawner.hpp>
#include <nt2/sdk/shared_memory/spawner/parfor.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  template<class Site>
  struct spawner< tag::parfor_, tag::openmp_<Site> >
  {

    spawner() {}

    template<typename Worker>
    void operator()(Worker & worker_, std::size_t begin_, std::size_t size_, std::size_t grain_)
    {
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      std::size_t nblocks  = size_/grain_;
      std::size_t ibound   = nblocks * grain_;
      std::size_t leftover = size_ % grain_;

      #pragma omp parallel
      {
        // Dispatch group of blocks over each threads
        #pragma omp for schedule(dynamic)
        for(std::size_t n=0;n<nblocks;++n)
        {
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            // Call operation
            worker_(begin_+n*grain_,grain_);

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

#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
          if(leftover) worker_(begin_+ibound,leftover);

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            #pragma omp critical
            exception = boost::current_exception();
          }
#endif
       }

     }
   }
 };
}

#endif
