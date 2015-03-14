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
#include <nt2/include/functions/abs.hpp>
//#include <nt2/include/functions/betainc.hpp>
#include <nt2/include/functions/caupdf.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/corrcov.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/logical_not.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/nanmean.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/normpdf.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/meta/is_policy.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/table.hpp>

namespace nt2
{
  namespace ext
  {
    struct all_       : boost::mpl::true_  {};
    struct complete_  : boost::mpl::true_  {};
    struct pairwise_  : boost::mpl::true_  {};
  }

  nt2::policy<ext::all_>         const all_;
  nt2::policy<ext::complete_>    const complete_;
  nt2::policy<ext::pairwise_>    const pairwise_;
}

namespace nt2 {
  namespace ext {
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
      typedef typename meta::as_logical<rtype_t>::type                    btype_t;
      typedef container::table<type_t>                                    table_t;
      typedef container::table<btype_t>                                  btable_t;
      typedef container::table<rtype_t>                                  rtable_t;
      typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;

      BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
      {
        computecorr(a0, a1, N0(), N1());
      }
    private:
      template < long N > BOOST_FORCEINLINE
        void computecorr(A0 & a0, A1& a1
                        , const boost::mpl::long_<1>&
                        , const boost::mpl::long_<N>&) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        compute(a1, cov(x));
        rtable_t nn = width(x);
        compute_accessory(a1, nn, boost::mpl::long_<N>());
      }

      template < class D> BOOST_FORCEINLINE
        void compute_accessory(A1 &, const D &, const boost::mpl::long_<1> &) const
      {
      }

      template < class D> BOOST_FORCEINLINE
        void compute_accessory(A1& a1, const D & nn, const boost::mpl::long_<2> &) const
      {
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        // Operate on half of symmetric matrix.abs
        std::size_t m =  width(cc);
        auto lowerhalf = (tril(is_gtz(ones(m, meta::as_<rtype_t>()),-1)));
        auto   rv = cc(lowerhalf);
        auto   nv = nn(lowerhalf);
        // Tstat = +/-Inf and p = 0 if abs(r) == 1, NaN if r == NaN.
        auto tstat = rv* sqrt((nv-Two<rtype_t>())/ (oneminus(sqr(rv))));
        rtable_t p = Nan(m, meta::as_<rtype_t>());
        p(lowerhalf) = Two<rtype_t>(); //*tpvalue(-nt2::abs(tstat),nv-Two<rtype_t>(), p);
        p += ctrans(p) + diag_of(_from_diag(cc)); // Preserve NaNs on diag.
        assign_swap(boost::proto::child_c<1>(a1), p);
      }


      BOOST_FORCEINLINE
        void computecorr(A0 & a0, A1& a1
                        , const boost::mpl::long_<2>&
                        , const boost::mpl::long_<1>&) const
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename meta::is_policy<typename child1::value_type>::type is_option_t;
        dispatch_second(a0, a1, is_option_t(), N1());
      }

      BOOST_FORCEINLINE
        void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::false_&  // correl(x, y)
                            , const boost::mpl::long_<1>&) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cov(x, y));
      }

      BOOST_FORCEINLINE
        void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::true_& // correl(x, option)
                            , const boost::mpl::long_<1>&) const
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        container::table<rtype_t> nn;
        compute(a1, x, nn, policy());
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

      template < class X, class NN> BOOST_FORCEINLINE
        void compute(const A1& a1, const X & x, NN&
                    , const policy<nt2::ext::all_> & ) const
      {
        compute(a1, cov(x));
      }

      template < class X, class NN> BOOST_FORCEINLINE
        void compute(const A1& a1, const X & x, NN&
                    , const policy<nt2::ext::complete_> & ) const
      {
        // Remove observations with missing values.
        compute(a1, cov(x(none(is_nan(x), 2), _)));
      }
      template < class X, class NN> BOOST_FORCEINLINE
        void compute(const A1& a1, const X & x,  NN & nn
                    , const policy<nt2::ext::pairwise_> & ) const
      {
        //Compute correlation for each pair.
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        btable_t t = is_nan(x);
        std::size_t m = width(x);
        cc =  zeros(m, meta::as_<rtype_t>());
        nn =  zeros(m, meta::as_<rtype_t>());
        table_t nmean = nanmean(x, 1);

        for (std::size_t j = 1; j <= m; ++j)
        {
          for (std::size_t k = 1; k <= j; ++k)
          {
            btable_t tjk = none(t(_, cons<std::size_t>(j, k)), 2);
            nn(j, k) = globalsum(if_one_else_zero(tjk));
            if (nn(j, k))
            {
              if (j == k)
              {
                cc(j, k) = One<type_t>();
              }
              else
              {
                cc(j, k) = corrcoef(x(tjk, cons<std::size_t>(of_size(1, 2), j, k)))(2);
              }
            }

            else
            {
              cc(j, k) = Nan<rtype_t>();
            }
          }
        }
        cc+=ctrans(tril(cc, -1));
        nn+= ctrans(tril(nn, -1));
    //     table_t cc1 =  cc+ctrans(tril(cc, -1));
//         table_t nn1 =  nn+ctrans(tril(nn, -1));
//         cc = cc1;
//         nn =  nn1;
        boost::proto::child_c<0>(a1) = cc;
      }

      template < class X,  class V, class P>
        BOOST_FORCEINLINE void tpvalue(const X &x, const V & v, P & p)
      {
        // TPVALUE Compute p-value for t statistic.

        rtype_t normcutoff = rtype_t(1.0e7);
        //        if length(x)~=1 && length(v)==1
        //    v = repmat(v,size(x));
        // end

        auto nans = logical_or(is_nan(x), is_nltz(v)); // v == NaN ==> is_nltz(v) == false

        //  First compute F(-|x|).
        //
        //  Cauchy distribution.  See Devroye pages 29 and 450.
        auto cauchy = eq(v, One<rtype_t>());
        p(cauchy) = cauchypdf(x(cauchy));
        // p(cauchy) = .5 + atan(x(cauchy))/pi;

        //  Normal Approximation.
        auto normal = gt(v, normcutoff);
        p(normal) = normpdf(x(normal));

        //  See Abramowitz and Stegun, formulas 26.5.27 and 26.7.1.// to replace by student
        auto gen = logical_not(logical_or(logical_or(cauchy, normal), nans));
        p(gen) = Zero<rtype_t>(); // betainc(v(gen)/(v(gen) + sqr(x(gen)), v(gen)*Half<rtype_t>(), Half<rtype_t>()))*Half<rtype_t>();

        // Adjust for x>0.  Right now p<0.5, so this is numerically safe.
        auto reflect = logical_and(gen, is_gtz(x));
        p(reflect) = oneminus(p(reflect));

        // Make the result exact for the median.
        p(logical_andnot(is_eqz(x), nans)) = Half<rtype_t>();

      }
    };
  }
}

#endif
