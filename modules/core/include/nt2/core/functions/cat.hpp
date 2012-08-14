//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct cat_ : ext::elementwise_<cat_>
    {
      typedef ext::elementwise_<cat_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cat_, cat, 3)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::cat_,Domain,4,Expr>
        : boxed_size_of<Expr,3>
  {};

  template<class Domain, class Expr>
  struct  value_type<nt2::tag::cat_,Domain,4,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c_t;
    typedef typename meta::scalar_of<c_t>::type                             s_t;
    typedef typename meta::strip<s_t>::type                                 type;
  };
} } }

#endif
