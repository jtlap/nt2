/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_LU_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_LU_HPP_INCLUDED

#include <nt2/sdk/error/warning.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/toolbox/linalg/details/utility/options.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/lapack/getrf.hpp>
#include <nt2/toolbox/linalg/details/lapack/gecon.hpp>
#include <nt2/toolbox/linalg/details/lapack/getri.hpp>
#include <nt2/toolbox/linalg/details/lapack/gesvx.hpp>
#include <nt2/toolbox/linalg/details/lapack/lange.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

// TODO:
// these are the kind of syntaxes to be enforced by nt2::chol
//  lu     lu factorization.
//     [l,u] = lu(a) stores an upper triangular matrix in u and a
//     "psychologically lower triangular matrix" (i.e. a product of lower
//     triangular and permutation matrices) in l, so that a = l*u. a can be
//     rectangular.
// -> {pl, u]

//     [l,u,p] = lu(a) returns unit lower triangular matrix l, upper
//     triangular matrix u, and permutation matrix p so that p*a = l*u.
// -> {l, u, p]

//     [l,u,p] = lu(a,'vector') returns the permutation information as a
//     vector instead of a matrix.  that is, p is a row vector such that
//     a(p,:) = l*u.  similarly, [l,u,p] = lu(a,'matrix') returns a
//     permutation matrix p.  this is the default behavior.
// -> {l, u, ip]

////////////////////////////////////////////////////////////////////////////////////////
// The class provides:
// constructor from an expression or matrix a
//
// accesors to l, u, p, pl and ip
//
// l is lower unittriangular part of lu_
// u is upper triangular part of lu_
// p is a permutation matrix
// pl is l permuted by p
// ip is the permutation index vector defining p
// we have l*u =  p*a
//         pl*u =  a
/////////////////////////////////////////////////// TODO  perhaps l and u could return an expresiion rather than a matrix
//
// the class allow to compute
//
// status the plu status from lapack
//
// rank the matrix rank
//
// When a is square
// det and absdet determinant and absolute value of the determinant
// They have two syntaxes
//  1 - d =  f.det()   or d =  f.absdet()
//  2 - m =  f.det(e)  or m =  f.absdet(e)
// In the second case m is a mantissa and e and exponent
// If there is no overflow or undeflow in e the determinant is then equal to ldexp(m, e)
//
// rcond the reciprocal condition number of a
//
// Two solvers
// solve and inplace_solve
//
// a matrix inversion
// inv
// inv() can emit a warning if rcond is bad
// inv(false) never warns
//     please avoid using inv if you need not the inverse coefficients.

namespace nt2 { namespace details
{
  template<class T> struct lu_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t;
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;

    template<class Input>
    lu_result ( Input& xpr
              , typename boost::
                disable_if_c<boost::is_same<lu_result,Input>::value>::type* = 0
              )
      : a_(xpr)
      , lu_(xpr)
      , m_( nt2::height(xpr) )
      , n_( nt2::width(xpr)  )
      , ldlu_( lu_.leading_size() )
      , ipiv_(nt2::of_size(nt2::min(n_, m_), 1))
      , rc_(base_t(-1))
      , info_(0)
    {
      nt2::details::getrf(&m_, &n_, lu_.raw(), &ldlu_, ipiv_.raw(), &info_, w_);
    }

    lu_result(lu_result const& src)
      : a_(src.a_) , lu_(src.lu_), m_( src.m_ ), n_( src.n_ )
      , ldlu_( src.ldlu_ ) , ipiv_(src.ipiv_)
      , rc_(src.rc_)
      , info_(src.info_) , w_(src.w_)
    {}

    lu_result& operator=(lu_result const& src)
    {
      a_      = src.a_;
      lu_     = src.lu_;
      m_      = src.m_;
      n_      = src.n_;
      ldlu_   = src.ldlu_;
      ipiv_   = src.ipiv_;
      rc_     = src.rc_;
      info_   = src.info_;
      w_      = src.w_;
      return *this;
    }

    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type values() const { return lu_; }

    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type original() const { return a_; }

    //==========================================================================
    // Return u part of the decomposition
    //==========================================================================
    result_type u() const
    {
      result_type that;
      that = nt2::triu(lu_(_(1, std::min(n_, m_)),_));
      return that;
    }
    //==========================================================================
    // Return l part of the decomposition
    //==========================================================================
    result_type l() const
    {
      result_type that;
      that = nt2::tri1l(lu_(_,_(1, std::min(n_, m_))));
      return that;
    }

