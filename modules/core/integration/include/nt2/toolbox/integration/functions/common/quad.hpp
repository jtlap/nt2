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
#include <nt2/include/constants/oneo_180.hpp>
#include <nt2/include/constants/c180.hpp>
#include <nt2/include/constants/fifteen.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>

namespace nt2 { namespace details
{
  template<class V> class quad_impl
  {
  public :
    typedef V                                             value_t;
    typedef typename meta::as_real<value_t>::type          real_t;
    typedef details::integration_settings<real_t, tag::quad_> o_t;
    typedef container::table<value_t>                       tab_t;
    typedef container::table<real_t>                       rtab_t;
    typedef container::table<bool>                         btab_t;

    quad_impl() :   err_(Nan<real_t>()),
                    fcnt_(0),
                    maxfcnt_(Valmax<size_t>()),
                    warn_(0),
                    ifault_(-1),
                    res_(){}
    ~quad_impl() {}

    size_t nbeval()        const { return fcnt_;                   }
    real_t lasterror()     const { return err_*Oneo_180<real_t>(); }
    bool   ok()            const { return warn_ == 0;              }
    const tab_t & result() const { return res_;                    }
    void setwarn(size_t w)       { if(w > warn_) warn_ =  w;       }
    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o)
    {
      init(o);
      real_t tmptol = tol_;
      tol_/= (x(end_)-x(begin_));
      BOOST_AUTO_TPL(dif, nt2::diff(nt2::rowvect(x)));
      //      BOOST_ASSERT_MSG(globalall(is_gez(dif)), "Using quad abscissae must be in increasing order");
      size_t l = numel(dif);
      res_.resize(extent(x));
      res_(1) = nt2::Zero<value_t>();
      tol_ = tmptol*dif(1);
      res_(2) = compute<true>(f, x(1), x(2));
      for(size_t i=2; i < l; ++i)
      {
        tol_ = tmptol*dif(i);
        res_(i+1) = res_(i)+compute<false>(f, x(i), x(i+1));
      }
      if (l >= 2)
      {
        tol_ = tmptol*dif(l);
        res_(l) = res_(l-1)+compute<true>(f, x(l-1), x(l));
      }

      tol_ = tmptol;
    }
   private :
    real_t         err_;
    size_t        fcnt_;
    size_t     maxfcnt_;
    bool    singular_a_;
    bool    singular_b_;
    size_t        warn_;
    ptrdiff_t   ifault_;
    real_t         tol_;
    tab_t          res_;
    real_t        hmin_;
    rtab_t        wpts_;
    void init( const o_t & o)
    {
//      o.display_options();
      tol_ = o.abstol*nt2::C180<real_t>();
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = o.maxfunccnt;
      ifault_ =  -1;
      err_ = nt2::Zero<real_t>();
      singular_a_ = o.singular_a;
      singular_b_ = o.singular_b;
    }

    template < class FUNC, int IND, bool test = true> struct fudge
    {
      void operator ()(const  FUNC & f, tab_t&y, size_t& fcnt, const bool & singular, const real_t& x, const real_t& shift)
      {
        size_t i =  IND;
        if ((singular) && nt2::is_invalid(y(i)))// Fudge to avoid infinities.
        {
          y(i) = f(x+shift); ++fcnt;
        }
      }
    };

    template < class FUNC, int IND> struct fudge < FUNC, IND, false>
    {
      void operator ()(const  FUNC &, tab_t&, size_t& , const bool &, const real_t&, const real_t&) {}
    };

    template <bool test, class FUNC>
    value_t compute(const  FUNC &f, const real_t& a, const real_t& b)
    {
      real_t d =  b-a;
      real_t e = nt2::eps(d);
      real_t s = e*sign(d);
      real_t h = real_t(0.13579)*d;
      real_t cx[] = {a, a+h, a+2*h, nt2::average(a, b), b-2*h, b-h, b};
      rtab_t x(nt2::of_size(1, 7), &cx[0], &cx[7]);
      tab_t y = f(x);
      fcnt_ = 7;
      fudge<FUNC,1,test>()(f, y, fcnt_, singular_a_, a,  s); // Fudge a to avoid infinities.
      fudge<FUNC,7,test>()(f, y, fcnt_, singular_b_, b, -s); // Fudge b to avoid infinities.
      // Call the recursive core integrator.
      hmin_ = nt2::fast_ldexp(e, -10); // e/1024
      return // estimate divided by 180
        (quadstep(f,x(1),x(3),y(1),y(2),y(3)) +
         quadstep(f,x(3),x(5),y(3),y(4),y(5)) +
         quadstep(f,x(5),x(7),y(5),y(6),y(7)))*nt2::Oneo_180<real_t>();
    }

    template < class FUNC >
    value_t quadstep(const FUNC & f, const real_t & a,  const real_t & b,
                                   const value_t &fa, const value_t &fc,const value_t& fb)
    {
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
      value_t q1 = (fa +nt2::Four<real_t>()*fc + fb)*nt2::Two<real_t>();  // float_three point Simpson's rule times 12
      value_t q02 = (fa+nt2::Four<real_t>()*fd+nt2::Two<real_t>()*fc+nt2::Four<real_t>()*fe+fb);  // Five point double Simpson's rule times 12
      value_t q2  = nt2::Fifteen<real_t>()*q02; //integral estimate times 180
      value_t q =h*(q2+(q02-q1)); // One step of Romberg extrapolation  times 180
      if (is_invalid(q))// Infinite or Not-a-Number function value encountered.
      {
        setwarn(3); return q;
      }
      // Check accuracy of integral over this subinterval.
      real_t curerr;
      if ((curerr = nt2::abs(h*q2 - q)) <= tol_*nt2::abs(h)) //tol has been multiplied by 180
      {
        err_+= curerr;
        return q;
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
     typedef nt2::container::table<value_type>                            tab_t;
     typedef nt2::integration::output<tab_t,real_type>              result_type;
//     typedef typename meta::as_logical<value_type>::type                 l_type;
//     typedef nt2::container::table<real_type>                            rtab_t;
//     typedef nt2::container::table<ptrdiff_t>                            ltab_t;
//     typedef details::integration_settings<real_type>                     otype;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::quad_impl<value_type> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok()};
//      o.display_options();
      return that;
    }
  };
} }
#endif
