/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUADGK_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUADGK_HPP_INCLUDED

#include <nt2/toolbox/integration/functions/quadgk.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/toolbox/integration/waypoints.hpp>
#include <nt2/toolbox/integration/fudge.hpp>
#include <nt2/toolbox/integration/order.hpp>
#include <nt2/toolbox/integration/split.hpp>
#include <nt2/toolbox/integration/midparea.hpp>
#include <nt2/toolbox/integration/transforms.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>


#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_not_finite.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/logical_not.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/table.hpp>

#include <boost/mpl/bool.hpp>


namespace nt2 { namespace details
{
  template<class T, class V> class quadgk_impl
  {
  public :
    typedef T                                              input_t;
    typedef typename meta::as_logical<input_t>::type          bi_t;
    typedef V                                              value_t;
    typedef typename meta::as_real<value_t>::type           real_t;
    typedef details::integration_settings<T, V, tag::quadgk_>  o_t;
    typedef container::table<value_t>                       vtab_t;
    typedef container::table<input_t>                       itab_t;
    typedef container::table<real_t>                        rtab_t;
    typedef container::table<bool>                          btab_t;
    typedef container::table<bi_t>                         bitab_t;
    typedef typename boost::is_same<input_t,real_t>::type   input_is_real_t;

    quadgk_impl() :  errbnd_(Nan<real_t>()),
                     fcnt_(0),
                     maxfcnt_(Valmax<size_t>()),
                     warn_(0),
                     res_(){}
    ~quadgk_impl() {}

    size_t nbeval()         const { return fcnt_;             }
    real_t lasterror()      const { return errbnd_;           }
    bool   ok()             const { return warn_ == 0;        }
    const vtab_t & result() const { return res_;              }
    void setwarn(size_t w)        { if(w > warn_) warn_ =  w; }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o,
                  const boost::mpl::false_ & choice) // cplx path integration
    {
      init(o, x,  choice);
      interval_ = tinterval_;
      vadapt(details::f0<FUNC, input_t, rtab_t, vtab_t>(f, a_, b_));
    }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o,
                  const boost::mpl::true_ & choice) // real interval integration
    {
      init(o, x, choice);
      if (a_ == b_) //quick return
      {
        res_ = details::midparea<value_t>(f, tinterval_(begin_), tinterval_(end_));
        errbnd_ = nt2::abs(res_);
        return;
      }
      adjust_and_call(f);
      if(reversedir_) res_ = -res_;
    }
  private :
    real_t      errbnd_;
    size_t        fcnt_;
    size_t     maxfcnt_;
    size_t  maxintvcnt_;
    size_t        warn_;
    real_t      abstol_;
    real_t      reltol_;
    vtab_t         res_;
    real_t        hmin_;
    bool    reversedir_;
    itab_t   tinterval_; //original points
    itab_t    interval_; //transformed points,  to reduce integration to a subinterval of [-1, 1]
    input_t      a_, b_;
    bool firstfunceval_;
    size_t          nb_;
    static const size_t minintervalcount_ = 10; // Minimum number subintervals to start.

//  Gauss-Kronrod (7,15) pair. Use symmetry in defining nodes and weights.
    static const itab_t& nodes()
    {
      static const input_t gk[7] = {
        input_t(0.2077849550078985), input_t(0.4058451513773972), input_t(0.5860872354676911),
        input_t(0.7415311855993944), input_t(0.8648644233597691), input_t(0.9491079123427585),
        input_t(0.9914553711208126)};
      static const itab_t k(of_size(7, 1), &gk[0], &gk[7]);
      static const itab_t k15 =  nt2::catv(nt2::catv(-flipud(k), nt2::Zero<input_t>()),k);
      return k15;
    }

    static const vtab_t& wt()
    {
      static const value_t pwt[7] = {
        value_t(0.2044329400752989), value_t(0.1903505780647854), value_t(0.1690047266392679),
        value_t(0.1406532597155259), value_t(0.1047900103222502), value_t(0.06309209262997855),
        value_t(0.02293532201052922) };
      static const vtab_t wt(of_size(1, 7), &pwt[0], &pwt[7]);
      static const vtab_t wt15 = nt2::cath(nt2::cath(fliplr(wt),value_t(0.2094821410847278)),wt);
      return wt15;
    }

    static const vtab_t& ewt()
    {
      static const value_t pwt7[7] = {
        value_t(0),value_t(0.3818300505051189),value_t(0),value_t(0.2797053914892767),
        value_t(0),value_t(0.1294849661688697),value_t(0)
      };
      static const vtab_t wt7(of_size(1, 7), &pwt7[0], &pwt7[7]);
      static const vtab_t ewt15 = wt()-nt2::cath(nt2::cath(fliplr(wt7),value_t(0.4179591836734694)),wt7);
      return ewt15;
    }

