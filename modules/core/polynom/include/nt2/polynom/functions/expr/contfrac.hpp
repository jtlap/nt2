//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_CONTFRAC_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_CONTFRAC_HPP_INCLUDED

#include <nt2/polynom/functions/contfrac.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/fam.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/options.hpp>

#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/table.hpp>
namespace nt2
{ namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( contfrac_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_<floating_<A0> > )
                                (scalar_<floating_<A1> > )
                              )
    {
      typedef A0   base_t;

      BOOST_DISPATCH_RETURNS( 2
                            , (const A0& a0, const A1 &a1)
                            , a0/base_t(a1)
                            );
    };
    BOOST_DISPATCH_IMPLEMENT  ( contfrac_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (scalar_<floating_<A0> > )
                                (scalar_<floating_<A1> > )
                                (scalar_<floating_<A2> > )
                              )
    {
      typedef A2   base_t;

      BOOST_DISPATCH_RETURNS( 3
                            , (const A0& a0, const A1 &a1, const A2 &a2)
                            , (base_t(a0)+a2)/base_t(a1)
                            );
    };

    BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::contfrac_, N,nt2::container::domain> ))
                              )
    {
      typedef typename A0::value_type                                        type_t;
      typedef container::table<type_t>                                        tab_t;
      typedef A0&                                                       result_type;
      typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>      o_semantic;

      result_type operator()(A0& out, const A1& in) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, a, boost::proto::child_c<0>(in));
        NT2_AS_TERMINAL_IN(o_semantic, b, boost::proto::child_c<1>(in));
        compute(a, b, in, out, N());
        return out;
      }
    private:
      template <class A,  class B>
      BOOST_FORCEINLINE void
      compute( A & f, B& g, const A1&, A0& out, const boost::mpl::long_<2> &) const
      {
        out.resize(of_size(1, 1));
        type_t r1, r2;
        r1 =  g(1)/f(1);
        type_t u = Zero<type_t>();
        type_t v = rec(f(1));
        for (std::size_t k = 2; k <= numel(f); ++k)
        {
          u = rec(fam(g(k), f(k), u));
          r2 = fam(g(k)*r1, f(k), v) * u;
          v = r1 * u;
          r1 = r2;
        }
        out = rec(r1);
      }

      template <class A,  class B>
      BOOST_FORCEINLINE void
      compute( A & f, B& g, const A1& in, A0& out, const boost::mpl::long_<3> &) const
      {
        compute( f, g, in, out, nt2::lower_);
      }

      template <class A,  class B>
      BOOST_FORCEINLINE void
      compute( A & f, B& g, const A1& in, A0& out, const boost::mpl::long_<4> &) const
      {
        compute(f, g, in, out, boost::proto::value(boost::proto::child_c<3>(in)) );
      }

      template <class A,  class B>
      BOOST_FORCEINLINE void
        compute( A & f, B& g, const A1& in, A0& out, const nt2::policy<nt2::ext::lower_> &) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<2>(in));
        out.resize(x.extent());
        tab_t r2(x.extent());
        tab_t r1 =  (g(1)+x)/f(1);
        tab_t u = zeros(x.extent(), meta::as_<type_t>());
        tab_t v = repnum(rec(f(1)), x.extent());
        for (std::size_t k = 2; k <= numel(f); ++k)
        {
          u = rec(fma(f(k), u, g(k)+x));
          r2 =fma((g(k)+x), r1, f(k)*v)*u;
          v = r1 * u;
          nt2::swap(r1, r2);
        }
        out = rec(r1);
      }


      template <class A,  class B>
      BOOST_FORCEINLINE void
        compute( A & f, B& g, const A1& in, A0& out, const nt2::policy<nt2::ext::both_> &) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<2>(in));
        out.resize(x.extent());
        tab_t r2(x.extent());
        tab_t r1 =  (g(1)+x)/(f(1)+x);
        tab_t u = zeros(x.extent(), meta::as_<type_t>());
        tab_t v = rec(f(1)+x);
        for (std::size_t k = 2; k <= numel(f); ++k)
        {
          u = rec(fma((f(k)+x), u, g(k)+x));
          r2 =fma((g(k)+x), r1, (f(k)+x)*v)*u;
          v = r1 * u;
          nt2::swap(r1, r2);
        }
        out = rec(r1);
      }

      template <class A,  class B>
      BOOST_FORCEINLINE void
        compute( A & f, B& g, const A1& in, A0& out, const nt2::policy<nt2::ext::upper_> &) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<2>(in));
        out.resize(x.extent());
        tab_t r2(x.extent());
        tab_t r1 =  g(1)/(f(1)+x);
        tab_t u = zeros(x.extent(), meta::as_<type_t>());
        tab_t v = rec(f(1)+x);
        for (std::size_t k = 2; k <= numel(f); ++k)
        {
          u = rec(fma((f(k)+x), u, g(k)));
          r2 =fma(g(k), r1, (f(k)+x)*v)*u;
          v = r1 * u;
          nt2::swap(r1, r2);
        }
        out = rec(r1);
      }


    };
  }
}

#endif
