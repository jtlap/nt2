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
//#include <nt2/include/functions/trans.hpp> //TODO
#include <nt2/include/constants/zero.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/lapack/gesvd.hpp>
#include <iostream>



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
    svd_result ( Input& xpr, char jobz = 'A')
      : jobz_(jobz)
      , a_(xpr)
      , aa_(xpr)
      , m_( nt2::height(xpr) )
      , n_( nt2::width(xpr)  )
      , lda_( a_.leading_size() )
      , info_(0)
    {
      allocate();
      init();
    }

    svd_result& operator=(svd_result const& src)
    {
      jobz_   = src.jobz_;
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
    result_type values() const { return a_; }

    //==========================================================================
    // Return u part
    //==========================================================================
    result_type u() const
    {
      BOOST_ASSERT_MSG(jobz_ != 'N', "please call svd wit jobz = 'A', 'S' or 'O'");
      return u_;
    }

    //==========================================================================
    // Return vt part
    //==========================================================================
    result_type vt() const {
      BOOST_ASSERT_MSG(jobz_ != 'N', "please call svd wit jobz = 'A', 'S' or 'O'");
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
    base_t     cond()       const { return  w_(1)/w(nt2::min(m_, n_)); }

    //==========================================================================
    // Return matrix rank up to epsi
    //==========================================================================
     size_t      rank(base_t epsi = -1) const
    {
      epsi =  (is_ltz(epsi)) ?  nt2::max(n_, m_)*nt2::eps(w_(1)): epsi;
      return sum(sb2b(gt(w, epsi)));
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
        return nt2::fliplr(trans(vt_(_(j, last_index<1>(vt_)), _)));//TODO
      }

    //==========================================================================
    // image space basis up to epsi
    //==========================================================================
      tab_t orth(base_t epsi =  -1)const
      {
        return u(_, nt2::_(1, rank(epsi)));
      }

      tab_t zerosolve()const
      {
        return trans(vt(vt.last_index<1>(), _));
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
    char                           jobz_;
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

    inline void allocate()
    {
      switch (jobz_)
        {
        case 'A':
          ldu_ = m_;  ucol_ = m_;
          ldvt_ = n_; vtcol_ = n_;
          break;
        case 'S':
          ldu_ = m_;  ucol_ = nt2::min(n_, m_);
          ldvt_ = n_; vtcol_ = n_;
          break;
        case 'O':
          ldu_ = m_;  ucol_ = nt2::min(n_, m_);
          ldvt_ = n_; vtcol_ = nt2::min(n_, m_);
          break;
        case 'N':
          ldu_ = 1;  ucol_ = 1;
          ldvt_ = 1; vtcol_ = 1;
          break;
        default :
          break;
        }
      u_.resize(of_size(ldu_, ucol_));
      ldu_ = u_.leading_size();
      vt_.resize(of_size(ldvt_, vtcol_));
      ldvt_ = vt_.leading_size();
      w_.resize(of_size(nt2::max(n_, m_), 1));
    }

    inline void init()
    {
      std::cout << "jobz_ " << jobz_ << std::endl;
      nt2::details::gesvd(&jobz_, &jobz_, &m_, &n_, aa_.raw(), &lda_,
                          w_.raw(), u_.raw(), &ldu_,
                          vt_.raw(), &ldvt_, &info_, wrk_);

      for(size_t i = nt2::min(n_, m_)+1; i<= nt2::numel(w_); ++i) w_(i) = Zero<base_t>();
      //w_(_(nt2::min(n_, m_)+1, nt2::numel(w_))) =  Zero<base_t>();
    }

    template < class S>
    static S diag_of(const S& a)
    {
      S d(of_size(nt2::min(width(a), height(a)), 1));
      for (int i = 1; i <= nt2::min(width(a), height(a)); ++i) d(i) = a(i, i);
      return d;
    }
    template < class S>
    static S from_diag(const S& w)
    {
      S m(of_size(numel(w), numel(w)));
      for (int i = 1; i <= numel(w); ++i) m(i, i) = w(i);
      return m;
    }
    template < class S>
    static S trans(const S& a)
    {
      S ta(of_size(width(a), height(a)));
      for (int i = 1; i <= heigth(a); ++i)
        for (int j = 1; j <= width(a); ++j) ta(j, i) = a(i, j);
      return ta;
    }

  };
} }

#endif
