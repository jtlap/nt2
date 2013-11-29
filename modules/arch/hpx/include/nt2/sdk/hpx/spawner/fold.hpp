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

  namespace details
  {
     template<class Worker, class result_type>
     struct Hpx_Folder
     {
       Hpx_Folder(){}

       result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
       {
         result_type reduced_out = w.neutral_(nt2::meta::as_<result_type>());
         std::vector< hpx::lcos::future<result_type> > out;

#ifndef BOOST_NO_EXCEPTIONS
         boost::exception_ptr exception;
#endif

#ifndef BOOST_NO_EXCEPTIONS
      try
      {
#endif

         if(size == grain) w(reduced_out,begin,size);
         else
         {
           while (size > grain)
           {
              std::size_t middle = begin + (size/(2*grain))*grain;
              out.push_back( hpx::async((*this),w,middle,begin+size-middle,grain) );
              size = middle - begin;
           }

           w(reduced_out,begin,size);

           for(std::size_t i=0; i<out.size(); i++)
              reduced_out = w.bop_( reduced_out, out[i].get() );
        }

#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
#endif

        return reduced_out;
     }
   };
  }

  template<class Site, class result_type>
  struct spawner< tag::fold_, tag::hpx_<Site> , result_type>
  {

    spawner() {}

    template<typename Worker>
    result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {

      BOOST_ASSERT_MSG( size % grain == 0, "Reduce size not divisible by grain");

      details::Hpx_Folder<Worker, result_type> hpx_w;
      return hpx_w(w,begin,size,grain);
    }
  };
}


#endif

#endif
