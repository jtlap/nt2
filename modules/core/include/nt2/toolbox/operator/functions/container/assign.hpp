//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_ASSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_ASSIGN_HPP_INCLUDED

#include <nt2/toolbox/operator/functions/assign.hpp>
#include <nt2/core/container/dsl/generator.hpp>

namespace nt2 { namespace container { namespace ext
{
  // size is that of left-hand side
  template<class Domain, class Expr>
  struct size_of<tag::assign_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::
    child_c<Expr&, 0>::type                         child0;

    typedef typename size_transform<Domain>::template
    result<size_transform<Domain>(child0)>::type    result_type;

    BOOST_FORCEINLINE
    result_type operator()(Expr& e) const
    {
      return size_transform<Domain>()(boost::proto::child_c<0>(e));
    }
  };

} } }

#endif