    template < class X >
    void init( const o_t & o, const X& x, const boost::mpl::false_ & )
    {
      details::prepare_waypoints(o, x, tinterval_);
      a_ = tinterval_(begin_);
      b_ = tinterval_(end_);
      abstol_ = o.abstol;
      reltol_ = o.reltol;
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = Valmax<size_t>();
      maxintvcnt_ = o.maxintvcnt;
      errbnd_ = nt2::Inf<real_t>();
    }

    template < class X >
    void init( const o_t & o, const X& x, const boost::mpl::true_ & )//real path integration
    {
      details::prepare_waypoints(o, x, tinterval_);
      reversedir_ = details::order_points(tinterval_, true);
      a_ = tinterval_(begin_);
      b_ = tinterval_(end_);
      abstol_ = o.abstol;
      reltol_ = o.reltol;
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = Valmax<size_t>();
      maxintvcnt_ = o.maxintvcnt;
      errbnd_ = nt2::Inf<real_t>();
      firstfunceval_ = true;
    }

    template < class FUNC >
    inline bool check(FUNC f, bool t, size_t w, const value_t& q)
    {
      if (t)
      {
//         std::cout << "q = " << q << std::endl << "  warn = " << w << std::endl;
//         std::cout << "fcnt_ = " << f.fcnt() << std::endl;
//         std::cout << "nb_   = " << nb_  << std::endl;
        fcnt_ = f.fcnt();
        res_ = q;
        setwarn(w);
      }
      return t;
    }

    template < class FUNC >
    void vadapt(FUNC f)
    {
//      std::cout << std::setprecision(15) << std::scientific << std::endl;
      real_t pathlen;
      itab_t tmp;
      details::split(interval_, minintervalcount_, tmp, pathlen);
      interval_ = tmp;
      if (pathlen == 0)
      {
        res_ = details::midparea<value_t>(f, interval_(begin_), interval_(end_));
        errbnd_ =  nt2::abs(res_);
        return;
      }
      // Initialize array of subintervals of [a,b].
      itab_t subs = nt2::catv(interval_(nt2::_(begin_, end_-1)),
                              interval_(nt2::_(begin_+1, end_)));
      // Initialize partial sums.
      value_t q_ok = nt2::Zero<value_t>();
      value_t err_ok = nt2::Zero<value_t>();
      // Initialize main loop
      nb_ = 0;
      while (true)
      {
        ++nb_;
        // subs contains subintervals of [a,b] where the integral is not
        // sufficiently accurate. The first row of SUBS holds the left end
        // points and the second row, the corresponding right endpoints.
        itab_t midpt = nt2::mean(subs);             // midpoints of the subintervals
        itab_t halfh = diff(subs)*Half<input_t>();  // half the lengths of the subintervals

        itab_t x = nt2::rowvect(nt2::sx(nt2::tag::plus_(),nt2::mtimes(nodes(), halfh),midpt));
        //        BOOST_AUTO_TPL(fx, f(x));
        vtab_t fx = f(x);
        // Quit if mesh points are too close.
        fx.resize(nt2::of_size(nt2::numel(wt()), numel(fx)/numel(wt())));
        // Quantities for subintervals.
        vtab_t qsubs = nt2::mtimes(wt(), fx)*halfh;
        vtab_t errsubs = nt2::mtimes(ewt(), fx)* halfh;
        // Calculate current values of q and tol.
        value_t q = nt2::globalsum(qsubs) + q_ok;
        if (check(f, f.tooclose(), 6, q)) break;
        real_t  tol = max(abstol_,reltol_*nt2::abs(q));
        // Locate subintervals where the approximate integrals are
        // sufficiently accurate and use them to update the partial
        // error sum.
        bitab_t ff= nt2::le(nt2::abs(errsubs), (Two<real_t>()*tol/pathlen)*nt2::abs(halfh));
        bitab_t notff = nt2::logical_not(ff);
        err_ok += nt2::globalsum(errsubs(ff));
        // Remove errsubs entries for subintervals with accurate
        // approximations.
        vtab_t errsubs1 = nt2::rowvect(errsubs(notff)); errsubs =  errsubs1; //ALIASING CAN BE AVOIDED PERHAPS
        // The approximate error bound is constructed by adding the
        // approximate error bounds for the subintervals with accurate
        // approximations to the 1-norm of the approximate error bounds
        // for the remaining subintervals.  This guards against
        // excessive cancellation of the errors of the remaining
        // subintervals.
        errbnd_ = nt2::abs(err_ok) + nt2::norm(errsubs,1);
        // Check for nonfinites.
        if (check(f, is_not_finite(q) && is_finite(errbnd_), 3, q)) break; // Infinite or Not-a-Number value encountered.
        if (check(f, errbnd_ <= tol, 0, q)) break;                         // tolerance reached: convergence
        //        if (check(f, f.fcnt() > maxfcnt_, 5, q)) break;          // Max evaluation number reached
        // Remove subintervals with accurate approximations.
        itab_t subs_tmp = subs(nt2::_, notff); subs = subs_tmp;
        if (check(f, nt2::isempty(subs), 0, q)) break;                     // All subs got required precision
        // Update the partial sum for the integral.
        q_ok +=  nt2::globalsum(qsubs(ff));
        // Split the remaining subintervals in half. Quit if splitting
        // results in too many subintervals.
        size_t nsubs = 2*nt2::size(subs,2);
        if (check(f, nsubs > maxintvcnt_, 2, q)) break;                    //Reached the limit on the maximum number of intervals in use.
        itab_t midpt1 = nt2::rowvect(midpt(notff)); midpt = midpt1;
        itab_t z = catv(catv(catv(subs(begin_,nt2::_),midpt),midpt),subs(end_,nt2::_));
        subs = reshape(z,2,numel(z)/2);
//         std::cout << " inbtrue(notff) " <<  nt2::inbtrue(notff)<< std::endl;
      }
    }

