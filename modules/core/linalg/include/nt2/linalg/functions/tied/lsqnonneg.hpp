//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_LSQNONNEG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_LSQNONNEG_HPP_INCLUDED

#include <nt2/linalg/functions/lsqnonneg.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/falses.hpp>
#include <nt2/include/functions/globalany.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/mldivide.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/posmax.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/trues.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/utility/assign_swap.hpp>
#include <nt2/table.hpp>


namespace nt2 { namespace ext
{
  //============================================================================
  // Capture a tie(l, u, p) = lsqnonneg(...) at assign time and resolve to optimized call
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( lsqnonneg_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::lsqnonneg_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename A0::value_type                                     value_t;
    typedef typename container::table<value_t>                          table_t;
    typedef typename meta::as_logical<value_t>::type                     bool_t;
    typedef typename container::table<bool_t>                          btable_t;
    typedef nt2::memory::container<tag::table_, value_t, nt2::_2D>   o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      NT2_AS_TERMINAL_IN(o_semantic, c, boost::proto::child_c<0>(a0));
      NT2_AS_TERMINAL_IN(o_semantic, d, boost::proto::child_c<1>(a0));
      value_t tol = gettol(a0, c, N0());
      compute(c, d, tol, a1, N1());
    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class C > BOOST_FORCEINLINE
    value_t gettol(A0 const &, C const & c, boost::mpl::long_<2> const &) const
    {
      return Ten<value_t>()*Eps<value_t>()*mnorm1(c)*length(c);
    }

    template < class C > BOOST_FORCEINLINE
    value_t gettol(A0 const & a0, C const &, boost::mpl::long_<3> const &) const
    {
      return boost::proto::value(boost::proto::child_c<3>(a0));
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1&,  R const &, std::size_t, std::size_t
                   , W const &, boost::mpl::long_<1> const &) const
    {
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t, std::size_t
                   , W const &, boost::mpl::long_<2> const &) const
    {
      value_t resnorm = mtimes(trans(resid), resid);
      boost::proto::child_c<1>(a1) = resnorm;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
      void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                     , W const & w, boost::mpl::long_<3> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w,  boost::mpl::long_<2>());
      boost::proto::child_c<2>(a1) = resid;
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<4> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w,  boost::mpl::long_<3>());
      boost::proto::child_c<3>(a1) =  exitflag;
    }

    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<5> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w, boost::mpl::long_<4>());
      boost::proto::child_c<4>(a1) =  outeriter;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class W, class R> BOOST_FORCEINLINE
    void setresults( A1& a1, R const & resid, std::size_t exitflag, std::size_t outeriter
                   , W const & w, boost::mpl::long_<6> const &) const
    {
      setresults(a1, resid, exitflag, outeriter, w, boost::mpl::long_<5>());
      boost::proto::child_c<5>(a1) =  w;
    }
    //==========================================================================
    // INTERNAL ONLY
    //==========================================================================
    template < class C, class D> BOOST_FORCEINLINE
    void compute(C const & c, D const & d, value_t tol, A1& a1, N1 const & ) const
    {
      std::size_t n = size(c,2);
      //  initialize vector of n zeros and infs (to be used later)
      table_t nzeros = zeros(n,1,meta::as_<value_t>());
      table_t wz = nzeros;
      // initialize set of non-active columns to null
      btable_t p = falses(n,1,meta::as_<bool_t>());
      //  initialize set of active columns to all and the initial point to zeros
      btable_t z = trues(n,1,meta::as_<bool_t>());
      table_t x = nzeros;

      table_t resid = d - mtimes(c, x);
      table_t w = mtimes(trans(c), resid);

      //  set up iteration criterion
      std::size_t outeriter = 0;
      std::size_t iter = 0;
      const std::size_t itmax = 3*n;
      //  outer loop to put variables into set to hold positive coefficients
      while (globalany(z) && globalany(w(z) > tol))
      {
        ++outeriter;
        //  reset intermediate solution zz
        table_t zz = nzeros;
        //  create wz, a lagrange multiplier vector of variables in the zero set.
        //  wz must have the same size as w to preserve the correct indices, so
        //  set multipliers to -inf for variables outside of the zero set.
        wz(p) = Minf<value_t>();
        wz(z) = w(z);
        //  find variable with largest lagrange multiplier
        std::size_t t = globalfind(globalmax(wz) == wz);
        //   move variable t from zero set to positive set
        p(t) = True<bool_t>();
        z(t) = False<bool_t>();
        //  compute intermediate solution using only variables in positive set
        zz(p) = mldivide(c(_,p), d);
        // inner loop to remove elements from the positive set which no longer belong
        while (globalany(is_lez(zz(p))))
        {
          ++iter;
          if (iter > itmax)
          {
            assign_swap(boost::proto::child_c<0>(a1), zz);
            setresults(a1, resid, 0, outeriter, w, N1());
            return;
          }
          //  find indices where intermediate solution zz is approximately negative
          btable_t q = logical_and(is_lez(zz), p);
          //    choose new x subject to keeping new x nonnegative
          value_t alpha = nt2::min(x(q)/(x(q) - zz(q)));
          x  += alpha*(zz - x);
          //  reset z and p given intermediate values of x
          z = logical_or(logical_and((nt2::abs(x) < tol), p), z);
          p = logical_not(z);
          zz = nzeros;          // reset zz
          zz(p) = mldivide(c(_,p), d);     // re-solve for zz
        }
        x =  zz;
        resid = d - mtimes(c, x);
        w = mtimes(trans(c), resid);
      }
      assign_swap(boost::proto::child_c<0>(a1), x);
      setresults(a1, resid, 1, outeriter, w, N1());
    }

  };
} }