    //==========================================================================
    // Return p part of the decomposition as a matrix such that p*a = l*u
    //==========================================================================
    result_type p() const
    {
      std::size_t mm = nt2::numel(ipiv_);
      tab_t pp = nt2::eye(mm, mm, meta::as_<type_t>());
      for(size_t i=1; i <= mm; ++i)
        // pp({i, ipiv_(i)}, _) =  pp({ipiv_(i),i}, _)
        {
          tab_t c = pp(i, _);
          pp(i,_) = pp(ipiv_(i),_);
          pp(ipiv_(i),_) = c;
        }
      return pp;
    }
    //==========================================================================
    // Return p part of the decomposition as a vector
    //==========================================================================
    itab_t ip() const
    {
      //      itab_t ip = itab_t(ipiv_.raw(), ipiv_.raw()+numel(ipiv_));
      itab_t ip(of_size(1, numel(ipiv_)));
      for(size_t i=1; i <= numel(ipiv_); ++i) ip(i) = ipiv_(i);
      return ip;
    }

    //==========================================================================
    // Return tpl part of the decomposition  a =  tpl*u (pl = tp *l)
    //==========================================================================
    tab_t pl() const
    {
      //    return trans(p())*l;
      std::size_t mm = nt2::numel(ipiv_); //incorrect
      tab_t ll = l();
      for(size_t i=1; i <= mm; ++i)
        // pp({i, ipiv_(i)}, _) =  pp({ipiv_(i),i}, _)
        {
          tab_t c = ll(ipiv_(i), _);
          ll(ipiv_(i),_) = ll(i,_);
          ll(i,_) = c;
        }
      return ll;

    }

    //==========================================================================
    // Return post-computation status
    //==========================================================================
    nt2_la_int  status() const { return info_; }

    //==========================================================================
    // Reverse conditioning evaluation
    //==========================================================================
    base_t rcond(char c = '1')
    {
      if (c !=  '1' || rc_ == base_t(-1))
        {
          char norm = c;
          base_t anorm = nt2::details::lange(&norm,  &n_,  &n_, lu_.raw(), &ldlu_);
          nt2::details::gecon(&norm, &n_,  lu_.raw(), &ldlu_, &anorm, &rc_, &info_);
       }
      return rc_;
    }

    //==========================================================================
    // system rank
    //==========================================================================
    size_t rank(base_t epsi = nt2::Eps<base_t>()) //provisouare
    {
      //int32_t r = 0;
      base_t thresh = nt2::max(n_, m_)*epsi*nt2::max(nt2::abs(nt2::diag_of(lu_)(_)));
      return  size_t(sum(if_one_else_zero(gt(nt2::diag_of(lu_), thresh))(_)));

      //       for(int i=1; i <= nt2::min(n_, m_); ++i)
      //         {
      //           if(nt2::abs(lu_(i, i)) > thresh) ++r;
      //         }
      //       return r;
      //      nt2::inbtrue(nt2::abs(diag_of(lu_)) > nt2::max(n_, m_)*epsi*nt2::max(abs(diag_of(lu_()))) );
    }

    base_t absdet()
    {
      BOOST_ASSERT_MSG(m_ == n_, "non square matrix in determinant computation");
      return nt2::prod(nt2::abs(nt2::diag_of(lu_)(_)));
    }

    type_t signdet(bool check = true){
      BOOST_ASSERT_MSG(m_ == n_, "non square matrix in determinant computation");
      boost::dispatch::ignore_unused(check); 
      //if (check)     BOOST_ASSERT_MSG(is_real<type_t>::value, "determinant sign is not avalaible for complex matrices");
      //count modulo 2 the number of ipiv_ elements such that ipiv_(i) !=  i
      //return nt2::sum(nt2::sb2b(ipiv_ != cif(numel(ipiv_), 1, meta::as_<itype_t>())))&1 ? Mone<type_t>() : One<type_t>();
      type_t s = One<type_t>();
      for(int i=1; i < numel(ipiv_) ; ++i)
        {
          if (ipiv_(i) !=  i) s = -s;
        }
      return s;
    }

    type_t det(){
      BOOST_ASSERT_MSG(m_ == n_, "non square matrix in determinant computation");
      //     BOOST_ASSERT_MSG(is_real<type_t>::value, "determinant sign is not avalaible for complex matrices");
      //count modulo 2 the number of ipiv_ elements such that ipiv_(i) !=  i
      return  nt2::prod(nt2::diag_of(lu_)(_))*signdet(false);
    }

