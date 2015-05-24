//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_EXPR_D2F_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_EXPR_D2F_HPP_INCLUDED

#include <nt2/derivation/functions/d2f.hpp>
#include <nt2/include/functions/depth.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/whereijk.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/derivation/options.hpp>
#include <nt2/derivation/details/choosediags.hpp>
#include <nt2/derivation/details/compute_h.hpp>
#include <nt2/derivation/details/get_epsi.hpp>
#include <nt2/core/container/colon/colon.hpp>


namespace nt2 { namespace ext
{
 BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::d2f_, N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                   result_type;
    typedef typename A0::value_type                    type_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef typename boost::proto::result_of::child_c<A1&, N::value-1>::value_type vtype_t;
    typedef typename meta::is_scalar< vtype_t>::type choice_t;

    result_type operator()(A0& out, const A1& in ) const
    {
      auto x0 = boost::proto::child_c<1>(in);
      auto f =  boost::proto::value(boost::proto::child_c<0>(in));
      std::size_t nbcoefs = height(x0); // number of coefficients in an input vector
      std::size_t nbvec = width(x0);    // number of f input vectors
      auto x =  reshape(x0, nbcoefs, 1, nbvec);
      rtype_t epsi =  details::get<A1, rtype_t>::epsi(in, Derivinc2<rtype_t>(), N());
      auto h = details::compute<rtype_t>::h(x, epsi, N(), choice_t());
      auto hh = expand_to(h, nbcoefs, nbcoefs,  nbvec);
      auto dx = whereijk(details::choosediags(), hh, Zero<rtype_t>());
      auto xxp =  sx(nt2::tag::plus_(),x, dx);
      auto xxm =  sx(nt2::tag::minus_(),x, dx);
      out = sx(nt2::tag::divides_()
                 , sx(nt2::tag::fma_()
                     , reshape(f(x),  _(), 1, nbvec)
                     , Mtwo<rtype_t>()
                     , sx(nt2::tag::plus_()
                         , reshape(f(xxp), _(), nbcoefs, nbvec)
                         , reshape(f(xxm), _(), nbcoefs, nbvec)
                         )
                     )
              , reshape(sqr(h), 1, height(h), depth(h)));
      return out;
    }
  };


} }

#endif
