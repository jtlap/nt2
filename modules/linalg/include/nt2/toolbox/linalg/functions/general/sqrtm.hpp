/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_SQRTM_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_SQRTM_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/sqrtm.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>  

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrtm_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    typedef table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef nt2::table<value_type > tab_t; 
      size_t n = length(a0);
      tie(q, t) = schur(a,'complex'); // t is complex schur form.
      if (nt2::isdiagonal(a0))
        {
          return nt2::from_diag(sqrt(nt2::diag_of(a0))); 
        }
      else
        {
          // Compute upper triangular square root R of T, a column at a time.
          
          tab_t r = nt2::zeros(n);  
          for (size_t j=1; j <= n; ++j)
            {
              r(j,j) = nt2::sqrt(t(j,j));
              for (size_t i=j-1; j >= 1; --j)
                {
                  itab_ k = _(i+1, j-1);
                  s = nt2::mtimes(r(i,_(i+1, j-1)), r(_(i+1, j-1),j));
                  r(i,j) = (t(i,j) - s)/(r(i,i) + r(j,j));
                }
            }
        } 
      x = nt2::mtimes( nt2::mtimes(q, r), nt2::trans(nt2::conj(q)));
      //bool nzeig = any(diag_of(T)(_))(1);
      
      // if nzeig 
      //     warning(message('sqrtm:SingularMatrix'))
      // end  
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrtm_, tag::cpu_
                            , (A0)
                            , (scalar_<fundamental_<A0> >)
                            )
  {
    typedef typename nt2::meta::as_floating<A0>::type return_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::sqrt(nt2::tofloat(a0)); 
    }
  };  
} }

#endif

// function [X, arg2, condest] = sqrtm(A)
// %SQRTM     Matrix square root.
// %   X = SQRTM(A) is the principal square root of the matrix A, i.e. X*X = A.
// %          
// %   X is the unique square root for which every eigenvalue has nonnegative
// %   real part.  If A has any real, negative eigenvalues then a complex
// %   result is produced.  If A is singular then A may not have a
// %   square root.  A warning is printed if exact singularity is detected.
// %          
// %   With two output arguments, [X, RESNORM] = SQRTM(A) does not print any
// %   warning, and returns the residual, norm(A-X^2,'fro')/norm(A,'fro').
// %
// %   With three output arguments, [X, ALPHA, CONDEST] = SQRTM(A) returns a
// %   stability factor ALPHA and an estimate CONDEST of the matrix square root
// %   condition number of X.  The residual NORM(A-X^2,'fro')/NORM(A,'fro') is
// %   bounded approximately by N*ALPHA*EPS and the Frobenius norm relative
// %   error in X is bounded approximately by N*ALPHA*CONDEST*EPS, where
// %   N = MAX(SIZE(A)).
// %
// %   See also EXPM, LOGM, FUNM.

// %   References:
// %   N. J. Higham, Computing real square roots of a real
// %       matrix, Linear Algebra and Appl., 88/89 (1987), pp. 405-430.
// %   A. Bjorck and S. Hammarling, A Schur method for the square root of a
// %       matrix, Linear Algebra and Appl., 52/53 (1983), pp. 127-140.
// %
// %   Nicholas J. Higham
// %   Copyright 1984-2009 The MathWorks, Inc.
// %   $Revision: 5.15.4.5 $  $Date: 2010/08/23 23:11:29 $

// n = length(A);
// [Q, T] = schur(A,'complex');  % T is complex Schur form.

// if isequal(T,diag(diag(T)))      % Check if T is diagonal.
    
//     R = diag(sqrt(diag(T)));     % Square root always exists. 
    
// else
    
//     % Compute upper triangular square root R of T, a column at a time.
    
//     R = zeros(n);  
//     for j=1:n
//         R(j,j) = sqrt(T(j,j));
//         for i=j-1:-1:1
//             k = i+1:j-1;
//             s = R(i,k)*R(k,j);
//             R(i,j) = (T(i,j) - s)/(R(i,i) + R(j,j));
//         end
//     end
    
// end

// X = Q*R*Q';

// nzeig = any(diag(T)==0);

// if nzeig && (nargout ~= 2)
//     warning(message('MATLAB:sqrtm:SingularMatrix'))
// end

// if nargout == 2
//     arg2 = norm(X*X-A,'fro')/norm(A,'fro');
// end

// if nargout > 2
    
//     arg2 = norm(R,'fro')^2 / norm(T,'fro');
    
//     if nzeig
//         condest = inf;
//     else
        
//         % Power method to get condition number estimate.
        
//         tol = 1e-2;
//         x = ones(n^2,1);    % Starting vector.
//         cnt = 1;
//         e = 1;
//         e0 = 0;
//         while abs(e-e0) > tol*e && cnt <= 6
//             x = x/norm(x);
//             x0 = x;
//             e0 = e;
//             Sx = tksolve(R, x);
//             x = tksolve(R, Sx, 'T');
//             e = sqrt(real(x0'*x));  % sqrt of Rayleigh quotient.
//             % fprintf('cnt = %2.0f, e = %9.4e\n', cnt, e)
//             cnt = cnt+1;
//         end
        
//         condest = e*norm(A,'fro')/norm(X,'fro');
        
//     end
    
// end

// % As in FUNM:
// if isreal(A) && norm(imag(X),1) <= 10*n*eps*norm(X,1)
//    X = real(X);
// end

// %====================================

// function x = tksolve(R, b, tran)
// %TKSOLVE     Solves block triangular Kronecker system.
// %            x = TKSOLVE(R, b, TRAN) solves
// %                  A*x = b  if TRAN = '',
// %                 A'*x = b  if TRAN = 'T',
// %            where A = KRON(EYE,R) + KRON(TRANSPOSE(R),EYE).
// %            Default: TRAN = ''.

// if nargin < 3, tran = ''; end

// n = max(size(R));
// x = zeros(n^2,1);

// I = eye(n);

// if isempty(tran)

//    % Forward substitution.
//    for i = 1:n
//        temp = b(n*(i-1)+1:n*i);
//        for j = 1:i-1
//            temp = temp - R(j,i)*x(n*(j-1)+1:n*j);
//        end
//        x(n*(i-1)+1:n*i) = (R + R(i,i)*I) \ temp;
//    end

// elseif strcmp(tran,'T')

//    % Back substitution.
//    for i = n:-1:1
//        temp = b(n*(i-1)+1:n*i);
//        for j = i+1:n
//            temp = temp - conj(R(i,j))*x(n*(j-1)+1:n*j);
//        end
//        x(n*(i-1)+1:n*i) = (R' + conj(R(i,i))*I) \ temp;
//    end

// end

// return