    type_t absdet(itype_t & exponent)
    {
      BOOST_ASSERT_MSG(m_ ==  n_, "non square matrix in determinant computation");
      // compute e and return m for matrix determinant such that |det| = ldexp(m, e)
      // if no overflow or underflow can occur,  with 0.5 < abs(m) < 1
      // the exponent result is enough to know the order of magnitude of the determinant
      // (between 0.5*2^e and 2^e if the mantissa is non zero)
      // This routine is inspired from linpack http://www.netlib.org/linpack/dgedi.f
      // that use ten power factor instead
      type_t   m1 = One<type_t>();
      exponent = Zero<itype_t>();
        for(size_t i = 1;  i <= n_; ++i)
          {
            itype_t e;
            m1 *=  nt2::abs(nt2::frexp(nt2::abs(lu_(i, i)), e));
            exponent+= e;
          }
      if (is_eqz(m1)){
        exponent = Zero<itype_t>();
      }
      return m1;
    }

    type_t det(itype_t & exponent)
    {
      BOOST_ASSERT_MSG(m_ ==  n_, "non square matrix in determinant computation");
      // compute e and m for matrix determinant such that det = ldexp(m, e)
      // if no overflow or underflow can occur,  with 0.5 < abs(m) < 1
      // the exponent result is enough to know the order of magnitude of the determinant
      // (between 0.5*2^e and 2^e if the mantissa is non zero)
      // This routine is inspired from linpack http://www.netlib.org/linpack/dgedi.f
      // that use ten power factor instead
      type_t   m1 = One<type_t>();
      exponent = Zero<itype_t>();
        for(size_t i = 1;  i <= n_; ++i)
          {
            itype_t e;
            m1 *=  nt2::frexp(nt2::abs(lu_(i, i)), e);
            exponent+= e;
          }
      if (is_eqz(m1)){
        exponent = Zero<itype_t>();
      }
      return m1*signdet(false);
    }

     //==========================================================================
    // Solver interface
    //==========================================================================
    template<class XPR> result_type solve(const XPR& b )
    {
      result_type bb = b;
      inplace_solve(bb);
      return bb;
    }

    //==========================================================================
    // inverse matrix: DO NOT USE THAT TO SOLVE A SYSTEM
    //==========================================================================
    tab_t inv()
    {
      rc_ = rcond();
      tab_t i = lu_;

      NT2_WARNING ( (rc_ >= nt2::Eps<base_t>())
                  , "Matrix is close to singular or badly scaled."
                    " Results may be inaccurate."
                  );

      nt2::details::getri(&n_, i.raw(), &ldlu_, ipiv_.raw(), &info_, w_);
      return i;
    }

    template<class Xpr> void inplace_solve(Xpr& b )
    {
      BOOST_ASSERT_MSG(issquare(a_), "matrix must be square to use the lu solver");
      nt2_la_int nrhs = nt2::size(b, 2);
      nt2_la_int ldb  = b.leading_size();
      tab_t x(b);
      nt2_la_int ldx  = x.leading_size();
      btab_t ferr(of_size(nrhs, 1)), berr(of_size(nrhs, 1));
      btab_t r_(of_size(n_, 1)), c_(of_size(n_, 1));
      char equed = 'N';
      nt2::details::gesvx(nt2::details::lapack_option('F'),
                          nt2::details::lapack_option('N'),
                          &n_, &nrhs,
                          a_.raw(), &ldlu_,
                          lu_.raw(), &ldlu_,
                          ipiv_.raw(),
                          &equed,
                          r_.raw(),
                          c_.raw(),
                          b.raw(), &ldb,
                          x.raw(), &ldx,
                          &rc_,
                          ferr.raw(),
                          berr.raw(),
                          &info_,
                          w_);
      b = x;
    }

  private:
    data_t                            a_;
    tab_t                            lu_;
    nt2_la_int                     m_,n_;
    nt2_la_int                     ldlu_;
    ibuf_t                 ipiv_;
    base_t                   rc_;
    nt2_la_int             info_;
    workspace_t               w_;
    //    template < class T, class XPR1, class XPR2 > XPR2 cast(const XPR1& a)
    //     {
    //       typedef typename XPR1::index_type index_t; 
    //       table<T, index_t> b;
    //       for(int i=nt2::first_index<0>(a); i < nt2::first_index<0>(a)+numel(a); ++i)
    //         {
    //           b(i) = a(i); 
    //         }
    //       return b; 
    //     }
  };
} }

#endif
