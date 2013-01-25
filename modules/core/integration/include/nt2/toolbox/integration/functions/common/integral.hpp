/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_INTEGRAL_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_COMMON_INTEGRAL_HPP_INCLUDED

#include <nt2/toolbox/integration/functions/integral.hpp>
#include <nt2/toolbox/integration/output.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/toolbox/integration/waypoints.hpp>
#include <nt2/toolbox/integration/fudge.hpp>
#include <nt2/toolbox/integration/order.hpp>
#include <nt2/toolbox/integration/split.hpp>
#include <nt2/toolbox/integration/midparea.hpp>
#include <nt2/toolbox/integration/int_transforms.hpp>

#include <nt2/include/constants/half.hpp>
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
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

#include <boost/mpl/bool.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace details
{
  template<class T, class V> class integral_impl
  {
  public :
    typedef T                                                                input_t;
    typedef typename meta::as_logical<input_t>::type                            bi_t;
    typedef V                                                                value_t;
    typedef typename meta::is_complex<value_t>::type                     v_is_cplx_t;
    typedef typename boost::mpl::if_<v_is_cplx_t,value_t,input_t>::type     result_t;
    typedef typename meta::as_real<value_t>::type                             real_t;
    typedef details::integration_settings<T, V, tag::integral_>                    o_t;
    typedef container::table<value_t>                                         vtab_t;
    typedef container::table<input_t>                                         itab_t;
    typedef container::table<real_t>                                          rtab_t;
    typedef container::table<result_t>                                      restab_t;
    typedef container::table<bi_t>                                           bitab_t;

    integral_impl() :  errbnd_(Nan<real_t>()),
                     fcnt_(0),
                     maxfcnt_(Valmax<size_t>()),
                     warn_(0),
                     res_(){}
    ~integral_impl() {}

    size_t nbeval()           const { return fcnt_;             }
    real_t lasterror()        const { return errbnd_;           }
    bool   ok()               const { return warn_ == 0;        }
    const restab_t & result() const { return res_;              }
    void setwarn(size_t w)          { if(w > warn_) warn_ =  w; }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o,
                  const boost::mpl::false_ & choice) // cplx path integration
    {
      init(o, x,  choice);
      interval_ = tinterval_;
      vadapt(transform<FUNC, details::no_transform, input_t, value_t>(f, a_, b_, interval_));
    }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o,
                  const boost::mpl::true_ & choice) // real interval integration
    {
      init(o, x, choice);
      if (a_ == b_) //quick return
      {
        result_t r = nt2::multiplies(f(a_), Zero<input_t>());
          //result_t r = details::midparea<result_t, value_t>(f, tinterval_(begin_), tinterval_(end_));
        res_ = r;
        errbnd_ = nt2::abs(r);
        return;
      }
      interval_ = tinterval_;
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
    restab_t       res_;
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
      array_valued_ =  o.array_valued; 
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
    inline bool check(FUNC f, bool t, size_t w, const result_t& q)
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
      NT2_DISPLAY("vadapt");
//      std::cout << std::setprecision(15) << std::scientific << std::endl;
      real_t pathlen;
      itab_t tmp;
      NT2_DISPLAY(interval_);
      NT2_DISPLAY(f.interval_);
      details::split(f.interval_, minintervalcount_, tmp, pathlen);
      NT2_DISPLAY(tmp);
      interval_ = tmp;
      if (pathlen == 0)
      {
        input_t tmp =  nt2::multiplies(f.interval_(end_), nt2::Half<real_t>());
        input_t xx =  nt2::fma(f.interval_(begin_), nt2::Half<real_t>(), tmp);
        input_t d = (f.interval_(end_)-f.interval_(begin_));

        result_t r = nt2::multiplies(f(xx), d); //details::midparea<result_t, value_t>(f, f.interval_(begin_), f.interval_(end_));
        res_ = r;
        errbnd_ =  nt2::abs(r);
        return;
      }
      // set maxintvcnt_ high enough that each initial subinterval
      // can be refined at least once.
      maxintvcnt_ = nt2::max(maxintvcnt_,2*(nt2::numel(interval_)-1));
      if (array_valued_)
        iterate_array_valued(f);
      else
        iterate_scalar_valued(f);
    }

    template < class FUNC >
    void iterate_scalar_valued(FUNC f)
    {
      firstfuneval = true;
         // Initialize array of subintervals of [a,b].
      // Initialize array of subintervals of [a,b].
      itab_t subs = nt2::catv(interval_(nt2::_(begin_, end_-1)),
                              interval_(nt2::_(begin_+1, end_)));
      // Initialize partial sums.
      result_t q_ok = nt2::Zero<result_t>();
      result_t err_ok = nt2::Zero<result_t>();
      // Initialize main loop
      nb_ = 0;

      size_t   nsubs = size(subs,2);
      // Initialize main loop
      while (true)
      {
        ++nb_; 
        //  subs contains subintervals of [a,b] where the integral is not
        //  sufficiently accurate. the first row of subs holds the left
        //  end points and the second row, the corresponding right
        //  endpoints.
        itab_t midpt = nt2::mean(subs);             // midpoints of the subintervals
        itab_t halfh = diff(subs)*Half<input_t>();  // half the lengths of the subintervals
        itab_t x = nt2::rowvect(nt2::sx(nt2::tag::plus_(),nt2::mtimes(nodes(), halfh),midpt));
 
        if (firstfuneval)
        {
          vtab_t fx = f(x(nt2::_, 1));
          
//                 % Unwrap the first function evaluation to get size and
//                 % class information.
//                 [t,w] = u(x(:,1));
//                 fxj = FUN(t(1)).*w(1);
//                 nfx = numel(fxj);
//                 outsize = size(fxj);
//                 outcls = superiorfloat(x,fxj);
//                 finalInputChecks(x,fxj);
//                 % Define initializers.
//                 if issparse(fxj)
//                     zeros_nfx_by_nsubs = sparse(nfx,nsubs);
//                     zeros_outsize = sparse(outsize(1),outsize(2));
//                     zeros_nfx_by_1 = sparse(nfx,1);
//                 else
//                     zeros_nfx_by_nsubs = zeros([nfx,nsubs],outcls);
//                     zeros_outsize = zeros(outsize,outcls);
//                     zeros_nfx_by_1 = zeros(nfx,1,outcls);
//                 end
//                 qsubs = zeros_nfx_by_nsubs;
//                 errsubs = zeros_nfx_by_nsubs;
//                 qsubsk = fxj*WT(1);
//                 errsubsk = fxj*EWT(1);
//                 % Finish up the first subinterval.
//                 for j = 2:NNODES
//                     fxj = FUN(t(j)).*w(j);
//                     qsubsk = qsubsk + fxj*WT(j);
//                     errsubsk = errsubsk + fxj*EWT(j);
//                 end
//                 qsubsk = qsubsk.*halfh(1);
//                 errsubsk = errsubsk.*halfh(1);
//                 q = qsubsk;
//                 qsubs(:,1) = qsubsk(:);
//                 errsubs(:,1) = errsubsk(:);
//                 % Now process the remaining subintervals. We don't check
//                 % the mesh spacing on the first iteration.
//                 for k = 2:nsubs
//                     qsubsk = zeros_outsize;
//                     errsubsk = zeros_outsize;
//                     [t,w] = u(x(:,k));
//                     for j = 1:NNODES
//                         fxj = FUN(t(j)).*w(j);
//                         qsubsk = qsubsk + fxj*WT(j);
//                         errsubsk = errsubsk + fxj*EWT(j);
//                     end
//                     qsubsk = qsubsk.*halfh(k);
//                     errsubsk = errsubsk.*halfh(k);
//                     q = q + qsubsk;
//                     qsubs(:,k) = qsubsk(:);
//                     errsubs(:,k) = errsubsk(:);
//                 end
//                 firstFunEval = false;
//                 % Initialize partial sums.
//                 q_ok = zeros_nfx_by_1;
//                 err_ok = zeros_nfx_by_1;
        }
        else
        {
          restab_t qsubs = nt2::zeros(nt2::of_size(nfx, nsubs)); 
          restab_t errsubs = nt2::zeros(nt2::of_size(nfx, nsubs)); 
//                 qsubs = zeros_nfx_by_nsubs;
//                 errsubs = zeros_nfx_by_nsubs;
//                 q = reshape(q_ok,outsize);
//                 for k = 1:nsubs
//                     qsubsk = zeros_outsize;
//                     errsubsk = zeros_outsize;
//                     [t,w] = u(x(:,k));
//                     too_close = checkSpacing(t);
//                     if too_close
//                         break
//                     end
//                     for j = 1:NNODES
//                         fxj = FUN(t(j)).*w(j);
//                         qsubsk = qsubsk + fxj*WT(j);
//                         errsubsk = errsubsk + fxj*EWT(j);
//                     end
//                     qsubsk = qsubsk.*halfh(k);
//                     errsubsk = errsubsk.*halfh(k);
//                     q = q + qsubsk;
//                     qsubs(:,k) = qsubsk(:);
//                     errsubs(:,k) = errsubsk(:);
//                 end
//                 if too_close
//                     break
//                 end
//             end
//             % Locate subintervals where the approximate integrals are
//             % sufficiently accurate and use them to update the partial
//             % error sum.
//             nleft = 0;
//             tol = RTOL*abs(q(:));
//             tolr = 2*tol/pathlen;
//             tola = 2*ATOL/pathlen;
//             err_not_ok = zeros_nfx_by_1;
//             for k = 1:nsubs
//                 abserrsubsk = abs(errsubs(:,k));
//                 if all(abserrsubsk <= tolr*halfh(k) | ...
//                         abserrsubsk <= tola*halfh(k))
//                     q_ok = q_ok + qsubs(:,k);
//                     err_ok = err_ok + errsubs(:,k);
//                 else
//                     err_not_ok = err_not_ok + abserrsubsk;
//                     nleft = nleft + 1;
//                     subs(:,nleft) = subs(:,k);
//                     midpt(nleft) = midpt(k);
//                 end
//             end
//             subs = subs(:,1:nleft); % Trim subs array.
//             midpt = midpt(1:nleft); % Trim midpt array.
//             % The approximate error bound is constructed by adding the
//             % approximate error bounds for the subintervals with accurate
//             % approximations to the 1-norm of the approximate error bounds
//             % for the remaining subintervals.  This guards against
//             % excessive cancellation of the errors of the remaining
//             % subintervals.
//             errbnd = reshape(abs(err_ok) + err_not_ok, outsize);
//             % Check for nonfinites.
//             if ~all(isfinite(q(:)) & isfinite(errbnd(:)))
//                 warning(message('MATLAB:integral:NonFiniteValue'));
//                 if opstruct.ThrowOnFail
//                     error(message('MATLAB:integral:unsuccessful'));
//                 end
//                 break
//             end
//             % Test for convergence.
//             if nleft < 1 || all(errbnd(:) <= tol | errbnd(:) <= ATOL)
//                 break
//             end
//             % Split the remaining subintervals in half. Quit if splitting
//             % results in too many subintervals.
//             nsubs = 2*nleft;
//             if nsubs > MAXINTERVALCOUNT
//                 % newPersistence = ceil(nsubs/DEFAULT_MAXINTERVALCOUNT);
//                 warning(message('MATLAB:integral:MaxIntervalCountReached', ...
//                     sprintf('%9.1e',max(errbnd(:)))));
//                 if opstruct.ThrowOnFail
//                     error(message('MATLAB:integral:unsuccessful'));
//                 end
//                 break
//             end
//             subs = reshape([subs(1,:); midpt; midpt; subs(2,:)],2,[]);
//         end
//     end
   }

    
    template < class FUNC >
    void iterate_scalar_valued(FUNC f)
    {
      // Initialize array of subintervals of [a,b].
      itab_t subs = nt2::catv(interval_(nt2::_(begin_, end_-1)),
                              interval_(nt2::_(begin_+1, end_)));
      // Initialize partial sums.
      result_t q_ok = nt2::Zero<result_t>();
      result_t err_ok = nt2::Zero<result_t>();
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
        vtab_t fx = f(x);
        // Quit if mesh points are too close.
        fx.resize(nt2::of_size(nt2::numel(wt()), numel(fx)/numel(wt())));
        // Quantities for subintervals.
        restab_t qsubs = nt2::mtimes(wt(), fx)*halfh;
        restab_t errsubs = nt2::mtimes(ewt(), fx)* halfh;
        // Calculate current values of q and tol.
        result_t q = nt2::globalsum(qsubs) + q_ok;
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
        restab_t errsubs1 = nt2::rowvect(errsubs(notff)); errsubs =  errsubs1; //ALIASING CAN BE AVOIDED PERHAPS
        // The approximate error bound is constructed by adding the
        // approximate error bounds for the subintervals with accurate
        // approximations to the 1-norm of the approximate error bounds
        // for the remaining subintervals.  This guards against
        // excessive cancellation of the errors of the remaining
        // subintervals.
        errbnd_ = nt2::abs(err_ok) + nt2::norm(errsubs, 1);
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
      NT2_DISPLAY("adjust_and_call");
      bool fina = nt2::is_finite(a_);
      bool finb = nt2::is_finite(b_);
      if(fina && finb)
      { NT2_DISPLAY("fina && finb");
        vadapt(transform<F, details::fina_finb, input_t, value_t>(f, a_, b_, interval_));
      }
      else
      {
        bool infb = nt2::is_inf(b_);
        if (fina && infb)
        {
          vadapt(transform<F, details::fina_infb, input_t, value_t>(f, a_, b_, interval_));
        }
        else
        {
          bool infa = nt2::is_inf(a_);
          if (infa && finb)
          {
            vadapt(transform<F, details::infa_finb, input_t, value_t>(f, a_, b_, interval_));
          }
          else if (infa && infb)
          {
            vadapt(transform<F, details::infa_infb, input_t, value_t>(f, a_, b_, interval_));
          }
          else //is_nan(a) || is_nan(b)
          {
            result_t r = Nan<result_t>();
            errbnd_ = nt2::abs(r);
            fcnt_ = 1;
          }
        }
      }
    }
  };
} }


namespace nt2 { namespace ext
                {
                  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::integral_, tag::cpu_
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
      details::integral_impl<input_t, value_t> q;
      q.compute(f, x, o, input_is_real_t());
      result_type that =  {q.result(), q.lasterror(),q.nbeval(),q.ok()};
      return that;
    }
  };
} }
#endif
