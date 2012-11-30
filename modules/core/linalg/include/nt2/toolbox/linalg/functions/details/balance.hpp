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
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/toolbox/linalg/details/lapack/gebal.hpp>
#include <nt2/toolbox/linalg/details/lapack/gebak.hpp>
#include <nt2/core/container/table/table.hpp>
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
    typedef nt2::container::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::container::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::container::table<itype_t,nt2::matlab_index_>            itab_t;
    typedef nt2::container::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::container::table<type_t,index_t>                   result_type;
    typedef nt2::container::table<base_t,index_t>                  bresult_type;
    typedef nt2::container::table<itab_t,index_t>                  iresult_type;
    //must be dry I think

    template<class Input>
    balance_result ( Input& xpr, char job/* = 'B'*/)
      : job_(job)
      , a_(xpr)
      , aa_(xpr)
      , ipi_(of_size(0, 0))
      , n_( nt2::height(a_)  )
      , lda_( a_.leading_size() )
      , t_(of_size(n_, n_))
      , invt_(of_size(0, 0))
      , ilo_(0)
      , ihi_(0)
      , scale_(of_size(1, n_))
      , info_(0)
    {
      BOOST_ASSERT_MSG(issquare(aa_),
                       "matrix to balance must be square");
      nt2::details::gebal(&job_, &n_, aa_.raw(), &lda_,
                          &ilo_, &ihi_, scale_.raw(),
                          &info_);
      t_ = nt2::eye(n_, n_, meta::as_<type_t>());
      nt2_la_int ldt = t_.leading_size();
      char side =  'R';
      nt2::details::gebak(&job_, &side, &n_,
                          &ilo_, &ihi_, scale_.raw(),
                          &n_, t_.raw(), &ldt, &info_);
    }

    balance_result& operator=(balance_result const& src)
    {
      job_    = src.job_;
      a_      = src.a_;
      aa_     = src.aa_;
      ipi_    = src.ipi_;
      n_      = src.n_;
      t_      = src.t_;
      invt_   = src.invt_;
      lda_    = src.lda_;
      ilo_    = src.ilo_;
      ihi_    = src.ihi_;
      scale_  = src.scale_;
      info_   = src.info_;
      return *this;
    }
    balance_result(balance_result const& src)
      : job_(src.job_),
        a_(src.a_),
        aa_(src.aa_),
        ipi_(src.ipi_),
        n_(src.n_),
        lda_(src.lda_),
        t_(src.t_),
        invt_(src.invt_),
        ilo_(src.ilo_),
        ihi_(src.ihi_),
        scale_(src.scale_),
        info_(src.info_)
    {}

    //==========================================================================
    // Return raw values
    //==========================================================================
    data_t values() const { return a_; }
    //result_type
    const tab_t & balanced() const { return aa_; }

    //==========================================================================
    // Return scale part as a vector
    // This surely can be done in a more clever way directly from scale_
    //==========================================================================
    typedef typename meta::call < tag::maximum_(btab_t const&, int32_t)>::type                    scale_T0;
    typedef typename meta::call < tag::reshape_(scale_T0 const&, int32_t, nt2_la_int)>::type scale_result;

    scale_result scale() const
    {
      return nt2::reshape(nt2::max(t_, nt2::_(), 2), 1, n_);
    }
    //==========================================================================
    // Return permute part as a vector of indices
    // This surely can be done in a more clever way directly from scale_
    //==========================================================================
    const itab_t& ipiv()
    {
      if (isempty(ipi_))
      {
        ipi_.resize(of_size(1, n_));
        for(int i=1; i <= n_; ++i)
        {
          for(int j=1; j <= n_; ++j)
          {
            if(t_(i, j))
            {
              ipi_(i) = j;
              break;
            }
          }
        }
      }
      return ipi_;
    }
    //==========================================================================
    // Return t transform
    //==========================================================================
    const tab_t& t() const
    {
      return t_;
    }
    const tab_t& invt()
    {
      if (isempty(invt_))
      {
        invt_ = nt2::eye(n_, n_, meta::as_<type_t>());
        nt2_la_int ldt = invt_.leading_size();
        char side =  'L';
        nt2::details::gebak(&job_, &side, &n_,
                              &ilo_, &ihi_, scale_.raw(),
                            &n_, invt_.raw(), &ldt, &info_);
      }
      return invt_;
    }
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
    itab_t                         ipi_;
    nt2_la_int                       n_;
    nt2_la_int                     lda_;
    tab_t                            t_;
    tab_t                         invt_;
    nt2_la_int               ilo_, ihi_;
    btab_t                       scale_;
    nt2_la_int                    info_;
  };
} }



#endif

// /////////////////////////////////////////////////////////////////////////////
// End of balance.hpp
// /////////////////////////////////////////////////////////////////////////////
