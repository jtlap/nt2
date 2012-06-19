/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_EXPM_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_EXPM_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/expm.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/norm.hpp>
#include <vector>

namespace nt2{ namespace ext {
  namespace details
  {
    template < class T > struct expm_helper
    {
      typedef table < T >       tab_t;
      typedef table < size_t > itab_t;
      static const itab_t& m_vals(const double&) {
        static const size_t m_vals_[] = {3, 5, 7, 9, 13}; 
        static const itab_t v( of_size(5, 1), &m_vals_[0], &m_vals_[0]+5);
        return v; 
      }
      static const itab_t& m_vals(const float&) {
        static const size_t m_vals_[] = {3, 5, 7};
        static const itab_t v( of_size(3, 1), &m_vals_[0], &m_vals_[0]+3);
        return v; 
      }
      static const tab_t& theta(const double&){
        static const double theta_[] = {
          1.495585217958292e-002,//  m_vals = 3
          2.539398330063230e-001,//  m_vals = 5
          9.504178996162932e-001,//  m_vals = 7
          2.097847961257068e+000,//  m_vals = 9
          5.371920351148152e+000 //  m_vals = 13 
        }; 
        static const tab_t v( of_size(5, 1),&theta_[0], &theta_[0]+5);
        return v; 
      }
      static const tab_t& theta(const float&){
        static const float theta_[] = {
          4.258730016922831e-001f, //m_vals = 3
          1.880152677804762e+000f, //m_vals = 5
          3.925724783138660e+000f  //m_vals = 7
        }; 
        static const tab_t v( of_size(3, 1), &theta_[0], &theta_[0]+3);
        return v; 
      }
      
      static tab_t 
      getpadecoefficients(const size_t & m)
      {
        //  getpadecoefficients coefficients of numerator p of pade approximant
        //     c = getpadecoefficients returns coefficients of numerator
        //     of [m/m] pade approximant, where m = 3,5,7,9,13.
        const T m3[] = {120, 60, 12, 1};
        const T m5[] = {30240, 15120, 3360, 420, 30, 1};
        const T m7[] = {17297280, 8648640, 1995840, 277200, 25200, 1512, 56, 1};
        const T m9[] = {17643225600, 8821612800, 2075673600, 302702400, 30270240, 
                        2162160, 110880, 3960, 90, 1};
        const T m13[] = {64764752532480000, 32382376266240000, 7771770303897600, 
                         1187353796428800,  129060195264000,   10559470521600,
                         670442572800,      33522128640,       1323241920, 
                         40840800,          960960,            16380,  182,  1}; 
        static tab_t v;

        switch (m)
          {
          case 3: v = tab_t(of_size(4, 1), &m3[0], &m3[0]+4); return v;  
          case 5: v = tab_t(of_size(6, 1), &m5[0], &m5[0]+6); return v;  
          case 7: v = tab_t(of_size(8, 1), &m7[0], &m7[0]+8); return v;  
          case 9: v = tab_t(of_size(10, 1), &m9[0], &m9[0]+10); return v;  
          case 13:v = tab_t(of_size(14, 1), &m13[0], &m13[0]+14); return v;  
          }
        v = nt2::zeros(0, 1, meta::as_<T>()); return v; 
      }
      
    };
    
