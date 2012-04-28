/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/lapack/hsev.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/issymetric.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/table.hpp>
////////////////////////////////////////////////////////////////////////////////
// Construct the class choosing the computation model :
// float,  double or complex < float >  or complex < double > and a matrix or
// matrix expression as:
//                     symeig_result<table <double> >s(1.0/(cif(5)+rif(5)-1)); 
// or
//                     matrix < double >  a(1.0/(cif(5)+rif(5)-1));
//                     symeig<table < double > >s(a)
//
// then you can extract v, w and using the accessors v(), w() to
// obtain 2 matrices such that up to rounding errors :
//                     s.v()*a = s.v()*s.w()
// is the original matrix
// If you just want the eigenvalues but not the eigenvectors call s(a, 'N')
// Take care that the input expression is supposed to be hermitian
// (symetric if real),  but that by default the upper part of the expression
// is considered an even a not "really" symetric input will be taken as such.
//
// Use s(a, 'N', 'L') or  s(a, 'V', 'L') to use the lower part.
////////////////////////////////////////////////////////////////////////////////


namespace nt2 { namespace details
{
  template<class T> struct symeig_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
    //    typedef typename meta::as_dry<type_t>::type                dry_t;
    //    typedef nt2::table<dry_t, nt2::matlab_index_>             dtab_t; 
    typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t; 
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;
    
    template<class Input>
    symeig_result ( Input& xpr, const char & jobz = 'V', const char & uplo = 'U')
      : jobz_(?jobz == 'V' ? 'V':'N')
      , uplo_(?uplo == 'L' ? 'L':'U')
      , a_(xpr)
      , aa_(xpr)
      , n_( nt2::height(xpr)  )
      , w_(of_size(1, n_))       
      , lda_( aa_.leading_size() )
      , info_(0)
    {
      BOOST_ASSERT_MSG(nt2::issymetric(a_), "input must be a symetric matrix"); 
      nt2::details::hsev(&jobz_, &uplo_, &n_,
                         aa_.raw(), &lda_, w_.raw(),
                         &info_, wrk_);
    }

    symeig_result& operator=(symeig_result const& src)
    {
      a_      = src.a_; 
      aa_     = src.aa_;
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
    
    // /////////////////////////////////////////////////////////////////////////////
    // return eigen vectors
    // /////////////////////////////////////////////////////////////////////////////
    tab_t v ()
    {
      BOOST_ASSERT_MSG(jobz_ == 'V', "use jobz =  'V' to get eigenvectors"); 
      return aa_;
    }
    
    // /////////////////////////////////////////////////////////////////////////////
    // return eigen values (as vector of reals)
    // /////////////////////////////////////////////////////////////////////////////
    btab_t      eigen()          { return w_;      }
    // /////////////////////////////////////////////////////////////////////////////
    // return eigen values (as diagonal matrix of reals)
    // /////////////////////////////////////////////////////////////////////////////
    btab_t      w ()         { return from_diag(w_);}//TODO
    
    //     // /////////////////////////////////////////////////////////////////////////////
    //     // return eigen values (as vector of dry)
    //     // /////////////////////////////////////////////////////////////////////////////
    //     dtab_t      deigen()          { return w_;      }
    //     // /////////////////////////////////////////////////////////////////////////////
    //     // return eigen values (as diagonal matrix of dry)
    //     // /////////////////////////////////////////////////////////////////////////////
    //     dtab_t      dw ()         { return diag_from(w_);}
    
    nt2_la_int status() const { return info_;   }
    
    // /////////////////////////////////////////////////////////////////////////////
    // return condition number
    // /////////////////////////////////////////////////////////////////////////////
    base_t     cond() const {return  nt2::abs(w_(1)/w_(numel(w_))); }
    // /////////////////////////////////////////////////////////////////////////////
    // return rank up to epsi
    // /////////////////////////////////////////////////////////////////////////////
    size_t     rank(base_t epsi = nt2::Eps<base_t>())
    {
      int32_t r = 0;
      btab_t m = nt2::max(nt2::abs(w_)); 
      base_t thresh = n_*epsi*m(1); 
      for(int i=1; i <= n_; ++i)
        {
          if(nt2::abs(w_(i)) > thresh) ++r; 
        }
      return r; 
    }
    
  private:
    template < class S>
    static btab_t from_diag(const S& w)
    {
      btab_t m = nt2::zeros(numel(w), numel(w), meta::as_<type_t>());
      for (int i = 1; i <= numel(w); ++i) m(i, i) = w(i);
      return m;
    }
    char     jobz_, uplo_;
    data_t             a_;
    tab_t             aa_; 
    nt2_la_int         n_;
    btab_t             w_; 
    nt2_la_int       lda_; 
    nt2_la_int      info_; 
    workspace_t      wrk_;
  }; 
} }


#endif
