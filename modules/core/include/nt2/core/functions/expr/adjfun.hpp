//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ADJFUN_HPP_INCLUDED

#include <nt2/core/functions/adjfun.hpp>
#include <nt2/core/functions/common/adjfun.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename A1::extent_type                extt_t;
    typedef typename meta::strip<extt_t>::type       ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::adjfun_
                                          , container::domain
                                          , A1 const&
                                          , size_t
                                          , box<A0>
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& f, A1 const& a1) const
    {
      size_t along = nt2::firstnonsingleton(a1)-1; 
      ext_t sizee = nt2::extent(a1);
      if (sizee[along]) sizee[along]--;
      return boost::proto::make_expr<nt2::tag::adjfun_, container::domain>
        (boost::cref(a1),along, boxify(f), boxify(sizee));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)(ast_<A1>)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef typename A1::extent_type                   extt_t;
    typedef typename meta::strip<extt_t>::type          ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::adjfun_
                                          , container::domain
                                          , A1 const&
                                          , size_t
                                          , box<A0>
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& f,
                                             A1 const& a1,
                                             A2 const& alon) const
    {
      size_t along = alon-1;
      ext_t sizee = nt2::extent(a1);
      if (sizee[along]) sizee[along]--;
      return boost::proto::make_expr<nt2::tag::adjfun_, container::domain>
        (boost::cref(a1),along,boxify(f),boxify(sizee));
    }
  };

} } 

#endif
