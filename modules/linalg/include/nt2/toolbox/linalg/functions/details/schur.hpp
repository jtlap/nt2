/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_SCHUR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_SCHUR_HPP_INCLUDED

#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
//#include <nt2/toolbox/linalg/details/utility/lower.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/toolbox/linalg/details/lapack/geesx.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/table.hpp>
//#include <iostream>

//  schur  schur decomposition.
//     [u,t] = schur(x) produces a quasitriangular schur matrix t and
//     a unitary matrix u so that x = u*t*u' and u'*u = eye(size(u)).
//     x must be square.
 
//     t = schur(x) returns just the schur matrix t.
 
//     if x is complex, the complex schur form is returned in matrix t.
//     the complex schur form is upper triangular with the eigenvalues
//     of x on the diagonal.
 
//     if x is real, two different decompositions are available.
//     schur(x,'real') has the real eigenvalues on the diagonal and the
//     complex eigenvalues in 2-by-2 blocks on the diagonal.
//     schur(x,'complex') is triangular and is complex if x has complex
//     eigenvalues.  schur(x,'real') is the default.
///////////// TO DO
// The second style must be enforced in nt2 by converting input to complex
// before calling schur
///////////// 
//     see rsf2csf to convert from real to complex schur form.
namespace nt2 {
  namespace details
  {
    template<class T,
             class CPLX = typename nt2::details::is_complex<typename meta::strip<T>::type::value_type >::type>
    struct schur_result
    {
      typedef typename meta::strip<T>::type                   source_t;
      typedef typename source_t::value_type                     type_t;
      typedef typename source_t::index_type                     index_t;
      typedef typename meta::as_real<type_t>::type              base_t;
      typedef typename meta::as_integer<base_t, signed>::type  itype_t;
      typedef T                                                data_t;
      typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
      typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
      typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t;
      typedef nt2::details::workspace<type_t>              workspace_t;
      typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
      typedef nt2::table<type_t,index_t>                   result_type;
      
      
      template<class Input>
      schur_result ( Input& xpr
                     , char jobvs/* = 'V'*/
                     , char sort /* = 'N'*/
                     , char sense/* = 'N'*/)
        : jobvs_(jobvs)
        , sort_(sort)
        , sense_(sense)
        , a_(xpr)
        , aa_(xpr)
        , n_(nt2::height(xpr))
        , lda_(a_.leading_size())
      {
        BOOST_ASSERT_MSG(is_square(aa_), "Error using schur. Matrix must be square."); 
        jobvs_ = (sense_ == 'E' || sense_ == 'B') ? 'V':jobvs_;
        sort_ = (sense_ == 'E') ? 'S' : sort_; 
        ldvs_ = (jobvs_ == 'N') ? n_ : 1;
        w_.resize(nt2::of_size(n_, 1));
        vs_.resize(of_size(ldvs_, ldvs_));
        ldvs_ = vs_.leading_size(); 
        nt2::details::geesx(&jobvs_, &sort_, &nt2::details::selectall , &sense_, &n_, 
                            aa_.raw(), &lda_, &sdim_, w_.raw(),
                            vs_.raw(), &ldvs_,
                            &rconde_, &rcondv_, 
                            &info_, wrk_);
      }

      schur_result(schur_result const& src)
        : jobvs_(src.jobvs_)
        , sort_(src.sort_)
        , sense_(src.sense_)
        , a_(src.a_)
        , aa_(src.aa_)
        , n_(src.n_)
        , lda_(src.lda_)
    {}
    

      
      result_type values() const { return aa_; }
      result_type     w () const { return from_diag(w);}
      result_type     t () const { return aa_;     }
      result_type     z () const 
      {
        BOOST_ASSERT_MSG( (jobvs_ == 'V'), "choose jobvs == 'V' to compute z"); 
        return vs_;
      }
      nt2_la_int  status() const   { return info_;   }
      base_t      rconde()
      {
        BOOST_ASSERT_MSG( (sense_ ==  'E' || sense_ ==  'B'), "choose sense in {'E', 'B'} to compute rconde"); 
        return rconde_; 
      }
      base_t      rcondv()
      {
        BOOST_ASSERT_MSG( (sense_ ==  'E' || sense_ ==  'B'), "choose sense in {'E', 'B'} to compute rconde"); 
        return rcondv_; 
      }
    private:
      char                 jobvs_, sort_;
      char                        sense_;
      data_t                          a_;
      tab_t                          aa_; 
      nt2_la_int                      n_;
      nt2_la_int                    lda_; 
      nt2_la_int                   ldvs_;
      nt2_la_int                   sdim_; 
      base_t            rcondv_, rconde_;
      tab_t                          vs_; 
      tab_t                           w_; 
      nt2_la_int                   info_; 
      workspace_t                   wrk_;
    }; 

