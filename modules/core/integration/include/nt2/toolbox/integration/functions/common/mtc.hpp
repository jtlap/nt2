/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_MTC_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_MTC_HPP_INCLUDED

#include <nt2/toolbox/integration/functions/mtc.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/fifteen.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalprod.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/toolbox/integration/waypoints.hpp>
#include <nt2/toolbox/integration/fudge.hpp>

namespace nt2 { namespace details
{
  template<class T, class V> class mtc_impl
  {
  public :
    typedef T                                              input_t;
    typedef V                                              value_t;
    typedef typename meta::as_real<value_t>::type           real_t;
    typedef details::integration_settings<T, V, tag::mtc_>   o_t;
    typedef container::table<value_t>                       vtab_t;
    typedef container::table<input_t>                       itab_t;
    typedef container::table<real_t>                        rtab_t;
    typedef container::table<bool>                          btab_t;

    mtc_impl() :   err_(Nan<real_t>()),
                    fcnt_(0),
                    maxfcnt_(Valmax<size_t>()),
                    warn_(0),
                    ifault_(-1),
                    res_(){}
    ~mtc_impl() {}

    size_t nbeval()        const { return fcnt_;                   }
    real_t lasterror()     const { return err_;                    }
    bool   ok()            const { return warn_ == 0;              }
    const vtab_t & result()const { return res_;                    }
    void setwarn(size_t w)       { if(w > warn_) warn_ =  w;       }
    size_t  warn()         const { return warn_;                   }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & ranges, const o_t & o)
    {
      init(o); //, ranges);
      NT2_ASSERT_MSG(size(ranges, 2) == 2, "ranges must be a nx2 expression");
      res_ =  compute<true>(f, ranges);
//       real_t tmptol = tol_;
//       BOOST_AUTO_TPL(dif, nt2::abs(nt2::diff(nt2::rowvect(wpts_))));
//       real_t tol1= tol_/nt2::globalasum1(dif);
//       size_t l = numel(dif);
//       res_.resize(extent(wpts_));
//       res_(1) = nt2::Zero<value_t>();
//       tol_ = tol1*dif(1);
//       res_(2) = compute<true>(f, wpts_(1), wpts_(2));
//       for(size_t i=2; i < l; ++i)
//       {
//         tol_ = tol1*dif(i);
//         res_(i+1) = res_(i)+compute<false>(f, wpts_(i), wpts_(i+1));
//       }
//       if (l >= 2)
//       {
//         tol_ = tol1*dif(l);
//         res_(l+1) = res_(l)+compute<true>(f, wpts_(l), wpts_(l+1));
//       }

//       tol_ = tmptol;
//       if (!o.return_waypoints)
//       {
//         res_(begin_) = res_(end_);
//         res_.resize(nt2::of_size(1, 1));
//       }
//       NT2_DISPLAY(o.return_waypoints);
//       NT2_DISPLAY(res_);
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
    vtab_t         res_;
    real_t        hmin_;
    real_t      thresh_;
    itab_t        wpts_;
    size_t  maxintvcnt_;
    size_t       nbpts_;
  private:
    template < class X >
    void init( const o_t & o) //, const X&x)
    {
      //      o.display_options();
//      details::prepare_waypoints(o, x, wpts_);
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = o.maxfunccnt;
      tol_ = o.abstol;
      nbpts_ = 10000;
    }

    template <class FUNC, class X>
    value_t compute(const  FUNC &f, const X&ranges)
    {
      size_t n =  size(ranges, 1);
      BOOST_AUTO_TPL(fact, ranges(nt2::_,begin_+1)-ranges(nt2::_,begin_));
      input_t vol = nt2::globalprod(fact);
      BOOST_AUTO_TPL(z, f(nt2::expand_to(ranges(nt2::_, begin_), n, nbpts_))+ mul(rand(n, nbpts_), nt2::expand_to(fact, n, nbpts_)));
      res_ =  vol*globalMean(z);
      err_ =  vol*globalstdev(z)/nt2::sqrt(nbpts_);
    }
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtc_, tag::cpu_
                              , (F)(X)(O)
                              , (unspecified_< F >)
                              ((ast_<X, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename O::value_t                                             value_t;
    typedef typename O::input_t                                             input_t;
    typedef typename O::real_t                                               real_t;
    typedef typename O::result_t                                           result_t;
    typedef typename O::restab_t                                           restab_t;
    typedef typename boost::is_same<input_t,real_t>::type           input_is_real_t;
    typedef nt2::integration::output<restab_t,real_t>                   result_type;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::mtc_impl<input_t, value_t> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok(), q.warn()};
      //      NT2_DISPLAY(q.warn());
//      o.display_options();
      return that;
    }
  };
} }
#endif
