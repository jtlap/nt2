//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_FUNCTIONS_TABLE_AD_DF_HPP_INCLUDED
#define NT2_AD_FUNCTIONS_TABLE_AD_DF_HPP_INCLUDED


#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/core/functions/tie.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/ad/functions/ad.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //AD_GRADIENT Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( ad_gradient_, tag::cpu_
                            , (F)(X)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x) const
    {
      ad::valder<result_type> r =  f(ad::valder<X>(x));
      return r.der();

    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( ad_gradient_, tag::cpu_
                            , (F)(X)(EPSI)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >) //dummy
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x, const EPSI&) const
    {
      return ad_gradient(f, x);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( ad_gradient_, tag::cpu_
                            , (F)(X)(EPSI)(OPT)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (scalar_<floating_<EPSI> >) //dummy
                              (unspecified_<OPT>) //dummy
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) result_type;

    BOOST_FORCEINLINE
    result_type operator()(F f, const X& x, const EPSI&, const OPT&) const
    {
      return ad_gradient(f, x);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( ad_gradient_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::ad_gradient_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type      F;
    typedef typename boost::proto::result_of::child_c<A0&,1>::value_type      X;
    typedef typename X::value_type                                       elem_t;
    typedef typename nt2::container::table<elem_t>                        tab_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      auto x =  boost::proto::child_c<1>(a0);
      std::size_t nbcoefs= height(x); // number of coefficients in an input vector
      std::size_t nbvec = width(x);  // number of f input vectors
      auto xx = expand_to(reshape(x, nbcoefs, 1, nbvec), nbcoefs, nbcoefs, nbvec);
      auto dd = expand_to(eye(nbcoefs, nbcoefs, meta::as_<elem_t>()), nbcoefs, nbcoefs, nbvec);
      auto z = nt2::ad::valder<tab_t>(xx, dd);
      auto f = boost::proto::value(boost::proto::child_c<0>(a0));
      auto r = f(z);
      affect(a1, r, nbcoefs, nbvec, N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - d = ad_gradient(f, x)
    template<class R>
    BOOST_FORCEINLINE
    void affect ( A1& a1,  R & r
                , std::size_t h
                , std::size_t w
                , boost::mpl::long_<1> const&
                ) const
    {
      boost::proto::child_c<0>(a1) = reshape(r.der(), h, w);
    }

    //==========================================================================
    /// INTERNAL ONLY - tie(v, d) = ad_gradient(f, x)
    template<class R,  long N>
    BOOST_FORCEINLINE
    void affect ( A1& a1,  R & r
                , std::size_t h
                , std::size_t w
                , boost::mpl::long_<N> const&
                ) const
    {
      boost::proto::child_c<0>(a1) = r.val()(_(1u, h, end_));
      boost::proto::child_c<1>(a1) = reshape(r.der(), h, w);
    }
  };
} }

#endif
