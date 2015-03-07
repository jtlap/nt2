//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_CORRCOEF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_CORRCOEF_HPP_INCLUDED

#include <nt2/linalg/functions/corrcoef.hpp>
#include <nt2/include/functions/corrcov.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //CORRCOEF Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( corrcoef_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&) const
    {
      return One<result_type>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( corrcoef_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& , const A1&) const
    {
      return One<result_type>();
    }
  };


  //============================================================================
  //CORRCOEF
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( corrcoef_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::corrcoef_
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
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                  type_t;
    typedef typename meta::as_real<type_t>::type                        rtype_t;
    typedef container::table<type_t>                                    table_t;
    typedef container::table<rtype_t>                                  rtable_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
     computecorr(a0, a1, N0(), N1());
    }
  private:
    BOOST_FORCEINLINE
    void computecorr(A0 & a0, A1& a1
                    , const boost::mpl::long_<1>&
                    , const boost::mpl::long_<1>&) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
      NT2_DISPLAY(x);
      NT2_DISPLAY(cov(x));
      compute(a1, cov(x));
    }
    BOOST_FORCEINLINE
    void computecorr(A0 & a0, A1& a1
                  , const boost::mpl::long_<2>&
                  , const boost::mpl::long_<1>&) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
      NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
      compute(a1, cov(x, y));
    }

    template < class C> BOOST_FORCEINLINE
    void compute(const A1& a1, const C & c) const
    {
      NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
      rtable_t sigma = sqrt(real(diag_of((c))));
      auto s = expand_to(sigma, c.extent());
      cc = (c/s)/ctrans(s);
      // Fix up possible round-off problems, while preserving NaN: put exact 1 on the
      // diagonal, and limit off-diag to [-1,1]
      auto absccgt1 = gt(nt2::abs(cc), One<rtype_t>());
      cc(absccgt1)/= abs(cc(absccgt1));
      cc(_(begin_, height(cc)+1,end_)) = sign(real(diag_of(cc)));
      boost::proto::child_c<0>(a1) = cc;
    }
  };
} }

#endif
