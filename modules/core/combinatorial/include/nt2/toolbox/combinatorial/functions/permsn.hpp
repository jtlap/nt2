//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PERMSN_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PERMSN_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_permsn permsn
 *
 * \par Description
 * m = permsn(n, k) returns the first k permutations
 * of _(1, n) in a table<size_t> of size nXk
 * If k is not provided k is n!
 *
 * Take care in this last case that n <= 10 to avoid exhausting memory
 * See also perms
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag permsn_ of functor permsn
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct permsn_ : ext::unspecified_<permsn_> { typedef ext::unspecified_<permsn_> parent; };
    }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permsn_, permsn, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permsn_, permsn, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::permsn_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  boost::proto::child_c<0>(e);
      size_t k =  boost::proto::child_c<1>(e);
      result_type sizee;
      sizee[1] = nt2::min(k, nt2::prod(nt2::_(size_t(1), n))); sizee[0] = n;
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::permsn_, Domain,N,Expr>
  {
    typedef size_t type;
  };

} }

#endif
