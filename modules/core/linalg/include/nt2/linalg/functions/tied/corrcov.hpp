//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_CORRCOV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_CORRCOV_HPP_INCLUDED

#include <nt2/linalg/functions/corrcov.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/ispositive.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //CORRCOV Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( corrcov_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      BOOST_ASSERT_MSG(real(a0) >= 0, "invalid covariance matrix");
      return sign(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( corrcov_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return sign(a0);
    }
  };


  //============================================================================
  //CORRCOV
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( corrcov_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::corrcov_
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
    typedef typename meta::as_integer<rtype_t>::type                    itype_t;
    typedef container::table<type_t>                                    table_t;
    typedef container::table<rtype_t>                                  rtable_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>   r_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, c, boost::proto::child_c<0>(a0));
      NT2_DISPLAY("corrcov");
      NT2_DISPLAY(c);
      BOOST_ASSERT_MSG(testcov(c, N0()), "invalid covariance matrix");
      computecorr(a1, c, N1());
    }
  private:
    template < class C > BOOST_FORCEINLINE
    bool testcov(const C& c,  const boost::mpl::long_<1>&) const
    {
      return ispositive(c);
    }
    template < class C > BOOST_FORCEINLINE
    bool testcov(const C&,  const boost::mpl::long_<2>&) const
    {
      return true;
    }
    template < class C> BOOST_FORCEINLINE
    void computecorr(const A1& a1, const C & c, const N1&) const
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
      setsigma(a1, sigma, N1());
    }

    template < class S> BOOST_FORCEINLINE
    void setsigma(const A1&, const S &,const  boost::mpl::long_<1>&) const
    {
      //do nothing
    }
     template < class S> BOOST_FORCEINLINE
    void setsigma(const A1& a1, const S & sigma,const  boost::mpl::long_<2>&) const
    {
      boost::proto::child_c<1>(a1) = sigma;
    }

  };
} }

#endif
