//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GALLERY_QMULT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GALLERY_QMULT_HPP_INCLUDED
#include <nt2/linalg/functions/qmult.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2
{

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qmult0_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      BOOST_DISPATCH_RETURNS(2, (A0 const& n, T const & t),
                             (nt2::qmult(nt2::eye(n, n, T())))
                            )
    };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::qmult_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(a, boost::proto::child_c<0>(in));
      size_t n = nt2::size(a, 1);
      nt2::table<value_t> q(nt2::of_size(n, n)), r(nt2::of_size(n, n));
      nt2::tie(q, r) = nt2::qr(nt2::randn(n, n, nt2::meta::as_<value_t>()));
      out = nt2::mtimes(nt2::mtimes(q,nt2::from_diag(nt2::sign(nt2::diag_of(r)))), a);
      return out;
    }
  };

}

  meta::call<tag::qmult0_(const ptrdiff_t &, meta::as_<double> const &)>::type
  qmult(ptrdiff_t n)
  {
    return nt2::qmult(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::qmult0_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  qmult(ptrdiff_t n)
  {
    return nt2::qmult(n,  meta::as_<T>());
  }

}


#endif
