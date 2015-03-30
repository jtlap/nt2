//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_SPAWNER_SCAN_HPP_INCLUDED
#define NT2_SDK_HPX_SPAWNER_SCAN_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <hpx/include/lcos.hpp>
#include <hpx/include/util.hpp>

#include <nt2/sdk/shared_memory/spawner.hpp>

#include <boost/assert.hpp>

#include <vector>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  namespace tag
  {
    struct scan_;
    template<class T> struct hpx_;
  }

  namespace details
  {
    template<class Worker, class result_type>
    struct Hpx_Scaner
    {
        typedef typename hpx::lcos::future<result_type> Future;
        typedef typename hpx::util::tuple< Future , Future  > Two_Futures;
        typedef typename std::vector< hpx::lcos::future<result_type> > FutureVector;

        Hpx_Scaner(Worker & w, FutureVector & barrier, std::size_t begin = 0, std::size_t size = 0 )
        :w_(w),barrier_(barrier),begin_(begin),size_(size)
        {}

        Future operator()(std::size_t end, std::size_t size, std::size_t grain)
        {
           result_type summary = w_.neutral_(nt2::meta::as_<result_type>());

           if (size == grain)
           {
             return hpx::make_ready_future( w_(summary,end-size,size,false) );
           }

           std::size_t middle = end - grain;

           hpx::lcos::future<result_type> other_out
             = hpx::async(w_,summary,middle,grain,true);

           hpx::lcos::future<result_type> my_out
             = (*this)(middle, size - grain, grain);

           return hpx::when_all(my_out,other_out).then( Hpx_Scaner(w_,barrier_,middle,grain) );
        };

        template < typename T >
        result_type operator()(T deps) const
        {
            Two_Futures two_results = deps.get();
            result_type result1 = ( hpx::util::get<0>(two_results) ).get();
            result_type result2 = ( hpx::util::get<1>(two_results) ).get();

            barrier_.push_back( hpx::async(w_, result1, begin_, size_, false) );

            return w_.bop_(result1,result2);
        }

        Worker & w_;
        std::vector< hpx::lcos::future<result_type> > & barrier_;
        std::size_t begin_;
        std::size_t size_;

    private:
        Hpx_Scaner& operator=(Hpx_Scaner const&);

    };
  }

  template<class Site, class result_type>
  struct spawner< tag::scan_, tag::hpx_<Site> , result_type>
  {
    typedef typename std::vector< hpx::lcos::future<result_type> > FutureVector;

    spawner() {}

    template<typename Worker>
    result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {
      BOOST_ASSERT_MSG( size % grain == 0, "Scan size not divisible by grain");

      FutureVector barrier;
      barrier.reserve(size/grain);

      details::Hpx_Scaner<Worker,result_type> hpx_w (w, barrier);

      std::size_t end = begin + size;
      result_type result = hpx_w(end,size,grain).get();

      hpx::wait_all(barrier);

      return result;
    }
  };
}


#endif

#endif
