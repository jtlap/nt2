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
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/functions/betainc.hpp>
#include <nt2/include/functions/caupdf.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/erfinv.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_ngtz.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/logical_not.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/nan.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/normpdf.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/is_policy.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

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
        computecorr(a0, a1, N0());
      }
    private:
      // one input parameter
      BOOST_FORCEINLINE
      void computecorr(A0 & a0, A1& a1, const boost::mpl::long_<1>&) const
      {
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        compute(a1, x, rtype_t(0.05), nt2::all_);
      }

      // two input parameters
      // can be x, y
      // x, options
      // x, alpha
      // reduce to xy, alpha, options
      BOOST_FORCEINLINE
      void computecorr(A0 & a0, A1& a1, const boost::mpl::long_<2>&) const
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename meta::is_policy<typename child1::value_type>::type is_option_t;
        dispatch_second(a0, a1, is_option_t());
      }

      // auxilliaries for two input parameters
      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::false_&) const  // corrcoef(x, y) or  corrcoef(x,  alpha)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename meta::is_scalar<typename boost::dispatch::meta::semantic_of <child1>::type>::type is_scalar_t;
        redispatch_second(a0, a1, is_scalar_t());
      }

      BOOST_FORCEINLINE
      void redispatch_second(A0 & a0, A1& a1
                              , const boost::mpl::false_&) const  // corrcoef(x, y)
      {

        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cath(x(_), y(_)), rtype_t(0.05), nt2::all_);
      }

      BOOST_FORCEINLINE
      void redispatch_second(A0 & a0, A1& a1
                              , const boost::mpl::true_&) const  // corrcoef(x, alpha)
      {

        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        rtype_t alpha = boost::proto::value(boost::proto::child_c<1>(a0));
        compute(a1, x, alpha, nt2::all_);
      }

      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::true_&) const // correl(x, option)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        compute(a1, x, rtype_t(0.05), policy());
      }
      //end  auxilliaries for two input parameters


      // thee input parameters
      // can be x, y,  options
      // x, options alpha
      // x, alpha options
      BOOST_FORCEINLINE
      void computecorr(A0 & a0, A1& a1
                        , const boost::mpl::long_<3>&) const
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename boost::proto::result_of::child_c<A0&,2>::value_type child2;
        typedef typename meta::is_policy<typename child1::value_type>::type is_option1_t;
        typedef typename meta::is_policy<typename child2::value_type>::type is_option2_t;
        typedef typename meta::is_scalar<typename boost::dispatch::meta::semantic_of <child1>::type>::type is_scalar1_t;
        typedef typename meta::is_scalar<typename boost::dispatch::meta::semantic_of <child2>::type>::type is_scalar2_t;
        dispatch_second(a0, a1
                       , is_option1_t(), is_option2_t()
                       , is_scalar1_t(), is_scalar2_t());
      }

      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::true_&
                            , const boost::mpl::false_&
                            , const boost::mpl::false_&
                            , const boost::mpl::true_&) const // correl(x, option, alpha)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        compute(a1, x
               , boost::proto::value(boost::proto::child_c<2>(a0))
               , boost::proto::value(boost::proto::child_c<1>(a0))
               );
      }

      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::false_&
                            , const boost::mpl::true_&
                            , const boost::mpl::true_&
                            , const boost::mpl::false_&) const // correl(x, alpha, option)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        compute(a1, x
               , boost::proto::value(boost::proto::child_c<1>(a0))
               , boost::proto::value(boost::proto::child_c<2>(a0))
               );
      }

      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::false_&
                            , const boost::mpl::true_&
                            , const boost::mpl::false_&
                            , const boost::mpl::false_&) const // correl(x, y, option)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cath(x(_), y(_))
               , rtype_t(0.05)
               , boost::proto::value(boost::proto::child_c<2>(a0))
               );
      }

      BOOST_FORCEINLINE
      void dispatch_second(A0 & a0, A1& a1
                            , const boost::mpl::false_&
                            , const boost::mpl::false_&
                            , const boost::mpl::false_&
                            , const boost::mpl::true_&) const // correl(x, y, alpha)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cath(x(_), y(_))
               , boost::proto::value(boost::proto::child_c<2>(a0))
               , nt2::policy<ext::all_>()
               );
      }
     //end  auxilliaries for three input parameters


      // Four input parameters
      // can be x, y, alpha, options
      // x, y, options, alpha
      BOOST_FORCEINLINE
      void computecorr(A0 & a0, A1& a1
                        , const boost::mpl::long_<4>&) const
      {
        typedef typename boost::proto::result_of::child_c<A0&,2>::value_type child2;
        typedef typename meta::is_policy<typename child2::value_type>::type is_option2_t;
        dispatch_third(a0, a1, is_option2_t());
      }

      BOOST_FORCEINLINE
      void dispatch_third(A0 & a0, A1& a1
                         , const boost::mpl::true_&
                         ) const // correl(x, y, option, alpha)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cath(x(_), y(_))
               , boost::proto::value(boost::proto::child_c<3>(a0))
               , boost::proto::value(boost::proto::child_c<2>(a0))
               );
      }
      BOOST_FORCEINLINE
      void dispatch_third(A0 & a0, A1& a1
                         , const boost::mpl::false_&
                         ) const // correl(x, y, option, alpha)
      {
        typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
        typedef typename child1::value_type policy;
        NT2_AS_TERMINAL_IN(o_semantic, x, boost::proto::child_c<0>(a0));
        NT2_AS_TERMINAL_IN(o_semantic, y, boost::proto::child_c<1>(a0));
        compute(a1, cath(x(_), y(_))
               , boost::proto::value(boost::proto::child_c<2>(a0))
               , boost::proto::value(boost::proto::child_c<3>(a0))
               );
      }
      //end  auxilliaries for four input parameters

      // correlation computation routines
      // option all_ : regular correlation on whole data
      template < class X> BOOST_FORCEINLINE
      void compute(const A1& a1, const X & x, rtype_t alpha
                  , nt2::policy<ext::all_> const &) const
      {
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        rtable_t c = cov(x);
        rtable_t sigma = sqrt(real(diag_of((c))));
        auto s = expand_to(sigma, c.extent());
        cc = (c/s)/ctrans(s);
        // Fix up possible round-off problems, while preserving NaN: put exact 1 on the
        // diagonal, and limit off-diag to [-1,1]
        auto absccgt1 = gt(nt2::abs(cc), One<rtype_t>());
        cc(absccgt1)/= abs(cc(absccgt1));
        cc(_(begin_, height(cc)+1,end_)) = sign(real(diag_of(cc)));
        boost::proto::child_c<0>(a1) = cc;
        rtable_t nn = height(x);
        compute_p(a1, nn, alpha, N1());
      }

      // option complete_ : exclude incomplete data rows (containing nans)
      template < class X> BOOST_FORCEINLINE
      void compute(const A1& a1, const X & x, rtype_t alpha
                  , nt2::policy<ext::complete_> const &) const
      {
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        rtable_t c = cov(x(none(is_nan(x), 2), _));
        rtable_t sigma = sqrt(real(diag_of((c))));
        auto s = expand_to(sigma, c.extent());
        cc = (c/s)/ctrans(s);
        // Fix up possible round-off problems, while preserving NaN: put exact 1 on the
        // diagonal, and limit off-diag to [-1,1]
        auto absccgt1 = gt(nt2::abs(cc), One<rtype_t>());
        cc(absccgt1)/= abs(cc(absccgt1));
        cc(_(begin_, height(cc)+1,end_)) = sign(real(diag_of(cc)));
        boost::proto::child_c<0>(a1) = cc;
        rtable_t nn = height(x);
        compute_p(a1, nn, alpha, N1());
      }

      // option pairwise_ : exclude data rows containing nans,  computing by row pairs
      template < class X> BOOST_FORCEINLINE
      void compute(const A1& a1, const X & x, rtype_t alpha
                  , nt2::policy<nt2::ext::pairwise_> const & ) const
      {
        // Compute correlation for each pair.
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        btable_t t = is_nan(x);
        std::size_t m = width(x);
        cc =  zeros(m, meta::as_<rtype_t>());
        rtable_t nn =  zeros(m, meta::as_<rtype_t>());
        for (std::size_t j = 1; j <= m; ++j)
        {
          for (std::size_t k = 1; k <= j; ++k)
          {
            btable_t tjk = none(t(_, cons<std::size_t>(j, k)), 2);
            nn(j, k) = globalsum(if_one_else_zero(tjk));
            if (nn(j, k))
            {
              if (j == k)
                cc(j, k) = One<type_t>();
              else
                cc(j, k) = corrcoef(x(tjk, cons<std::size_t>(of_size(1, 2), j, k)))(2);
            }
            else
            {
              cc(j, k) = Nan<rtype_t>();
            }
          }
        }
        cc+=ctrans(tril(cc, -1));
        nn+= ctrans(tril(nn, -1));
        boost::proto::child_c<0>(a1) = cc;
        compute_p(a1, nn, alpha, N1());
      }


      // p-numbers computation routines
      template <class NN> BOOST_FORCEINLINE
        void compute_p(A1 &, NN &, rtype_t
                      , const boost::mpl::long_<1> &) const
      {
        // do nothing
      }

      template <long N, class NN> BOOST_FORCEINLINE
        void compute_p(A1& a1, NN & nn, rtype_t alpha
                      , const boost::mpl::long_<N> &) const
      {
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        std::size_t m =  width(cc);
        if (numel(nn) == 1)
        {
          nn = repnum(nn(1), m, m);
        }
        // Tstat = +/-Inf and p = 0 if abs(r) == 1, NaN if r == NaN.
        rtable_t tstat = cc*sqrt((nn-Two<rtype_t>())/ (oneminus(sqr(cc))));
        rtable_t p = nan(of_size(m, m), meta::as_<rtype_t>());
        tpvalue(-nt2::abs(tstat), nn-Two<rtype_t>(), cc, p);
        assign_swap(boost::proto::child_c<1>(a1), p);
        compute_bounds(a1, nn, alpha, N1());
      }

      // bounds computation routines
      template < class NN> BOOST_FORCEINLINE
        void compute_bounds(A1&, NN &, rtype_t
                           , const boost::mpl::long_<1> &) const
      {
        // do nothing
      }
      template < class NN> BOOST_FORCEINLINE
        void compute_bounds(A1&, NN &, rtype_t
                           , const boost::mpl::long_<2> &) const
      {
        // do nothing
      }

      template <class NN> BOOST_FORCEINLINE
        void compute_bounds(A1& a1, NN & nn, rtype_t alpha
                           , boost::mpl::long_<3> const &) const
      {
        // Confidence bounds are degenerate if abs(r) = 1, NaN if r = NaN.
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        std::size_t m =  width(cc);
        auto z = atanh(cc);
        rtable_t  zalpha =  nan(of_size(m, m), meta::as_<rtype_t>());
        auto gt3 = gt(nn, Three<rtype_t>());
        zalpha(gt3) = (-erfinv(dec(alpha)))*Sqrt_2<rtype_t>()/ sqrt(nn(gt3)-Three<rtype_t>());
        rtable_t rlo = tanh(z-zalpha);
        rlo(_(1, long(width(nn))+1, end_)) = diag_of(cc);
        assign_swap(boost::proto::child_c<2>(a1), rlo);
      }

      template <class NN> BOOST_FORCEINLINE
        void compute_bounds(A1& a1, NN & nn, rtype_t alpha
                           , boost::mpl::long_<4> const &) const
      {
        // Confidence bounds are degenerate if abs(r) = 1, NaN if r = NaN.
        NT2_AS_TERMINAL_OUT(o_semantic, cc, boost::proto::child_c<0>(a1));
        std::size_t m =  width(cc);
        auto z = atanh(cc);
        rtable_t  zalpha =  nan(of_size(m, m), meta::as_<rtype_t>());
        auto gt3 = gt(nn, Three<rtype_t>());
        zalpha(gt3) = (-erfinv(dec(alpha)))*Sqrt_2<rtype_t>()/ sqrt(nn(gt3)-Three<rtype_t>());
        rtable_t rlo = tanh(z-zalpha);
        rtable_t rup = tanh(z+zalpha);
        rlo(_(1, long(width(nn))+1, end_)) = diag_of(cc);
        rup(_(1, long(width(nn))+1, end_)) = diag_of(cc);
        assign_swap(boost::proto::child_c<2>(a1), rlo);
        assign_swap(boost::proto::child_c<3>(a1), rup);
      }

      // tp values
      template < class X,  class V,class CC, class P>
        BOOST_FORCEINLINE void tpvalue(const X &x, const V & v, const CC& cc, P & p) const
      {
        // TPVALUE Compute p-value for t statistic.
        rtype_t normcutoff = rtype_t(1.0e7);
        auto nans = logical_or(is_nan(x), is_ngtz(v)); // v == NaN ==> is_nltz(v) == false
        //  First compute F(-|x|).
        //
        //  Cauchy distribution.  See Devroye pages 29 and 450.
        auto cauchy = eq(v, One<rtype_t>());
        p(cauchy) = caupdf(x(cauchy));
        //  Normal Approximation.
        auto normal = gt(v, normcutoff);
        p(normal) = normpdf(x(normal));

        //  See Abramowitz and Stegun, formulas 26.5.27 and 26.7.1.// to replace by student
        auto gen = logical_not(logical_or(logical_or(cauchy, normal), nans));
        p(gen) = betainc( v(gen)/(v(gen) + sqr(x(gen))),
                          v(gen)*Half<rtype_t>(),
                          Half<rtype_t>())*Half<rtype_t>();
        // Adjust for x>0.  Right now p<0.5, so this is numerically safe.
        auto reflect = logical_and(gen, is_gtz(x));
        p(reflect) = oneminus(p(reflect));
        // Make the result exact for the median.
        p(logical_andnot(is_eqz(x), nans)) = Half<rtype_t>();
        p*= Two<rtype_t>();
        p(_(1, long(width(x))+1, end_)) = diag_of(cc);
      }
    };
  }
}

#endif
