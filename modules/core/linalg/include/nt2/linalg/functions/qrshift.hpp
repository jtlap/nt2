//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QRSHIFT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QRSHIFT_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2
{
  namespace tag
  {
    struct qrshift_ :  ext::tieable_<qrshift_>
    {
      typedef ext::tieable_<qrshift_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_qrshift_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::qrshift_, Site> dispatching_qrshift_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::qrshift_, Site>();
    }
    template<class... Args>
    struct impl_qrshift_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::qrshift_, qrshift, 4)
  /*
   * tie(q1, r1) = qrshift(q,r,i,j)
   *
   * given a qr factorisation of a mxn marix a by mxk matrix q and a  kxn matrix q
   *       returns the qr-factorization of a(_, p) where the columns where shifted with
   * a permutation p of the columns.
   *
   * in matlab notations
   * if i < j then
   *  p is [1:i-1, i+1:j, i, j+1:end]
   * else if j > i
   *  p is [1:j-1, i j+1:i, i+1:end]
   * else
   *  p is identity
   *
   * @see @funcref{qr}, @funcref{qrdelete}, @funcref{qrupdate}, @funcref{qrinsert}
   */
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::qrshift_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::qrshift_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
