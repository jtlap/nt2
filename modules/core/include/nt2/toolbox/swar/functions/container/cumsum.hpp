//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTIONS_CONTAINER_CUMSUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTIONS_CONTAINER_CUMSUM_HPP_INCLUDED

#include <nt2/toolbox/swar/functions/cumsum.hpp>
#include <boost/simd/toolbox/swar/functions/cumsum.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::cumsum_,Domain,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
    typedef typename child0::extent_type result_type;

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct size_of<boost::simd::tag::cumsum_,Domain, N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
    typedef typename child0::extent_type result_type;

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct value_type<boost::simd::tag::cumsum_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr, 0>::value_type child0;
    typedef typename child0::value_type type;
  };
} } }

#endif
