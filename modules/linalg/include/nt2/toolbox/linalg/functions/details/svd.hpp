/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SVD_HPP_INCLUDED

#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/zeros.hpp>
//#include <nt2/include/functions/trans.hpp> //TODO
#include <nt2/include/constants/zero.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/lapack/gesvd.hpp>
#include <iostream>
// TODO:
// these are the kind of syntaxes to be enforced by nt2::chol
//  svd    Singular value decomposition.
//     [u,s,v] = svd(x) produces a diagonal matrix s, of the same 
//     dimension as x and with nonnegative diagonal elements in
//     decreasing order, and unitary matrices u and v so that
//     x = u*s*v'.
// -> [u w v ]

//     s = svd(x) returns a vector containing the singular values.
 
//     [u,s,v] = svd(x,0) produces the "economy size"
//     decomposition. if x is m-by-n with m > n, then only the
//     first n columns of u are computed and s is n-by-n.
//     for m <= n, svd(x,0) is equivalent to svd(x).
// -> [u w v ] jobu ==  'o', jobvt ==  'a'
 
//     [u,s,v] = svd(x,'econ') also produces the "economy size"
//     decomposition. if x is m-by-n with m >= n, then it is
//     equivalent to svd(x,0). for m < n, only the first m columns 
//     of v are computed and s is m-by-m.
// -> [u w v ] jobu ==  'a' jobvt ==  'o'
 
////////////////////////////////////////////////////////////////////////////////////////
// The class provides:
// constructor from an expression or matrix a
//
// accesors to u, v, vt and singular also w as a vector
// u returns the left singular vectors
// v returns the right singular vectors
// vt returns the transpose of the right singular vectors
// w returns the diagonal matrix of the singular values
// singular returns the vector of the singular values
// we have u*w*vt = a

/////////////////////////////////////////////////// 
//
// the class allow to compute
//
// status the plu status from lapack
//
// rank the matrix rank up to epsi
//
//
// Two solvers
// solve and inplace_solve
//
// a matrix pseudo inversion penrose pseudo inverse
// pinv
// if z =  a.pinv(),  one has z*a*z = z and a*z*a = a
//
// null returns orthogonal basis of the kernel of the input up to epsi
// orth returns orthogonal basis of the image  of the input up to epsi
// zerosolve returns the a norm one  vector such that ||a*x|| is minimal
// (zero if a is singular)
//
namespace nt2 { namespace details
{
  template<class T> struct svd_result
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
    svd_result ( Input& xpr, char jobu = 'A', char jobvt = 'A')
      : jobu_(jobu)
      , jobvt_(jobvt)
      , a_(xpr)
      , aa_(xpr)
      , m_( nt2::height(xpr) )
      , n_( nt2::width(xpr)  )
      , lda_( a_.leading_size() )
      , info_(0)
    {
      BOOST_ASSERT_MSG((jobvt_ != 'O' || jobu_ != 'O'),
                        "jobu and jobvt cannot be 'O' simultaneously");
      ldu_  = (jobu_== 'N') ? 1 : m_;
      ucol_ = (jobu_== 'S'||jobu_== 'O') ? nt2::min(n_, m_) : ((jobu_== 'N') ? 1 : m_); 
      
      vtcol_  = (jobu_== 'N') ? 1 : n_;
      ldvt_   = (jobu_== 'S'||jobu_== 'O') ? nt2::min(n_, m_) : ((jobu_== 'N') ? 1 : n_);
      u_.resize(of_size(ldu_, ucol_));
      ldu_ = u_.leading_size();
      vt_.resize(of_size(ldvt_, vtcol_));
      ldvt_ = vt_.leading_size();
      w_.resize(of_size(nt2::min(n_, m_), 1));
      nt2::details::gesvd(&jobu_, &jobvt_, &m_, &n_, aa_.raw(), &lda_,
                          w_.raw(), u_.raw(), &ldu_,
                          vt_.raw(), &ldvt_, &info_, wrk_);
    }

    svd_result& operator=(svd_result const& src)
    {
      jobu_   = src.jobu_;
      jobvt_  = src.jobvt_;
      a_      = src.a_;
      aa_     = src.aa_;
      m_      = src.m_;
      n_      = src.n_;
      lda_    = src.lda_;
      info_   = src.info_;
      wrk_    = src.wrk_;
      return *this;
    }
    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type values() const { return aa_; }

    //==========================================================================
    // Return u part
    //==========================================================================
    result_type u() const
    {
      BOOST_ASSERT_MSG(jobu_ != 'N', "please call svd with jobu = 'A', 'S' or 'O'");
      if (jobu_ == 'O')
        return expand(aa_, min(m_, n_), n_);
      else
        return u_;
    }

    //==========================================================================
    // Return v part
    //==========================================================================
    result_type v() const {
      BOOST_ASSERT_MSG(jobvt_ != 'N', "please call svd with jobvt= 'A', 'S' or 'O'");
      if (jobvt_ == 'O')
        return trans(expand(aa_, min(m_, n_), n_));
      else
        return trans(vt_);
    }

