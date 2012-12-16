/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUADL_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_QUADL_HPP_INCLUDED

#include <nt2/toolbox/integration/functions/quadl.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/sqrt_1o_5.hpp>
#include <nt2/include/constants/sqrt_2o_3.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>

namespace nt2 { namespace details
{
  template<class V> class quadl_impl
  {
  public :
    typedef V                                       value_t;
    typedef typename meta::as_real<value_t>::type    real_t;
    typedef real_t                                        T;
    typedef details::integration_settings<real_t>      o_t;
    typedef container::table<value_t>                 tab_t;
    typedef container::table<real_t>                 rtab_t;

    quadl_impl() :   err_(Nan<real_t>()),
                     fcnt_(0),
                     maxfcnt_(Valmax<size_t>()),
                     warn_(0),
                     res_(){}
    ~quadl_impl() {}

    size_t nbeval()        const { return fcnt_;             }
    real_t lasterror()     const { return err_/c1470_;       }
    bool   ok()            const { return warn_ == 0;        }
    const tab_t & result() const { return res_;              }
    void setwarn(size_t w)       { if(w > warn_) warn_ =  w; }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o)
    {
      init(o);
      real_t tmptol = tol_;
      BOOST_AUTO_TPL(dif, nt2::diff(nt2::rowvect(x))/(x(end_)-x(begin_)));
      //      BOOST_ASSERT_MSG(globalall(is_gez(dif)), "Using quadl abscissae must be in increasing order");
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
    real_t         tol_;
    tab_t          res_;
    real_t        hmin_;
    real_t        c245_;
    real_t       c1470_;
    static const rtab_t& lobatto()
    {
      static const T cl[] = {T(1),T(5),T(5),T(1)};
      static const rtab_t l(of_size(1, 4), &cl[0], &cl[4]);
      return l;
    }
    static const rtab_t& kronrod()
    {
      static const T ck[] = {T(77),T(432),T(625),T(672),T(625),T(432),T(77)};
      static const rtab_t k(of_size(1, 7), &ck[0], &ck[7]);
      return k;
    }
    void init( const o_t & o)
    {
      tol_ = o.absolute_tolerance;
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = Valmax<size_t>();
      err_ = nt2::Inf<real_t>();
      c245_ = 245;
      c1470_ = 1470; // 245*6
    }


    template < class FUNC >
    value_t compute(const  FUNC &f, const real_t& a, const real_t& b)
    {
      real_t e = eps(b-a);
      real_t c = nt2::average(a, b);
      real_t h = nt2::average(b, -a);
      const real_t cs[] = {T(.942882415695480), nt2::Sqrt_2o_3<T>(),
                           T(.641853342345781),
                           nt2::Sqrt_1o_5<T>(), T(.236383199662150)};
      rtab_t s(nt2::of_size(1, 5), &cs[0], &cs[5]);
      rtab_t x = nt2::cath(nt2::cath(nt2::cath(nt2::cath(a, c-h*s), c), c+h*nt2::fliplr(s)), b);
      tab_t  y = f(x);
      fcnt_ += 13;
      if (nt2::is_inf(y(1)))  { y(1)  = f(a+e); ++fcnt_; }     // Fudge endpoints to avoid infinities.
      if (nt2::is_inf(y(13))) { y(13) = f(b-e); ++fcnt_; }
      // Call the recursive core integrator.
      // Increase tolerance if refinement appears to be effective.
      value_t Q1 = h*nt2::dot(lobatto(),y(nt2::_(1,4,13)))*c245_;
      value_t Q2 = h*nt2::dot(kronrod(), y(nt2::_(1,2,13)));
      const real_t cs1[] = {T(.0158271919734802),T(.094273840218850),T(.155071987336585),
                            T(.188821573960182),T(.199773405226859),T(.224926465333340)};
      rtab_t s1(nt2::of_size(1, 6), &cs1[0], &cs1[6]);
      rtab_t w = cath(cath(s1, T(.242611071901408)), fliplr(s1));
      value_t Q0 = h*nt2::dot(w, y)*c1470_;
      real_t r = nt2::abs((Q2-Q0)/(Q1-Q0+nt2::Smallestposval<real_t>()));
      if (r > 0 && r < 1) tol_ /= r;
      tol_*= c1470_;
      // Call the recursive core integrator.
      hmin_ = fast_ldexp(e, -10); //e/1024
      return quadlstep(f, a,b,y(1),y(13))/c1470_;

    }

    template < class FUNC >
    value_t quadlstep(const FUNC & f, const real_t & a,  const real_t & b,
                      const value_t &fa, const value_t& fb)
    {
      //  recursive core routine for function quadl.
      // maxfcnt = 10000;

      //  Evaluate integrand five times in interior of subinterval [a,b].
      real_t c = nt2::average(a, b);
      real_t h = nt2::average(b, - a);
      if (abs(h) < hmin_ || c == a || c == b ) //Minimum step size reached; singularity possible.
      {
        setwarn(1); return h*(fa+fb);
      }
      real_t alpha = nt2::Sqrt_2o_3<T>();
      real_t beta = nt2::Sqrt_1o_5<T>();
      T cx[] = {-alpha, -beta, Zero<T>(), beta, alpha};
      rtab_t x(of_size(1, 5), &cx[0], &cx[5]);
      x = c+h*x;
      tab_t y = f(x);
      fcnt_ += 5;
      if (fcnt_ > maxfcnt_){ setwarn(2); return h*(fa+fb); }    // Maximum function count exceeded; singularity likely.
      rtab_t x1 = nt2::cath(nt2::cath(a, x), b); x = x1;
      tab_t y1 = nt2::cath(nt2::cath(fa, y), fb);y =  y1;
      value_t Q1 = h*nt2::dot(lobatto(), y(_(1, 2, 7)))*c245_; // Four point Lobatto quadrature times 1470.
      value_t Q = h*nt2::dot(kronrod(), y);                    // Seven point Kronrod refinement times 1470.
      if (nt2::is_invalid(Q)) { setwarn(3); return Q; }        // Infinite or Not-a-Number function value encountered.
      //  Check accuracy of integral over this subinterval.
      if ((err_ = nt2::abs(Q1 - Q)) <= tol_)
      {
        setwarn(0);  return Q;
      }
      else //     % Subdivide into six subintervals.
      {
        setwarn(0);
        Q = Zero<value_t>();
        for(size_t k = 1; k <= 6; ++k)
        {
          Q += quadlstep(f, x(k), x(k+1), y(k), y(k+1));
        }
      }
      return Q;
    };
  };
} }


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::quadl_, tag::cpu_
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
    typedef details::integration_settings<real_type>                    otype;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::quadl_impl<value_type> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok()};
      return that;
    }
  };
} }
#endif
