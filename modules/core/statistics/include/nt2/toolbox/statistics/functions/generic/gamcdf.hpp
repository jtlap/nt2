/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_GAMCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_GAMCDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/gamcdf.hpp>
#include <nt2/include/functions/gammainc.hpp>
#include <nt2/include/functions/dgammainc.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf0_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2){ return nt2::gammainc(a1, a0); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf0_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        return nt2::gammainc(a1, a0/a2);
      }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::gamcdf_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename boost::proto::result_of::child_c<A0&,2>::type          In2;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      doit(a0, a1, N0(), N1());
    }
    ////////////////////////////////////////////
    // No enough inputs to computes all ouputs
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<1> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<2> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");

    }
    ////////////////////////////////////////////
    // No enough output to computes all ouputs
    ////////////////////////////////////////////
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    ////////////////////////////////////////////
    // Regular cases
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      const nt2::container::table<value_type> pcov =  boost::proto::child_c<3>(a0);
      pcovis2x2positive(pcov);
      const value_type normz =  -nt2::norminv(static_cast<value_type>(0.025));
      conf_bounds(a0, a1, pcov, normz, boost::proto::child_c<0>(a1));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, boost::mpl::long_<3> const & )
    {
      const nt2::container::table<value_type> pcov =  boost::proto::child_c<3>(a0);
      pcovis2x2positive(pcov);
      const value_type normz =  -nt2::norminv(boost::proto::child_c<4>(a0));
      conf_bounds(a0, a1, pcov, normz, boost::proto::child_c<0>(a1));
    }

    template < class M2x2 >
    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const M2x2 pcov,
                                              const value_type& normz,
                                              Out0 & p)
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type         Out1;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type         Out2;

      //      NT2_DISPLAY(a0.extent());   NT2_DISPLAY(a1.extent());
      p.resize(a0.extent());
      const In0& x  = boost::proto::child_c<0>(a0);
      //      NT2_DISPLAY(x);
      const In1& a = boost::proto::child_c<1>(a0);
      //      NT2_DISPLAY(a);
      const In2& b = boost::proto::child_c<2>(a0);
      //       NT2_DISPLAY(b);
      BOOST_AUTO_TPL(z, x/b);
      //       NT2_DISPLAY(z);
      //       NT2_DISPLAY(nt2::gammainc(z, a));
      //       NT2_DISPLAY(size(p));
      p =  nt2::exp(z); //nt2::gammainc(z, a);
      //       NT2_DISPLAY(p);
      //      Out0& p = boost::proto::child_c<0>(a1);
      //      NT2_DISPLAY(p);
      BOOST_AUTO_TPL(itp, (p/nt2::oneminus(p)));
      //       NT2_DISPLAY(itp);
      BOOST_AUTO_TPL(dp, nt2::rec(p*oneminus(p))); // derivative of logit(p) w.r.t. p
      //       NT2_DISPLAY(dp);
      BOOST_AUTO_TPL(da, dgammainc(z,a)*dp);       // dlogitp/da = dp/da * dlogitp/dp
      //       NT2_DISPLAY(da);
      BOOST_AUTO_TPL(db, -nt2::exp(a*nt2::log(z)-z-nt2::gammaln(a)-nt2::log(b))* dp); // dlogitp/db = dp/db * dlogitp/dp
      //      NT2_DISPLAY(db);
      BOOST_AUTO_TPL(varLogitp, pcov(1,1)*sqr(da) + (Two<value_type>()*pcov(1,2)*da + pcov(2,2)*db)*db);
      //       NT2_DISPLAY(varLogitp);
      //       NT2_DISPLAY(normz);
      BOOST_AUTO_TPL(exp_halfwidth, nt2::exp(normz*nt2::sqrt(varLogitp)));
      //       NT2_DISPLAY(exp_halfwidth);
      Out1 & plo = boost::proto::child_c<1>(a1);
      Out2 & pup = boost::proto::child_c<2>(a1);
      plo.resize(a0.extent());
      pup.resize(a0.extent());
      //      std::cout << "1" << std::endl;
      plo = itp*exp_halfwidth;
      //      std::cout << "2" << std::endl;
      pup = itp/exp_halfwidth;
      //      std::cout << "3" << std::endl;
      plo /= nt2::oneplus(plo);
      //      std::cout << "4" << std::endl;
      pup /= nt2::oneplus(pup);
      //      std::cout << "5" << std::endl;
    }
  private :
    template < class T > BOOST_FORCEINLINE static
    void pcovis2x2positive(const T & pcov)
    {
      BOOST_ASSERT_MSG((size(pcov, 1) == 2) && (size(pcov, 2) == 2), "pcov must be of size 2x2");
      BOOST_ASSERT_MSG(is_gez(pcov(1, 1)), "pcov must be positive") ;
      BOOST_ASSERT_MSG(is_gez(pcov(1, 1)*pcov(2, 2)-sqr(pcov(1, 2))),
                       "pcov must be positive") ;
    }
// try
//     z = x ./ b;
//     p = gammainc(z, a);
// catch
//     error(message('stats:gamcdf:InputSizeMismatch'));
// end

// % Compute confidence bounds if requested.
// if nargout >= 2
//     % Approximate the variance of p on the logit scale
//     logitp = log(p./(1-p));
//     dp = 1 ./ (p.*(1-p)); % derivative of logit(p) w.r.t. p
//     da = dgammainc(z,a) .* dp; % dlogitp/da = dp/da * dlogitp/dp
//     db = -exp(a.*log(z)-z-gammaln(a)-log(b)) .* dp; % dlogitp/db = dp/db * dlogitp/dp
//     varLogitp = pcov(1,1).*da.^2 + 2.*pcov(1,2).*da.*db + pcov(2,2).*db.^2;
//     if any(varLogitp(:) < 0)
//         error(message('stats:gamcdf:BadCovariancePosSemiDef'));
//     end

//     % Use a normal approximation on the logit scale, then transform back to
//     % the original CDF scale
//     halfwidth = -norminv(alpha/2) * sqrt(varLogitp);
//     explogitplo = exp(logitp - halfwidth);
//     explogitpup = exp(logitp + halfwidth);
//     plo = explogitplo ./ (1 + explogitplo);
//     pup = explogitpup ./ (1 + explogitpup);
// end
  };

} }

#endif
