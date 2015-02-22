//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QRUPDATE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QRUPDATE_HPP_INCLUDED

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
    struct qrupdate_ :  ext::tieable_<qrupdate_>
    {
      typedef ext::tieable_<qrupdate_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_qrupdate_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::qrupdate_, Site> dispatching_qrupdate_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::qrupdate_, Site>();
    }
    template<class... Args>
    struct impl_qrupdate_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::qrupdate_, qrupdate, 4)
  /*
   * tie(q1, r1) = qrupdate(q,r,u,v) returns the qr-factorization of a + u*ctrans(v),
   * where u and v are column vectors of appropriate lengths and q and r are a previously
   * computed qr-factorization of a
   *
   * @see @funcref{qr}, @funcref{qrdelete}, @funcref{qrshift}, @funcref{qrinsert}
   */
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::qrupdate_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::qrupdate_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
