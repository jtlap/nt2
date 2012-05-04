/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_BALANCE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_BALANCE_HPP_INCLUDED
#include <nt2/toolbox/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/toolbox/linalg/details/lapack/gebal.hpp>
#include <nt2/table.hpp>
//     [t,b] = balance(a) finds a similarity transformation t such
//     that b = t\a*t has, as nearly as possible, approximately equal
//     row and column norms.  t is a permutation of a diagonal matrix
//     whose elements are integer powers of two so that the balancing
//     doesn't introduce any round-off error.
 
//     b = balance(a) returns the balanced matrix b.
 
//     [s,p,b] = balance(a) returns the scaling vector s and the
//     permutation vector p separately.  the transformation t and 
//     balanced matrix b are obtained from a,s,p by 
//        t(:,p) = diag(s),    b(p,p) = diag(1./s)*a*diag(s).
    
//     to scale a without permuting its rows and columns, use
//     the syntax balance(a,'noperm').
 
namespace nt2 { namespace details
{
  template<class T> struct balance_result
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
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;
    typedef nt2::table<base_t,index_t>                  bresult_type;
    typedef nt2::table<itab_t,index_t>                  iresult_type;
    //must be dry I think

    template<class Input>
    balance_result ( Input& xpr, char job = 'B')
      : job_(job)
      , a_(xpr)
      , aa_(xpr)
      , n_( nt2::height(a_)  )
      , lda_( a_.leading_size() )
      , ilo_(0)
      , ihi_(0)
      , scale_(of_size(1, n_))
      , ipiv_(of_size(1, n_))
      , info_(0)
    {
      BOOST_ASSERT_MSG(issquare(aa_),
                        "matrix to balance must be square");
      nt2::details::gebal(&job_, &n_, aa_.raw(), &lda_,
                          &ilo_, &ihi_, scale_.raw(),
                          &info_);
    // I have not understood yet how to compute properly ipiv_ from original scale_    
      disp("scale ", scale_);
      disp("low   ",_(1,  ilo_-1));
      disp("high  ", _(ihi_+1, n_));
      if (job_ != 'N')
        {
          ipiv_ = _(One<itype_t>(), n_); 
          for(int i=1; i < ilo_; ++i) ipiv_(i) = toint(scale_(i)); 
          for(int i=ihi_+1; i <= n_; ++i) ipiv_(i) = toint(scale_(i)); 
          scale_(1, _(1,  ilo_-1)) = ones(1, ilo_-1, meta::as_<base_t>());
          scale_(1, _(ihi_+1, n_)) = ones(1, n_-ihi_-1, meta::as_<base_t>());  
        }
    }
    balance_result& operator=(balance_result const& src)
    {
      job_    = src.job_;
      a_      = src.a_;
      aa_     = src.aa_;
      n_      = src.n_;
      lda_    = src.lda_;
      ilo_    = src.ilo_; 
      ihi_    = src.ihi_;
      scale_  = src.scale_;
      ipiv_   = src.ipiv_; 
      info_   = src.info_;
      return *this;
    }
    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type values() const { return aa_; }

    //==========================================================================
    // Return scale part as a vector
    //==========================================================================
    bresult_type scale() const
    {
      BOOST_ASSERT_MSG(job_ != 'N', "please call balance with job = 'P', 'S' or 'B'");
      return scale_;
    }
    //==========================================================================
    // Return permute part as a vector of indices
    //==========================================================================
    itab_t ipiv() const
    {
      BOOST_ASSERT_MSG(job_ != 'N', "please call balance with jobu = 'P', 'S' or 'B'");
      return ipiv_;
    }
    //I DO NOT UNDERSTAND YET HOW TO GET PERM FROM SCALE !?
    //     //==========================================================================
    //     // Return permute part as matrix
    //     //==========================================================================
    //     bresult_type p() const
    //     {
    //       BOOST_ASSERT_MSG(job_ != 'N', "please call balance with job = 'P', 'S' or 'B'");
    //       btab_t p =  eye(n_, meta::as_<base_t>());
    //       for(int i=n_; i > ihi_; i++) p(ipiv(i), _) = p(i, _);
    //       for(int i=1;  i < ilo_; i++) p(ipiv(i), _) = p(i, _);
    //     }
    //     //==========================================================================
    //     // Return t transform
    //     //==========================================================================
    //     result_type t() const
    //     {
    //       BOOST_ASSERT_MSG(job_ != 'N', "please call balance with job = 'P', 'S' or 'B'");
    //       tab_t tt_ = aa_;
    //       tt_(_(ilo_, ihi_), _) = from_diag(scale_(1, _(ilo_, ihi_)));
    //       return tt_; 
    //     }
    
    //==========================================================================
    // Return lapack status
    //==========================================================================
    nt2_la_int  status()         const { return info_; }
    nt2_la_int  ilo   ()         const { return ilo_;  }
    nt2_la_int  ihi   ()         const { return ihi_;  }  
   private: 
    char                           job_;
    data_t                           a_;
    tab_t                           aa_; 
    nt2_la_int                       n_;
    nt2_la_int                     lda_;
    nt2_la_int               ilo_, ihi_; 
    btab_t                       scale_;
    itab_t                        ipiv_; 
    nt2_la_int                    info_;
  };
} }



#endif

// /////////////////////////////////////////////////////////////////////////////
// End of balance.hpp
// /////////////////////////////////////////////////////////////////////////////
