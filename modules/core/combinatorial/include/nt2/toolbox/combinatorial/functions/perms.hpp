/*******************************************************************************
 *         Copyright 2003-2013 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_perms perms
 *
 * \par Description
 *  m = permsn(v, k) returns the first k permutations
 * of the v elements in a table of size_t of size numel(v)Xk
 * If k is not provided k is numel(v)!
 *
 * Take care in this last case that numel(v) <= 10 to avoid exhausting memory
 * See also permsn
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag perms_ of functor perms
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct perms_ : ext::unspecified_<perms_> { typedef ext::unspecified_<perms_> parent; };
    }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::perms_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  nt2::numel(boost::proto::child_c<0>(e));
      size_t k =  boost::proto::child_c<1>(e);
      result_type sizee;
      sizee[1] = nt2::min(k, nt2::prod(nt2::_(size_t(1), n))); sizee[0] = n;
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::perms_, Domain,N,Expr>
    : meta::value_as<Expr,0>
  { };
} }

#endif
