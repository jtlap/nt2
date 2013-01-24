//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_TRANSFORM_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/tbb/tbb.hpp>
#include <nt2/sdk/meta/display_type.hpp>
#include <cstddef>
#include <cstdio>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2 { namespace ext
{
  //============================================================================
  // Global tbb elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::tbb_<Site>
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
  // Partial tbb elementwise operation
  // Generates a SPMD loop nest and forward to internal site for evaluation
  // using the partial transform syntax.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, nt2::tag::tbb_<Site>
                            , (A0)(A1)(Site)(A2)(A3)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< integer_<A2> >)
                              (scalar_< integer_<A3> >)
                            )
  {
    typedef void                                            result_type;

    template<class A0_, class A1_,class A2_, class A3_>
    struct apply_transformer
    {
      apply_transformer( A0_& a0, A1_& a1, A2_ it, A3_ sz
                       , std::ptrdiff_t const& id)
      : a0_(a0), a1_(a1), it_(it), sz_(sz), id_(id)
      {
        // How many inner block to process & dispatch w/r to "thinness"
        local_size     = sz / tbb::task_scheduler_init::default_num_threads();
        local_leftover = sz % tbb::task_scheduler_init::default_num_threads();
      }

      void operator()()
      {
        // Move forward starts of each block
        std::ptrdiff_t offset = local_size*id_
                              + std::min(local_leftover,id_);

        // Adjust number of elements to process w/r to leftovers
        local_size += local_leftover ? ((local_leftover > id_) ? 1 : 0) : 0;
        // Call transform over the sub-architecture in the memory hierachy
        transformer(a0_,a1_,it_+offset,local_size);
      }

      nt2::functor<tag::transform_,Site> transformer;
      A0_& a0_;
      A1_& a1_;
      A2   it_;
      A3   sz_;
      std::ptrdiff_t id_;
      std::size_t    local_size;
      std::ptrdiff_t local_leftover;
    };

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, A2 it, A3 sz) const
    {
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
      try
      {
#endif
        tbb::task_group group;
        for(std::ptrdiff_t th = 0; th < tbb::task_scheduler_init::default_num_threads(); ++th)
        {
          group.run(apply_transformer<A0,A1,A2,A3>(a0,a1,it,sz,th));
        }
        group.wait();
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
#endif

#ifndef BOOST_NO_EXCEPTIONS
      if(exception) boost::rethrow_exception(exception);
#endif
    }
  };
} }

#endif
#endif
