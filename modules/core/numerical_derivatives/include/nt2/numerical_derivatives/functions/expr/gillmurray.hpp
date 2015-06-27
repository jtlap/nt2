//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_EXPR_GILLMURRAY_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_EXPR_GILLMURRAY_HPP_INCLUDED

#include <nt2/numerical_derivatives/functions/gillmurray.hpp>
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
#include <nt2/numerical_derivatives/options.hpp>
#include <nt2/numerical_derivatives/details/choosediags.hpp>
#include <nt2/numerical_derivatives/details/compute_h.hpp>
#include <nt2/numerical_derivatives/details/get_epsi.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/table.hpp>
namespace nt2 { namespace ext
{
 BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::gillmurray_, N
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
      out.resize(of_size(nbcoefs, nbcoefs, nbvec));
      for(std::size_t k = 1; k <= nbvec;  ++k)
      {
        auto x0k = x0(_, k);
        auto x  =  expand_to(x0k, nbcoefs, nbcoefs, nbcoefs);
        rtype_t epsi =  details::get<A1, rtype_t>::epsi(in, Derivincgm<rtype_t>(), N());
        auto h0 = details::compute<rtype_t>::h(x0k, epsi, N(), choice_t());
        auto hh = expand_to(h0, nbcoefs, nbcoefs);
        auto hhh = expand_to(h0, nbcoefs, nbcoefs, nbcoefs);
        auto dx = whereij(details::choosediag(), hh, Zero<rtype_t>());
        auto dx0 = whereijk(details::chooserows(), hhh, Zero<rtype_t>());
        auto dx1 = repmat(dx, 1, 1, nbcoefs);
        auto xxi  =  sx(nt2::tag::plus_(), x, dx0);
        auto xxj  =  sx(nt2::tag::plus_(), x, dx1);
        auto xxij =  sx(nt2::tag::plus_(), xxi, dx);
        //why auto cannot be put there ?
        table<type_t> fh1h2  = reshape(f(xxij), nbcoefs, nbcoefs);
        table<type_t> fh1    = reshape(f(xxi), nbcoefs, nbcoefs);
        table<type_t> fh2    = reshape(f(xxj), nbcoefs, nbcoefs);
        type_t fx    = f(x0k);
        auto hihj =  sx(tag::multiplies_(), h0, rowvect(h0));
        out(_, _, k)= sx(nt2::tag::divides_(), (sx(nt2::tag::plus_(), fh1h2-fh1-fh2, fx)), hihj);
      }

      return out;
    }
  };


} }

#endif
