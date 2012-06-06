//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPHORZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPHORZ_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>


namespace nt2
{
  namespace tag
  {
    struct  rephorz_
          : ext::reshaping_<rephorz_> { typedef ext::reshaping_<rephorz_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::rephorz_, rephorz, 2) \
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct generator<nt2::tag::rephorz_,Domain,N,Expr> : generate_as<Expr,0> {};

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::rephorz_,Domain,N,Expr> : boxed_size_of<Expr,1> {};
} } }


#endif