#endif

// function [x,resnorm,resid,exitflag,output,lambda] = lsqnonneg(C,d,options,varargin)
// %LSQNONNEG Linear least squares with nonnegativity constraints.
// %   X = LSQNONNEG(C,d) returns the vector X that minimizes NORM(d-C*X)
// %   subject to X >= 0. C and d must be real.
// %
// %   X = LSQNONNEG(C,d,OPTIONS) minimizes with the default optimization
// %   parameters replaced by values in the structure OPTIONS, an argument
// %   created with the OPTIMSET function.  See OPTIMSET for details. Used
// %   options are Display and TolX. (A default tolerance TolX of
// %   10*MAX(SIZE(C))*NORM(C,1)*EPS is used.)
// %
// %   X = LSQNONNEG(PROBLEM) finds the minimum for PROBLEM. PROBLEM is a
// %   structure with the matrix 'C' in PROBLEM.C, the vector 'd' in
// %   PROBLEM.d, the options structure in PROBLEM.options, and solver name
// %   'lsqnonneg' in PROBLEM.solver. The structure PROBLEM must have all the
// %   fields.
// %
// %   [X,RESNORM] = LSQNONNEG(...) also returns the value of the squared 2-norm of
// %   the residual: norm(d-C*X)^2.
// %
// %   [X,RESNORM,RESIDUAL] = LSQNONNEG(...) also returns the value of the
// %   residual: d-C*X.
// %
// %   [X,RESNORM,RESIDUAL,EXITFLAG] = LSQNONNEG(...) returns an EXITFLAG that
// %   describes the exit condition of LSQNONNEG. Possible values of EXITFLAG and
// %   the corresponding exit conditions are
// %
// %    1  LSQNONNEG converged with a solution X.
// %    0  Iteration count was exceeded. Increasing the tolerance
// %       (OPTIONS.TolX) may lead to a solution.
// %
// %   [X,RESNORM,RESIDUAL,EXITFLAG,OUTPUT] = LSQNONNEG(...) returns a structure
// %   OUTPUT with the number of steps taken in OUTPUT.iterations, the type of
// %   algorithm used in OUTPUT.algorithm, and the exit message in OUTPUT.message.
// %
// %   [X,RESNORM,RESIDUAL,EXITFLAG,OUTPUT,LAMBDA] = LSQNONNEG(...) returns
// %   the dual vector LAMBDA  where LAMBDA(i) <= 0 when X(i) is (approximately) 0
// %   and LAMBDA(i) is (approximately) 0 when X(i) > 0.
// %
// %   See also LSCOV, SLASH.

// %   Copyright 1984-2012 The MathWorks, Inc.

// % Reference:
// %  Lawson and Hanson, "Solving Least Squares Problems", Prentice-Hall, 1974.

// % Check if more inputs have been passed. In that case error.
// if nargin > 4
//     error(message('MATLAB:lsqnonneg:TooManyInputs'));
// end

// defaultopt = struct('Display','notify','TolX','10*eps*norm(C,1)*length(C)');
// % If just 'defaults' passed in, return the default options in X
// if nargin == 1 && nargout <= 1 && isequal(C,'defaults')
//     x = defaultopt;
//     return
// end

// if nargin > 2
//     % Check for deprecated syntax
//     options = deprecateX0(options,nargin,varargin{:});
// elseif nargin == 1
//     % Detect problem structure input
//     if isa(C,'struct')
//         [C,d,options] = separateOptimStruct(C);
//     else % Single input and non-structure.
//         error(message('MATLAB:lsqnonneg:InputArg'));
//     end
// elseif nargin == 0
//     error(message('MATLAB:lsqnonneg:NotEnoughInputs'));
// else
//     % No options passed, set to empty
//     options = [];
// end

// if ~isreal(C) || ~isreal(d),
//     error(message('MATLAB:lsqnonneg:ComplexCorD'));
// end

