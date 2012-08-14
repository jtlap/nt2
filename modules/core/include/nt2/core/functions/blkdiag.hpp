//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct  blkdiag_ : ext::elementwise_<blkdiag_>
    {
      typedef ext::elementwise_<blkdiag_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 2)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::blkdiag_,Domain,3,Expr>
        : boxed_size_of<Expr,2>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::blkdiag_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::value_type type;
  };
} } }

#endif