    template<class T>
    struct schur_result < T, boost::mpl::false_ >
    {
      typedef typename meta::strip<T>::type                   source_t;
      typedef typename source_t::value_type                     type_t;
      typedef typename source_t::index_type                    index_t;
      typedef typename meta::as_real<type_t>::type              base_t;
      typedef typename meta::as_integer<base_t, signed>::type  itype_t;
      typedef T                                                 data_t;
      typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
      typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
      typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t;
      typedef nt2::details::workspace<type_t>              workspace_t;
      typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
      typedef nt2::table<type_t,index_t>                   result_type;
      
      
      template<class Input>
      schur_result ( Input& xpr
                     , char jobvs/* = 'V'*/
                     , char sort /* = 'N'*/
                     , char sense/* = 'N'*/)
        : jobvs_(jobvs)
        , sort_(sort)
        , sense_(sense)
        , a_(xpr)
        , aa_(xpr)
        , n_(nt2::height(xpr))
        , lda_(a_.leading_size())
      {
        BOOST_ASSERT_MSG(is_square(aa_), "Error using schur. Matrix must be square."); 
        jobvs_ = (sense_ == 'E' || sense_ == 'B') ? 'V':jobvs_;
        sort_ = (sense_ == 'E') ? 'S' : sort_; 
        ldvs_ = (jobvs_ == 'V') ? n_ : 1;
        wr_.resize(nt2::of_size(n_, 1));
        wi_.resize(nt2::of_size(n_, 1)); 
        vs_.resize(of_size(ldvs_, ldvs_));
        ldvs_ = vs_.leading_size(); 
        nt2::details::geesx(&jobvs_, &sort_, &nt2::details::selectall2 , &sense_, &n_, 
                            aa_.raw(), &lda_, &sdim_, wr_.raw(), wi_.raw(), 
                            vs_.raw(), &ldvs_,
                            &rconde_, &rcondv_, 
                            &info_, wrk_);
      }
     schur_result(schur_result const& src)
        : jobvs_(src.jobvs_)
        , sort_(src.sort_)
        , sense_(src.sense_)
        , a_(src.a_)
        , aa_(src.aa_)
        , n_(src.n_)
        , lda_(src.lda_)
    {}
    
      result_type values() const { return aa_; }
      result_type     t () const { return aa_;     }
      result_type     z () const 
      {
        BOOST_ASSERT_MSG( (jobvs_ == 'V'), "choose jobvs == 'V' to compute z"); 
        return vs_;
      }
      nt2_la_int  status() const   { return info_;   }
      base_t      rconde()
      {
        BOOST_ASSERT_MSG( (sense_ ==  'E' || sense_ ==  'B'), "choose sense in {'E', 'B'} to compute rconde"); 
        return rconde_; 
      }
      base_t      rcondv()
      {
        BOOST_ASSERT_MSG( (sense_ ==  'E' || sense_ ==  'B'), "choose sense in {'E', 'B'} to compute rconde"); 
        return rcondv_; 
      }
    private:
      char                 jobvs_, sort_;
      char                        sense_;
      data_t                          a_;
      tab_t                          aa_; 
      nt2_la_int                      n_;
      nt2_la_int                    lda_; 
      nt2_la_int                   ldvs_;
      nt2_la_int                   sdim_; 
      base_t            rcondv_, rconde_;
      tab_t                          vs_; 
      tab_t                     wr_, wi_;  
      nt2_la_int                   info_; 
      workspace_t                   wrk_;
    }; 
  }
}
#endif