// % Check for non-double inputs
// if ~isa(C,'double') || ~isa(d,'double')
//     error(message('MATLAB:lsqnonneg:NonDoubleInput'))
// end

// printtype = optimget(options,'Display',defaultopt,'fast');
// tol = optimget(options,'TolX',defaultopt,'fast');

// % In case the defaults were gathered from calling: optimset('lsqnonneg'):
// if ischar(tol)
//     if strcmpi(tol,'10*eps*norm(c,1)*length(c)')
//         tol = 10*eps*norm(C,1)*length(C);
//     else
//         error(message('MATLAB:lsqnonneg:OptTolXNotPosScalar'))
//     end
// end

// switch printtype
//     case {'notify','notify-detailed'}
//         verbosity = 1;
//     case {'none','off'}
//         verbosity = 0;
//     case {'iter','iter-detailed'}
//         warning(message('MATLAB:lsqnonneg:InvalidDisplayValueIter'))
//         verbosity = 3;
//     case {'final','final-detailed'}
//         verbosity = 2;
//     otherwise
//         error(message('MATLAB:lsqnonneg:InvalidOptParamDisplay'));
// end

// n = size(C,2);
// % Initialize vector of n zeros and Infs (to be used later)
// nZeros = zeros(n,1);
// wz = nZeros;

// % Initialize set of non-active columns to null
// P = false(n,1);
// % Initialize set of active columns to all and the initial point to zeros
// Z = true(n,1);
// x = nZeros;

// resid = d - C*x;
// w = C'*resid;

// % Set up iteration criterion
// outeriter = 0;
// iter = 0;
// itmax = 3*n;
// exitflag = 1;

// % Outer loop to put variables into set to hold positive coefficients
// while any(Z) && any(w(Z) > tol)
//    outeriter = outeriter + 1;
//    % Reset intermediate solution z
//    z = nZeros;
//    % Create wz, a Lagrange multiplier vector of variables in the zero set.
//    % wz must have the same size as w to preserve the correct indices, so
//    % set multipliers to -Inf for variables outside of the zero set.
//    wz(P) = -Inf;
//    wz(Z) = w(Z);
//    % Find variable with largest Lagrange multiplier
//    [~,t] = max(wz);
//    % Move variable t from zero set to positive set
//    P(t) = true;
//    Z(t) = false;
//    % Compute intermediate solution using only variables in positive set
//    z(P) = C(:,P)\d;
//    % inner loop to remove elements from the positive set which no longer belong
//    while any(z(P) <= 0)
//        iter = iter + 1;
//        if iter > itmax
//            msg = getString(message('MATLAB:lsqnonneg:IterationCountExceeded'));
//            if verbosity
//                disp(msg)
//            end
//            exitflag = 0;
//            output.iterations = outeriter;
//            output.message = msg;
//            output.algorithm = 'active-set';
//            resnorm = sum(resid.*resid);
//            x = z;
//            lambda = w;
//            return
//        end
//        % Find indices where intermediate solution z is approximately negative
//        Q = (z <= 0) & P;
//        % Choose new x subject to keeping new x nonnegative
//        alpha = min(x(Q)./(x(Q) - z(Q)));
//        x = x + alpha*(z - x);
//        % Reset Z and P given intermediate values of x
//        Z = ((abs(x) < tol) & P) | Z;
//        P = ~Z;
//        z = nZeros;           % Reset z
//        z(P) = C(:,P)\d;      % Re-solve for z
//    end
//    x = z;
//    resid = d - C*x;
//    w = C'*resid;
// end

// lambda = w;
// resnorm = resid'*resid;
// output.iterations = outeriter;
// output.algorithm = 'active-set';
// msg = getString(message('MATLAB:lsqnonneg:OptimizationTerminated'));
// if verbosity > 1
//     disp(msg)
// end
// output.message = msg;


// %--------------------------------------------------------------------------
// function options = deprecateX0(options,numInputs,varargin)
// % Code to check if user has passed in x0. If so, ignore it and warn of its
// % deprecation. Also check whether the options have been passed in either
// % the 3rd or 4th input.
// if numInputs == 4
//     % 4 inputs given; the 3rd (variable name "options") will be interpreted
//     % as x0, and the 4th as options
//     if ~isempty(options)
//         % x0 is non-empty
//         warning(message('MATLAB:lsqnonneg:ignoringX0'));
//     end
//     % Take the 4th argument as the options
//     options = varargin{1};
// elseif numInputs == 3
//     % Check if a non-empty or non-struct has been passed in for options
//     % If so, assume that it's an attempt to pass x0
//     if ~isstruct(options) && ~isempty(options)
//         warning(message('MATLAB:lsqnonneg:ignoringX0'));
//         % No options passed, set to empty
//         options = [];
//     end
// end
