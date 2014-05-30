//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_SPAWNER_SCAN_HPP_INCLUDED
#define NT2_SDK_OPENMP_SPAWNER_SCAN_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <omp.h>
#include <nt2/sdk/shared_memory/spawner.hpp>

namespace nt2
{
  namespace tag
    {
      struct scan_;
      template<class T> struct openmp_;
    }

  template<class Site, class result_type>
  struct spawner< tag::scan_, tag::openmp_<Site> , result_type>
  {

    spawner() {}

    template<typename Worker>
    void operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t)
    {
        result_type summary = w.neutral_(nt2::meta::as_<result_type>());

        // Call operation
        summary = w(summary,begin,size,false);
    }
  };
}

#endif
#endif
