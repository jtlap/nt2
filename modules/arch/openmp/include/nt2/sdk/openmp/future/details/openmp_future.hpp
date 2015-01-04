//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_FUTURE_DETAILS_OPENMP_FUTURE_HPP_INCLUDED
#define NT2_SDK_OPENMP_FUTURE_DETAILS_OPENMP_FUTURE_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 201307 /* OpenMP 4.0 */

#include <omp.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

namespace nt2
{
  namespace tag
  {
    template<class T> struct openmp_;
  }

  namespace details
  {
    template<typename result_type>
    struct openmp_future
    {
      openmp_future() : res_(new result_type),ready_(new bool(false))
      {}

      template<typename previous_future>
      void attach_previous_future(previous_future const & pfuture)
      {
        pfutures_.push_back(
          std::shared_ptr<previous_future>(
            new previous_future(pfuture)
            )
          );
      }

      bool is_ready() const
      {
        return *ready_;
      }

      inline void wait()
      {
        #pragma omp taskwait
      }

      result_type get()
      {
        if(!is_ready())
        {
          wait();
        }

        return *res_;
      }

      template<typename F>
      openmp_future<typename std::result_of<F(openmp_future)>::type>
      then(F && f)
      {
        typedef typename std::result_of<F(openmp_future)>::type
        then_result_type;

        details::openmp_future<then_result_type> then_future;
        then_future.attach_previous_future(*this);

        F f_( std::forward<F> (f) );

        openmp_future current_future(*this);
        bool * prev( ready_.get() );

// Remove warning because the variable is used in the omp pragma
        boost::ignore_unused(prev);

        bool * next( then_future.ready_.get() );

        #pragma omp task \
        firstprivate(then_future,current_future,f_,prev,next) \
        depend(in: prev) \
        depend(out: next)
        {
          *(then_future.res_) = f_(current_future);
          *next = true;
        }

        return then_future;
      }

      std::vector< std::shared_ptr<void> > pfutures_;
      std::shared_ptr<result_type> res_;
      std::shared_ptr<bool> ready_;

    };
  }
}

#endif
#endif
