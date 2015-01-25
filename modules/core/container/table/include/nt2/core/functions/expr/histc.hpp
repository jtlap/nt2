//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HISTC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HISTC_HPP_INCLUDED

#include <nt2/core/functions/histc.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/next.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/functions/tie.hpp>
#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/cons.hpp>

namespace nt2 { namespace ext
{

 BOOST_DISPATCH_IMPLEMENT  ( histc_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 value_type;
    typedef typename meta::as_integer<value_type, unsigned>::type ui_type;
    typedef container::table<ui_type> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& , A1 const & ) const
    {
      BOOST_ASSERT_MSG(false, "at least one bin is required");
      return result_type();
    }
  };
 BOOST_DISPATCH_IMPLEMENT  ( histc_, tag::cpu_
                           , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef A0 value_type;
    typedef typename meta::as_integer<value_type, unsigned>::type ui_type;
    typedef container::table<ui_type> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& , A1 const & , A2 const & ) const
    {
      BOOST_ASSERT_MSG(false, "at least one bin is required");
      return result_type();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( histc_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef A0 value_type;
    typedef typename meta::as_integer<value_type, unsigned>::type ui_type;
    typedef container::table<ui_type> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const & bins) const
    {
      ui_type n = numel(bins);
      BOOST_ASSERT_MSG(n >= 2, "at least one bin is required");
      result_type h = zeros(n, 1, meta::as_<ui_type>());
      table<value_type> b = cath(cath(Minf<value_type>(), rowvect(bins)), Inf<value_type>());
      for(ui_type i=1; i < ui_type(n) ; i++)
      {
        h(i) = touint(if_one_else_zero(logical_and(ge(x, b(i)), lt(x,  b(i+1)))));
        if (h(i)) return h;
      }
      h(n) = touint(if_one_else_zero(eq(x, bins(n))));
      return h;
    }
  };


  BOOST_DISPATCH_IMPLEMENT ( histc_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::histc_
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

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      BOOST_ASSERT_MSG(numel(boost::proto::child_c<1>(a0)) >= 2u, "at least one bin (two edges) is required");
      BOOST_ASSERT_MSG(issorted(boost::proto::child_c<1>(a0), true), "bins edges must be increasingly sorted");
      eval(a0, a1, N0(), N1());
    }
  private:
    /// INTERNAL ONLY - c = histc(x, bins)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      compute( boost::proto::child_c<0>(a1),
               boost::proto::child_c<0>(a0),
               boost::proto::child_c<1>(a0),
               nt2::firstnonsingleton(boost::proto::child_c<0>(a0)));
    }

    /// INTERNAL ONLY - c = histc(x, bins, dim)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
       compute(boost::proto::child_c<0>(a1),
               boost::proto::child_c<0>(a0),
               boost::proto::child_c<1>(a0),
               boost::proto::child_c<2>(a0));
    }

    /// INTERNAL ONLY - c = histc(x, bins)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      compute( boost::proto::child_c<0>(a1),
               boost::proto::child_c<1>(a1),
               boost::proto::child_c<0>(a0),
               boost::proto::child_c<1>(a0),
               nt2::firstnonsingleton(boost::proto::child_c<0>(a0)));

    }

    /// INTERNAL ONLY - c = histc(x, bins, dim)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      compute( boost::proto::child_c<0>(a1),
               boost::proto::child_c<1>(a1),
               boost::proto::child_c<0>(a0),
               boost::proto::child_c<1>(a0),
               boost::proto::child_c<2>(a0));
    }

    template <class H, class X, class B, class E>
    static BOOST_FORCEINLINE
    void compute (H& h,  const X& x, const B & bins, const E& dim)
    {
      typedef typename X::value_type value_type;
      typedef typename meta::as_integer<value_type, unsigned>::type ui_type;
      typedef container::table<ui_type> result_type;
      ui_type d = dim;
      auto sizee = x.extent();

      table<value_type> b = cath(cath(Minf<value_type>(), rowvect(bins)), Inf<value_type>());
      ui_type n = numel(b);
      sizee[dec(dim)] = n;
      h.resize(sizee);
      for(ui_type i=2; i < n ; ++i)
      {
        along(h, i, d) = inbtrue(logical_and(ge(x, b(i)), lt(x,  b(i+1))), d);
      }
//      along(h, n, d) = inbtrue(eq(x, bins(n)), d);
      h = along(h, _(2, n-1), dim);
    }

    template <class H, class P, class X, class B, class E>
    static BOOST_FORCEINLINE
    void compute (H& h,  P& p, const X& x, const B & bins, const E& dim)
    {
      typedef typename X::value_type value_type;
      typedef typename meta::as_integer<value_type, unsigned>::type ui_type;
      typedef container::table<ui_type> result_type;
      ui_type d = dim;
      auto sizee = x.extent();
      table<value_type> b = cath(cath(Minf<value_type>(), rowvect(bins)), Inf<value_type>());
      ui_type n = numel(b);
      p.resize(sizee);
      p(_) = cast<ui_type>(bsearch(rowvect(b), rowvect(x)));
      sizee[dec(dim)] = n-1;
      h.resize(sizee);
      for(ui_type i=2; i < n-1 ; ++i)
      {
        along(h, i, d) = inbtrue(eq(p, i), d);
      }
      h = along(h, _(2, n-2), dim);
      p =  minusone(p);
    }
  };


} }

#endif
