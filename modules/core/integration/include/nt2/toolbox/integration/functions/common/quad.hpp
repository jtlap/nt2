/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUAD_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUAD_HPP_INCLUDED

#include <nt2/toolbox/integration/functions/quad.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/optimization/options.hpp>

namespace nt2 { namespace details
{
  template<class V> class quad_impl
  {
  public :
    typedef V                                       value_t;
    typedef typename meta::as_real<value_t>::type    real_t;
    typedef details::optimization_settings<real_t>      o_t;
    typedef container::table<value_t>                 tab_t;
    typedef container::table<real_t>                 rtab_t;

    quad_impl() :   err_(Nan<real_t>()),
                    fcnt_(0),
                    maxfcnt_(Valmax<size_t>()),
                    warn_(0),
                    ifault_(-1),
                    res_(){}
    ~quad_impl() {}

    size_t nbeval()        const { return fcnt_;       }
    real_t lasterror()     const { return err_;        }
    bool   ok()            const { return warn_ == 0;  }
    const tab_t & result() const { return res_;        }
    void setwarn(size_t w)       { if(w > warn_) warn_ =  w; }
    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o)
    {
      init(o);
      real_t tmptol = tol_;
      BOOST_AUTO_TPL(dif, nt2::diff(nt2::rowvect(x))/(x(end_)-x(begin_)));
      //      BOOST_ASSERT_MSG(globalall(is_gez(dif)), "Using quad abscissae must be in increasing order");
      size_t l = numel(dif);
      res_.resize(extent(x));
      res_(1) = nt2::Zero<value_t>();
      for(size_t i=1; i <= l; ++i)
      {
        tol_ = tmptol*dif(i);
        res_(i+1) = res_(i)+compute(f, x(i), x(i+1));
      }
      tol_ = tmptol;
    }
   private :
    real_t         err_;
    size_t        fcnt_;
    size_t     maxfcnt_;
    size_t        warn_;
    ptrdiff_t   ifault_;
    real_t         tol_;
    tab_t          res_;
    real_t        hmin_;

    void init( const o_t & o)
    {
      tol_ = o.absolute_tolerance;
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = Valmax<size_t>();
      ifault_ =  -1;
      err_ = nt2::Inf<real_t>();
    }


    template < class FUNC >
    value_t compute(const  FUNC &f, const real_t& a, const real_t& b)
    {
      real_t d =  b-a;
      real_t e = nt2::eps(d);
      real_t h = real_t(0.13579)*d;
      real_t cx[] = {a, a+h, a+2*h, nt2::average(a, b), b-2*h, b-h, b};
      rtab_t x(nt2::of_size(1, 7), &cx[0], &cx[7]); //= nt2::cons(a, a+h, a+2*h, (a+b)*0.5, b-2*h, b-h, b);
      tab_t y = f(x);
      fcnt_ += 7;

      // Fudge endpoints to avoid infinities.
      if (nt2::is_inf(y(1)))
      {
        //            y(0) = f(cref(a+eps<float_t>()*(b-a)));
        y(0) = f(a+e);
        fcnt_++;
      }
      if (nt2::is_inf(y(7)))
      {
        y(6) = f(b-e);
        fcnt_++;
      }
      // Call the recursive core integrator.
      hmin_ = nt2::fast_ldexp(e, -10); // e/1024
      return
        quadstep(f,x(1),x(3),y(1),y(2),y(3)) +
        quadstep(f,x(3),x(5),y(3),y(4),y(5)) +
        quadstep(f,x(5),x(7),y(5),y(6),y(7));
    }

    template < class FUNC >
    value_t quadstep(const FUNC & f, const real_t & a,  const real_t & b,
                                   const value_t &fa, const value_t &fc,const value_t& fb)
    {
//    static const real_t Half =         real_t(0.5);
      static const real_t UnSurSix =     real_t(1.0/6.0);
      static const real_t UnSurDouze  =  real_t(1.0/12.0);
      static const real_t UnSurQuinze =  real_t(1.0/15.0);
//     static const real_t Deux =         real_t(2.0);
//     static const real_t Quatre =       real_t(4.0);
      // Evaluate integrand twice in interior of subinterval [a,b].
      real_t h = b-a;
      real_t c = nt2::average(a, b);
      if (nt2::abs(h) < hmin_ || c == a || c == b)
      {
        // Minimum step size reached; singularity possible.
        setwarn(1);
        return h*fc;
      }
      const value_t fd = f(nt2::average(a, c));
      const value_t fe = f(nt2::average(c, b));
      fcnt_ += 2;
      if (fcnt_ > maxfcnt_)
      {
        // Maximum function count exceeded; singularity likely.
        setwarn(2);
        return h*fc;
      }
      // float_three point Simpson's rule.
      value_t Q1 = (fa + Four<real_t>()*fc + fb)*UnSurSix;

      // Five point double Simpson's rule.
      value_t Q2 = (fa+Four<real_t>()*fd+Two<real_t>()*fc+Four<real_t>()*fe+fb)*UnSurDouze;

      // One step of Romberg extrapolation.
      value_t Q = h*(Q2+(Q2-Q1)*UnSurQuinze);

      if (is_invalid(Q))
      {
        // Infinite or Not-a-Number function value encountered.
        setwarn(3);
        return Q;
      }
      // Check accuracy of integral over this subinterval.
      err_ = nt2::abs(h*Q2 - Q);
      if (err_ <= tol_)
      {
        return Q;
      }
      else// Subdivide into two subintervals.
      {
        return  quadstep(f,a,c,fa,fd,fc)+quadstep(f,c,b,fc,fe,fb);
      }
    }

  };

} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::quad_, tag::cpu_
                              , (F)(X)(O)
                              , (unspecified_< F >)
                              ((ast_<X, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename X::value_type                                  value_type;
    typedef typename meta::as_real<value_type>::type                 real_type;
    typedef typename meta::as_logical<value_type>::type                 l_type;
    typedef nt2::container::table<value_type>                            tab_t;
    typedef nt2::container::table<real_type>                            rtab_t;
    typedef nt2::container::table<ptrdiff_t>                            ltab_t;
    typedef nt2::integration::output<tab_t,real_type>              result_type;
    typedef details::optimization_settings<real_type>                    otype;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::quad_impl<value_type> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok()};
      return that;
    }
  };
} }
#endif
