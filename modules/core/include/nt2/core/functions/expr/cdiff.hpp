//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CDIFF_HPP_INCLUDED

#include <nt2/core/functions/cdiff.hpp>
#include <nt2/core/functions/common/cdiff.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // Generates  from a 2ary thing and 2 expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cdiff_, tag::cpu_,
                              (A0),
                              (ast_<A0>)
                            )
  {
    typedef typename A0::extent_type                extt_t;
    typedef typename meta::strip<extt_t>::type       ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cdiff_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      size_t along = nt2::firstnonsingleton(a0)-1; 
      ext_t sizee = nt2::extent(a0);
      sizee[along] =  (sizee[along] >= 2) ? sizee[along]-2 : 0;
      return boost::proto::make_expr<nt2::tag::cdiff_, container::domain>
        (boost::cref(a0),along,boxify(sizee));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cdiff_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::extent_type                       extt_t;
    typedef typename meta::strip<extt_t>::type              ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cdiff_
                                          , container::domain
                                          , A0 const&
                                          , size_t   
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1 ) const
    {
      ext_t sizee = nt2::extent(a0);
      size_t along =  a1-1; 
      sizee[along] =  (sizee[along] >= 2) ? sizee[along]-2 : 0;
      return boost::proto::make_expr<nt2::tag::cdiff_, container::domain>
        (boost::cref(a0),size_t(along),boxify(sizee));
    }
  };  
} } 

#endif
