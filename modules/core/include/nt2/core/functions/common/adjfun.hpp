//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ADJFUN_HPP_INCLUDED

#include <nt2/core/functions/adjfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::adjfun_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef boost::proto::result_of::child_c<A0&, 0>                  child0_t;
    typedef typename  boost::dispatch::meta::
                      call< nt2::tag::run_( typename child0_t::type
                                          , State const&
                                          , Data const&
                                          )
                          >::type                                     value_t;
    typedef typename  boost::proto::result_of::
                      child_c<A0&, 2>::value_type::value_type         func_t;

    typedef typename  boost::dispatch::meta::
                      result_of<func_t(value_t,value_t)>::type      result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Types for indices computation
      typedef typename child0_t::value_type::extent_type                ext_t;
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename meta::call<nt2::tag::ind2sub_(ext_t,i_t)>::type  sub_t;

      // Compute position and shifted position
      sub_t pos0 = ind2sub(a0.extent(),enumerate<i_t>(p));

      sub_t pos1 = pos0;
      ++pos1[boost::proto::child_c<1>(a0)];

      // Run the functor on shifted data and original data
      return boost::proto::value(boost::proto::child_c<2>(a0))
            ( nt2::run( boost::proto::child_c<0>(a0)
                      , sub2ind(boost::proto::child_c<0>(a0).extent(), pos1)
                      , t
                      )
            , nt2::run( boost::proto::child_c<0>(a0)
                      , sub2ind(boost::proto::child_c<0>(a0).extent(), pos0)
                      , t
                      )
            );
    }
  };
} }

#endif