    template < class xpr > table<typename xpr::value_type>  
    padeapproximantofdegree(const xpr & a, const size_t & m)
    {
      //  padeapproximantofdegree  pade approximant to exponential.
      //     f = padeapproximantofdegree(m) is the degree m diagonal
      //     pade approximant to exp(a), where m = 3, 5, 7, 9 or 13.
      //     series are evaluated in decreasing order of powers, which is
      //     in approx. increasing order of maximum norms of the terms.
      
      typedef typename xpr::value_type                      value_type;
      typedef typename meta::as_real<value_type>::type          base_t; 
      typedef expm_helper<base_t>                                  h_t; 
      typedef table <value_type>                                 tab_t; 
      
      size_t n = nt2::length(a);
      tab_t  c = h_t::getpadecoefficients(m);
      std::vector<tab_t> apowers(m/2+1);
      // evaluate pade approximant.
      tab_t  u = nt2::zeros(n, n, meta::as_<value_type>());
      tab_t  v = u, u1;
      switch (m)
        {
        case 3:
        case 5:
        case 7:
        case 9:  
          apowers[0] = nt2::eye(n, meta::as_<value_type>());
          apowers[1] = nt2::mtimes(a, a);
          for (size_t j = 2; j < m/2+1; j++)
            {
              apowers[j] = nt2::mtimes(apowers[j-1], apowers[1]);
            }
          
          for(ptrdiff_t j=m+1; j >= 2 ; j-= 2)
            {
              u = u+c(j)*apowers[j/2-1]; 
            }
          u1 = mtimes(a, u); u =  u1; // will be suppressed with proper mtimes
          for(ptrdiff_t j=m; j >= 1 ; j-= 2)
            {
              v = v+c(j)*apowers[(j+1)/2-1]; 
            }
          break; 
        case 13:
          // for optimal evaluation need different formula for m >= 12.
          tab_t a2 = nt2::mtimes(a, a);
          tab_t a4 = nt2::mtimes(a2, a2);
          tab_t a6 = nt2::mtimes(a2, a4);
          u = mtimes(a, (mtimes(a6,(c(14)*a6 + c(12)*a4 + c(10)*a2))+
                         c(8)*a6 + c(6)*a4 + c(4)*a2 + c(2)*eye(n, n, meta::as_<value_type>() )));       
          v = mtimes(a6,c(13)*a6 + c(11)*a4 + c(9)*a2) 
            + c(7)*a6 + c(5)*a4 + c(3)*a2 + c(1)*eye(n,n,meta::as_<value_type>());
        }
      tab_t f = nt2::linsolve((-u+v), (u+v));
      return f;
    }
  }
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    typedef table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef nt2::table<value_type >                   tab_t;
      typedef typename meta::as_real<value_type>::type base_t;
      typedef typename meta::as_integer<base_t>::type ibase_t; 
      typedef nt2::table<base_t >                      btab_t;

      size_t n = length(a0);
      typedef details::expm_helper<base_t>                h_t; 
      typedef typename h_t::itab_t                     itab_t;
      const btab_t theta = h_t::theta(value_type());
      const itab_t m_vals = h_t::m_vals(value_type());
      tab_t a = a0; 
      base_t norma0 = nt2::norm(a0, 1);
      tab_t f; 
      if(norma0 <=  value_type(theta(end_)))// WHY value_type() is necessary ?
        {
          // no scaling and squaring is required.
          for(size_t i = 1;  i <= nt2::numel(m_vals); ++i)
            {
              if (norma0 <= value_type(theta(i)))
                {
                  f = details::padeapproximantofdegree(a, value_type(m_vals(i)));
                  break;
                }
            }
        }
      else
        {
          norma0/= value_type(theta(end_));
          ibase_t s; 
          base_t t = nt2::frexp(norma0, s);
          //       ptrdiff_t s = logb( norma0);
          s -= (t == 0.5); // adjust s if norma0/theta(end) is a power of 2.
          a =  nt2::ldexp(a, -s); 
          f = details::padeapproximantofdegree(a, value_type(m_vals(end_)));
          for(ibase_t i=1; i <= s; ++i)
            {
              tab_t f1 =  mtimes(f, f); // squaring //f1 must be suppressed
              f =  f1; 
            }
        }
      return f; 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm_, tag::cpu_
                            , (A0)
                            , (scalar_<fundamental_<A0> >)
                            )
  {
    typedef typename nt2::meta::as_floating<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::exp(nt2::tofloat(a0)); 
    }
  };  
} }

#endif
