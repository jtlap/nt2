//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_SPAWNER_FOLD_HPP_INCLUDED
#define NT2_SDK_HPX_SPAWNER_FOLD_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <hpx/include/lcos.hpp>
#include <hpx/lcos/future_wait.hpp>

#include <nt2/sdk/shared_memory/spawner.hpp>

#include <boost/assert.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  namespace tag
  {
    struct fold_;
    template<class T> struct hpx_;
  }

  template<class Site, class result_type>
  struct spawner< tag::fold_, tag::hpx_<Site> , result_type>
  {

    spawner() {}

    template<typename Worker>
    result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {

      BOOST_ASSERT_MSG( size % grain == 0, "Reduce size not divisible by grain");

      if (size == grain)
       {
         result_type out = w.neutral_(nt2::meta::as_<result_type>());
         w(out,begin,size);
         return out;
        }

       std::size_t middle = begin + (size/(2*grain))*grain;

       hpx::lcos::future<result_type>
          other_out = hpx::async((*this),w,middle,begin+size-middle,grain);
       result_type my_out = (*this)(w, begin, middle-begin, grain);
       return w.bop_( my_out, other_out.get() );

    }
  };
}


#endif

#endif