    //==========================================================================
    // Return vt part
    //==========================================================================
    result_type vt() const {
      BOOST_ASSERT_MSG(jobvt_ != 'N', "please call svd wit jobz = 'A', 'S' or 'O'");
       if (jobvt_ == 'O')
        return expand(aa_, min(m_, n_), n_);
      else
        return vt_;
    }

    //==========================================================================
    // Return singular values as a vector
    //==========================================================================
    btab_t      singular()const { return w_; }

    //==========================================================================
    // Return singular values as a diagonal matrix
    //==========================================================================
    btab_t      w()              const
    {
      return nt2::expand(from_diag(w_), ucol_, height(vt_));
    }

    //==========================================================================
    // Return lapack status
    //==========================================================================
    nt2_la_int  status()         const { return info_; }

    //==========================================================================
    // Return matrix condition number
    //==========================================================================
    base_t     cond()       const { return  w_(1)/w_(nt2::min(m_, n_)); }

    //==========================================================================
    // Return matrix rank up to epsi
    //==========================================================================
     size_t      rank(base_t epsi = -1) const
    {
      epsi =  (epsi < 0) ?  nt2::max(n_, m_)*nt2::eps(w_(1)): epsi;
      size_t r = 0; 
      for(int i=1; i <= numel(w_); ++i)
        {
          if (w_(i) > epsi)
            ++r;
          else
            return r; 
        }
      return r; 
       //     return sum(sb2b(gt(w_, epsi))); //TO DO
    }

    //==========================================================================
    // Solver interface
    // The default solver is not in place
    //==========================================================================
    template<class XPR> void inplace_solve(XPR& b ) const
    {
      b = solve(b);
    }
    template<class XPR> result_type solve(const XPR & b,
                                          base_t epsi = Mone<base_t>() )const{
      epsi =  epsi < 0 ? nt2::eps(w_(1)) : epsi;
      //      tab_t w1 = if_else( (w > epsi), nt2::rec(w), Zero<base_t>()); //TODO
      tab_t w1(w.extent());
      for(int i=1; i <= numel(w1) ; ++i)
        {
          w1(i) = w(i) > epsi ? nt2::rec(w) : Zero<base_t>();
        }
      //      return (nt2::trans(vt)*(nt2::from_diag(w1)*nt2::trans(u)))*b; //TODO
      return prodMM(prodtMM(vt_, prodMtM(from_diag(w1), u_)), b);
      }

    //==========================================================================
    // null space basis up to epsi
    //==========================================================================
      tab_t null(base_t epsi = -1 )const
      {
        epsi =  epsi < 0 ? nt2::eps(w_(1)) : epsi;
        int j = numel(w_);
        for(; (j > 0) && (w_(j)<= epsi); j--);
        j++;
        return nt2::fliplr(trans(vt()(_(j, last_index<1>(vt_)), _)));//TODO trans
      }

    //==========================================================================
    // image space basis up to epsi
    //==========================================================================
      tab_t orth(base_t epsi =  -1)const
      {
        int32_t r = rank(epsi); 
        return u()(_, _(1, r));
      }

      tab_t zerosolve()const
      {
        return trans(vt()(last_index<1>(vt_), _));
      }

      tab_t pinv(base_t epsi = -1 )const
      {
        epsi = epsi < 0 ? nt2::eps(w(1)) : epsi;
        tab_t w1(w.extent());
        for(int i=1; i <= numel(w1) ; ++i)
        {
          w1(i) = w_(i) > length(a_)*epsi ? nt2::rec(w) : Zero<base_t>();
        }
        //        w1 = if_else( (w1 > length(a)*epsi), rec(w1), Zero<base_t>());
        // return (nt2::trans(vt_)*(nt2::diag(w1)*nt2::trans(u_)));
        return prodtMM(vt_, prodMtM(diag_from(w1), u_));
      }

  private:
    char                           jobu_;
    char                          jobvt_; 
    data_t                            a_;
    tab_t                            aa_; 
    tab_t                             u_;
    tab_t                            vt_;
    tab_t                             w_;
    nt2_la_int                     m_,n_;
    nt2_la_int                      lda_;
    nt2_la_int                      ldu_;
    nt2_la_int                     ldvt_;
    nt2_la_int                     ucol_;
    nt2_la_int                    vtcol_;
    nt2_la_int                     info_;
    workspace_t                     wrk_;


    template < class S>
    static tab_t diag_of(const S& a)
    {
      tab_t d(of_size(nt2::min(width(a), height(a)), 1));
      for (int i = 1; i <= nt2::min(width(a), height(a)); ++i) d(i) = a(i, i);
      return d;
    }
    template < class S>
    static btab_t from_diag(const S& w)
    {
      tab_t m = nt2::zeros(numel(w), numel(w), meta::as_<type_t>());
      for (int i = 1; i <= numel(w); ++i) m(i, i) = w(i);
      return m;
    }
    template < class S>
    static tab_t trans(const S& a)
    {
      tab_t ta(of_size(width(a), height(a)));
      for (int i = 1; i <= height(a); ++i)
        for (int j = 1; j <= width(a); ++j) ta(j, i) = a(i, j);
      return ta;
    }

  };
} }

#endif
