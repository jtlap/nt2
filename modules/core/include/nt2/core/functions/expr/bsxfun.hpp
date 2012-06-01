//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/core/functions/common/bsxfun.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
//#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // Generates  from a 2ary thing and 2 expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (ast_<A1>)
                              (ast_<A2>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , box<A0>      
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      of_size_max s1 = size(a1);
      of_size_max s2 = size(a2);
      of_size_max sizee ;
      for(int i = 0; i < sizee.size(); ++i)
        {
          sizee[i] = 1; 
          if (s1[i] == 1) sizee[i] = s2[i];
          if (s2[i] == 1) sizee[i] = s1[i];
        }
      return boost::proto::make_expr<nt2::tag::bsxfun_, container::domain>
        (boost::cref(a1),boost::cref(a2),boxify(a0),boxify(sizee));
    }
  };
  
} } 

#endif
