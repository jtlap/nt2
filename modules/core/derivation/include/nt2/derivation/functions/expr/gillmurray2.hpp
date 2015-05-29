//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_EXPR_GILLMURRAY2_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_EXPR_GILLMURRAY2_HPP_INCLUDED

#include <nt2/derivation/functions/gillmurray2.hpp>
#include <nt2/include/functions/depth.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/whereijk.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/derivincgm.hpp>
#include <nt2/derivation/options.hpp>
#include <nt2/derivation/details/choosediags.hpp>
#include <nt2/derivation/details/compute_h.hpp>
#include <nt2/derivation/details/get_epsi.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/table.hpp>
namespace nt2 { namespace ext
{
 BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::gillmurray2_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                                      result_type;
    typedef typename A0::value_type                                       type_t;
    typedef typename meta::as_real<type_t>::type                         rtype_t;
    typedef typename boost::proto::result_of::child_c<A1&, N::value-1>::value_type vtype_t;
    typedef typename meta::is_scalar<vtype_t>::type                   semantic_t;
    typedef typename meta::is_scalar< semantic_t>::type                 choice_t;

    result_type operator()(A0& out, const A1& in ) const
    {
      auto x0 = boost::proto::child_c<1>(in);
      auto f =  boost::proto::value(boost::proto::child_c<0>(in));
      std::size_t nbcoefs = height(x0); // number of coefficients in an input vector
      std::size_t nbvec = width(x0);    // number of f input vectors
      auto x00 =  reshape(x0, nbcoefs, 1, 1, nbvec);
      auto x  =  expand_to(x00, nbcoefs, nbcoefs, nbcoefs, nbvec);
      NT2_DISPLAY(x);
      rtype_t epsi =  details::get<A1, rtype_t>::epsi(in, Derivincgm<rtype_t>(), N());
      NT2_DISPLAY(epsi);
      auto h0 = details::compute<rtype_t>::h(x0, epsi, N(), choice_t());
      NT2_DISPLAY(h0);
      h00 =  reshape(h0, nbcoefs, 1, 1, nbvec);
      auto hh = expand_to(h00, nbcoefs, nbcoefs, nbvec);
      NT2_DISPLAY(hh);
      h000 =  reshape(h0, nbcoefs, 1, 1, 1, nbvec);
      auto hhh = expand_to(h000, nbcoefs, nbcoefs, nbcoefs, nbvec);
      NT2_DISPLAY(hhh);
//       auto dx = whereij(details::choosediag(), hh, Zero<rtype_t>());
// //      NT2_DISPLAY(dx);
//       auto dx0 = whereijk(details::chooserows(), hhh, Zero<rtype_t>());
// //      NT2_DISPLAY(dx0);
//       auto dx1 = repmat(dx, 1, 1, nbcoefs);
// //      NT2_DISPLAY(dx1);
//       auto xxi  =  sx(nt2::tag::plus_(), x, dx0);
// //      NT2_DISPLAY(xxi);
//       auto xxj  =  sx(nt2::tag::plus_(), x, dx1);
// //      NT2_DISPLAY(xxj);
//       auto xxij =  sx(nt2::tag::plus_(), xxi, dx);
// //      NT2_DISPLAY(xxij);
//       table<type_t> fh1h2  = reshape(f(xxij), nbcoefs, nbcoefs);
// //      NT2_DISPLAY(fh1h2);
//       table<type_t> fh1    = reshape(f(xxi), nbcoefs, nbcoefs);
// //      NT2_DISPLAY(fh1);
//       table<type_t> fh2    = reshape(f(xxj), nbcoefs, nbcoefs);
// //      NT2_DISPLAY(fh2);
//       type_t fx    = f(x0);
// //      NT2_DISPLAY(fx);
//       auto hihj =  sx(tag::multiplies_(), h0, rowvect(h0));
//       out = sx(nt2::tag::divides_(), (sx(nt2::tag::plus_(), fh1h2-fh1-fh2, fx)), hihj);

//      NT2_DISPLAY(out);
      return out;
    }
  };


} }

#endif
