//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_LSCOV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_LSCOV_HPP_INCLUDED

#include <nt2/linalg/functions/lscov.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/mldivide.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/include/functions/orth.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
// #include <nt2/core/utility/assign_swap.hpp>
#include <nt2/table.hpp>


namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = lscov(...) at assign time and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( lscov_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::lscov_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef typename container::table<value_t>                          table_t;
    typedef typename meta::as_real<value_t>::type                      rvalue_t;
    typedef typename meta::as_integer<rvalue_t, unsigned>::type                  ivalue_t;
    typedef typename container::table<rvalue_t>                        rtable_t;
    typedef typename container::table<ivalue_t>                        itable_t;
    typedef nt2::memory::container<tag::table_, value_t, nt2::_2D>   o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      table_t aa, bb;
      NT2_AS_TERMINAL_INOUT(o_semantic, a, boost::proto::child_c<0>(a0), aa);
      NT2_AS_TERMINAL_INOUT(o_semantic, b, boost::proto::child_c<1>(a0), bb);
      bool cholevski;
      std::size_t rankv;
      precompute(a0, a, b, cholevski, rankv, N0());
      if(cholevski)
        lsqchol(a1, a, b, N1());
      else
        lsqorth(a1, a, b, rankv, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class A, class B> BOOST_FORCEINLINE
      void precompute(A0 &, A&, B&,
                      bool &cholevski, std::size_t &,
                      boost::mpl::long_<2> const &) const
    {
      cholevski =  true;
    }

    template < class A, class B> BOOST_FORCEINLINE
      void precompute(A0 &a0, A&a, B&b,
                      bool & cholevski, std::size_t & rankv,
                      boost::mpl::long_<3> const &) const
    {
      table_t vv;
      NT2_AS_TERMINAL_INOUT(o_semantic, v, boost::proto::child_c<2>(a0), vv);
      if (isempty(v))
      {
        cholevski = true;
      }
      else if (isvector(v))
      {
        v = colvect(v);
        a *= expand_to(v, a.extent());
        b *= expand_to(v, b.extent());
        cholevski = globalall(is_gtz(v));
      }
      else
      {
        int p;
        table_t t;
        tie(t, p) = chol(v);
        rankv = size(t, 2);
        cholevski = p > int(height(v));
        if(cholevski)
        {
          a = linsolve(t, a);
          b = linsolve(t, b);
        }
      }
    }

    template < class A, class B> BOOST_FORCEINLINE
      void precompute(A0 &a0, A&a, B&b,
                      bool & cholevski, std::size_t & rankv,
                      boost::mpl::long_<4> const &) const
    {
      precomp(a0, a, b, cholevski, rankv,  boost::proto::child_c<3>(a0));
    }

    template < class A, class B> BOOST_FORCEINLINE
      void precomp(A0 &a0, A&a, B&b,
                   bool & cholevski, std::size_t & rankv,
                   const tag::chol_ &) const
    {
      precompute(a0, a, b, cholevski, rankv, boost::mpl::long_<3>());
      if (!cholevski)
      {
        BOOST_ASSERT_MSG(cholevski, "you cannot enforce cholevski method with a rank defective covariance matrix");
      }

    }

    template < class A, class B> BOOST_FORCEINLINE
      void precomp(A0 &a0, A&, B&,
                   bool & cholevski, std::size_t & rankv,
                   const tag::orth_ &) const
    {
      table_t vv;
      NT2_AS_TERMINAL_INOUT(o_semantic, v, boost::proto::child_c<2>(a0), vv);
      int p;
      table_t t;
      tie(t, p) = chol(v);
      rankv = size(t, 2);
      cholevski = false;
    }


    template < class A, class B> BOOST_FORCEINLINE
    void lsqchol(A1& a1, A& a, B& b, N1 const &) const
    {
      table_t q, r, x;
      container::table<nt2_la_int> perm;
      tie(q, r, perm) = qr(a,0);
      table_t z = mtimes(ctranspose(q), b);
      auto keepcols = (abs(diag_of(r)) > abs(r(1))*length(a)*Eps<rvalue_t>());
      std::size_t ranka = nbtrue(keepcols);
      if (ranka < width(a))
      {
        //        warning(message('matlab:lscov:rankdefdesignmat'));
        r = r(keepcols,keepcols);
        z = z(keepcols,_);
        perm = perm(keepcols);
      }

      //Compute the LS coefficients, filling in zeros in elements corresponding
      // to rows of R that were thrown out.
      table_t xx = mldivide(r, z);
      x = zeros(width(a),width(b), meta::as_<value_t>());
      x(perm,_) = xx;
      boost::proto::child_c<0>(a1) = x;
      setresults(a1, a, b, q, r, perm, keepcols, z, ranka, N1());
    }

    template < class A, class B> BOOST_FORCEINLINE
    void lsqorth(A1& , A& , B& , std::size_t, N1 const &) const
    {
//     [Q,R,perm] = qr(A); % returns the _full_ Q and R
//     R((nvar+1):nobs,:) = []; % remove lower half (zeros)
//     [~,perm] = max(perm,[],1); % permutation matrix -> vector

//     % Use the rank-revealing QR to remove dependent columns of A.
//     rankA = sum(abs(diag(R)) > abs(R(1)).*max(nobs,nvar).*eps(class(R)));
//     if rankA < nvar
//         warning(message('MATLAB:lscov:RankDefDesignMat'));
//         R = R(1:rankA,1:rankA);
//         perm = perm(1:rankA);
//     end

//     % Separate out the columns of Q that are orthogonal to A, and get the
//     % orthogonal components of T and b.  Q0'*T can be tall, square, or
//     % wide, and can be rank deficient.
//     Q0 = Q(:,(rankA+1):nobs);
//     Q(:,(rankA+1):nobs) = []; % remove Q0
//     T0 = Q0'*T;
//     b0 = Q0'*b;

//     % Determine whether T is entirely in the column space of A.  When A is
//     % full-rank square, it always is.
//     if rankA == nobs
//         zeroE = true;
//     % Otherwise, check if T0 is effectively zero (small compared to T). Q0
//     % and T are factorizations of other matrices, so set tol liberally to
//     % allow for the extra errors resulting from their computation.
//     elseif norm(T0,1) < norm(T,1)*(max(nobs,rankV).^2)*eps(class(T0))
//         warning(message('MATLAB:lscov:TOrthogToNullSpace'));
//         zeroE = true;
//     else
//         zeroE = false;
//     end

//     % When T is entirely in span(A), then b = A*x + T*e can be satisfied
//     % with e = 0, as long as b is in span(A) too.
//     if zeroE
//         e = zeros(rankV,nrhs,outClass);
//         if nargout > 1
//             P = 0;
//             mse = zeros(1,nrhs,outClass);
//         end

//         % If A is full-rank square, then b is always in span(A).
//         if rankA == nobs
//             feasible = true;
//         else
//             % If b0 is effectively zero, then b is in span(A).
//             feasible = (norm(b0,1) < norm(b,1).*(nobs.^2).*eps(class(b0)));
//         end

//     % The minimum-norm solution to (Q0'*T)*e = (Q0'*b) is the error vector
//     % required to satisfy b = A*x + T*e.
//     else
//         if nargout > 1
//             [e,err,P] = lsminnorm(T0, b0);

//             % Compute the MSE, need it for the std. errs. and cov matrix.
//             dfe = size(P,2);
//             mse = sum(e.*conj(e),1) ./ dfe;
//         else
//             [e,err] = lsminnorm(T0, b0);
//         end

//         % e should satisfy (Q0'*T)*e = (Q0'*b) exactly.  Set a zero
//         % tolerance dependent on e's length.  e might be several vectors.
//         feasible = all(err < sqrt(sum(e.*conj(e), 1)).*rankV.*eps(class(err)));
//     end

//     % If b is not achievable with A*x + T*e, there's no solution.
//     if ~feasible
//         if nrhs == 1
//             error(message('MATLAB:lscov:InfeasibleRHS'));
//         else
//             error(message('MATLAB:lscov:InfeasibleRHScol'));
//         end
//     end

//     % T*e accounts exactly for the component of b that is orthogonal
//     % to A (i.e., the part that can't be accounted for by A*x).
//     % Subtract T*e from b; everything that is left over is in the
//     % column space of A.
//     b = b - T*e;

//     % Find x so that A*x exactly equals what remains in b.  Fill in zeros
//     % in elements corresponding to rows of R that were thrown out.
//     z = Q'*b;
//     x = zeros(nvar,1,outClass);
//     x(perm,1:nrhs) = R \ z;
    }

    template < class A, class B, class Q, class R, class P, class K, class Z> BOOST_FORCEINLINE
    void setresults(A1&, A&, B&, Q&, R&, P&, K&, Z&, std::size_t
                     , boost::mpl::long_<1> const &) const
    {
    }

    template < class A, class B, class Q, class R, class P, class K, class Z> BOOST_FORCEINLINE
    void setresults(A1& a1, A& a, B& b, Q&q, R& r, P& perm, K & keepcols, Z&z, std::size_t ranka
                   , boost::mpl::long_<2> const &) const
    {
      size_t dfe = height(a) - ranka;
      rtable_t mse;
      if (dfe)
      {
        auto res = b-mtimes(q(_, keepcols), z);
        mse = asum2(res,1)/value_t(dfe);
      }
      else // rankA == nobs, and so Ax == b exactly
      {
        mse = zeros(1,width(b), meta::as_<rvalue_t>());
      }
      table_t rinv = mldivide(r, eye(ranka, meta::as_<value_t>()));
      rtable_t stdx = zeros(width(a), width(b), meta::as_<rvalue_t>());
      stdx(perm,_) = sqrt(mtimes(asum2(rinv,2), mse)); // an outer product if nrhs>1
      boost::proto::child_c<1>(a1) = stdx;
    }

    template < class A, class B, class Q, class R, class P, class K, class Z> BOOST_FORCEINLINE
    void setresults(A1 &a1, A&a, B&b, Q&q, R&r, P&perm, K &keepcols, Z&z
                   , std::size_t ranka, boost::mpl::long_<3> const &) const
    {
      size_t dfe = height(a) - ranka;
      rtable_t mse;
      if (dfe)
      {
        auto res = b-mtimes(q(_, keepcols), z);
        mse = real(sum(res*conj(res),1))/value_t(dfe);
      }
      else // rankA == nobs, and so Ax == b exactly
      {
        mse = zeros(1,width(b), meta::as_<rvalue_t>());
      }
      table_t rinv = mldivide(r, eye(ranka, meta::as_<value_t>()));
      rtable_t stdx = zeros(width(a), width(b), meta::as_<rvalue_t>());
      stdx(perm,_) = sqrt(mtimes(asum2(rinv,2), mse)); // an outer product if nrhs>1
      boost::proto::child_c<1>(a1) = stdx;
      boost::proto::child_c<2>(a1) = mse;
    }

    template < class A, class B, class Q, class R, class P, class K, class Z> BOOST_FORCEINLINE
      void setresults(A1 &a1, A&a, B&b, Q&q, R& r, P&perm, K & keepcols, Z& z, std::size_t ranka
                     , boost::mpl::long_<4> const &) const
    {
      BOOST_ASSERT_MSG(width(b) == 1, "b must be a vector to compute s");
       setresults(a1, a, b, q, r, perm, keepcols, z, ranka, boost::mpl::long_<3>());
      auto mse =  boost::proto::child_c<2>(a1);
      table_t rinv = mldivide(r, eye(ranka, meta::as_<value_t>()));
      table_t s = zeros(width(a), meta::as_<value_t>());
      s(perm,perm) = mtimes(rinv, ctrans(rinv))*mse(1);
      rtable_t stdx = sqrt(diag_of(s));
      boost::proto::child_c<1>(a1) = stdx;
      boost::proto::child_c<3>(a1) = s;
    }

  };


} }

#endif