    template < class F >
    inline void adjust_and_call(const  F &f)
    {
      bool fina = nt2::is_finite(a_);
      bool finb = nt2::is_finite(b_);
      if(fina && finb)
      {
        if (nt2::numel(tinterval_) > 2)
        {
          // Analytical transformation suggested by K.L. Metlov:
          BOOST_AUTO_TPL(alpha, Two<real_t>()*nt2::sin(nt2::asin((a_+b_- Two<real_t>()*tinterval_(nt2::_(begin_+1, end_-1)))/(a_ - b_))/Three<real_t>() ));
          interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), alpha), nt2::One<input_t>());
        }
        else
        {
          interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::One<input_t>(), 2);
        }
//        NT2_DISPLAY("case f1");
        vadapt(details::f1<F, input_t, rtab_t, vtab_t>(f, a_, b_));
      }
      else
      {
        bool infb = nt2::is_inf(b_);
        if (fina && infb)
        {
          //          NT2_DISPLAY("case f2");
          if  (nt2::numel(tinterval_) > 2)
          {
            BOOST_AUTO_TPL(alpha, nt2::sqrt(tinterval_(2, end_-1) - a_));
            interval_ = nt2::cath(nt2::cath(nt2::Zero<input_t>(), alpha/oneplus(alpha)),nt2::One<input_t>());
          }
          else
            interval_ = nt2::linspace(nt2::Zero<input_t>(), nt2::One<input_t>(), 2);
          vadapt(details::f2<F, input_t, rtab_t, vtab_t>(f, a_));
        }
        else
        {
          bool infa = nt2::is_inf(a_);
          if (infa && finb)
          {
//            NT2_DISPLAY("case f3");
            if  (nt2::numel(tinterval_) > 2)
            {
              BOOST_AUTO_TPL(alpha, nt2::sqrt(b_-tinterval_(2, end_-1)));
              interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), -alpha/oneplus(alpha)),nt2::Zero<input_t>());
            }
            else
              interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::Zero<input_t>(), 2);
            vadapt(details::f3<F, input_t, rtab_t, vtab_t>(f, b_));
          }
          else if (infa && infb)
          {
//            NT2_DISPLAY("case f4");
            if  (nt2::numel(tinterval_) > 2)
            {
              BOOST_AUTO_TPL(alpha, nt2::tanh(nt2::asinh(Two<input_t>()*tinterval_(2, end_-1))*Half<input_t>()));
              interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), alpha), nt2::One<input_t>());
            }
            else
              interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::One<input_t>(), 2);
            vadapt(details::f4<F, input_t, rtab_t, vtab_t>(f));
          }
          else //is_nan(a) || is_nan(b)
          {
//            NT2_DISPLAY("case else");
            res_ = midparea<value_t>(f, a_, b_);
            errbnd_ = nt2::abs(res_);
            fcnt_ = 1;
          }
        }
      }
    }
  };
} }


namespace nt2 { namespace ext
                {
                  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::quadgk_, tag::cpu_
                                              , (F)(X)(O)
                                              , (unspecified_< F >)
                                              ((ast_<X, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename O::value_type                                   value_type;
    typedef typename O::input_type                                   input_type;
    typedef typename meta::as_real<value_type>::type                  real_type;
    typedef nt2::container::table<value_type>                            vtab_t;
    typedef nt2::integration::output<vtab_t,real_type>              result_type;
    typedef typename boost::is_same<input_type,real_type>::type input_is_real_t;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::quadgk_impl<input_type, value_type> q;
      q.compute(f, x, o, input_is_real_t());
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok()};
      return that;
    }
  };
} }
#endif
