//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_LOGM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_LOGM_HPP_INCLUDED
#include <nt2/linalg/functions/logm.hpp>

#include <nt2/core/container/table/table.hpp>

#include <nt2/sdk/complex/meta/is_complex.hpp>


#include <nt2/include/functions/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/twopower.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/horzcat.hpp>


namespace nt2
{
  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logm_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::logm_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                              )
    {
      typedef void                                                    result_type;
      typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
      typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
      typedef typename A0::value_type                                    elt_type;
      typedef typename nt2::meta::as_floating<elt_type>::type          value_type;
      typedef typename meta::as_real<value_type>::type                     r_type;
      typedef typename meta::as_complex<r_type>::type                   cplx_type;
      typedef typename meta::as_integer<r_type>::type                      i_type;
      typedef nt2::table<value_type >                                       tab_t;
      typedef nt2::table<r_type>                                           btab_t;
      typedef table<cplx_type>                                            ctab_t;
      typedef table<i_type>                                                itab_t;
      typedef typename A0::index_type                                  index_type;
      BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1) const
      {
        const In0& a  = boost::proto::child_c<0>(a0);
        const Out0& r  = boost::proto::child_c<0>(a1);
        if(nt2::isscalar(a))
        {
          nt2::table<value_type> aa = a;
          doit1(aa(1), r);
        }
        else
        {
          doit2(a, r);
        }
      }
    private:
      template < class T >
        BOOST_FORCEINLINE static void doit1(const T& a0, Out0& r)
      {
        r =  nt2::log(static_cast<value_type>(a0));
      }
      template < class T >
        BOOST_FORCEINLINE static void doit2(const T& a0, Out0& res)
      {
        //u, t and r are complex arrays
        res.resize(extent(a0));
        ctab_t u, t;
        nt2::tie(u, t) = schur(nt2::complexify(a0),'N'); // t is complex schur form.        result_type e, v;
//        NT2_DISPLAY(t);
        if (isdiagonal(t))
        {
          t = nt2::from_diag(nt2::log(nt2::diag_of(t)));
          BOOST_AUTO_TPL(r, nt2::mtimes(u, nt2::mtimes(t, nt2::trans(nt2::conj(u)))));
          transtype(res, r, typename nt2::meta::is_complex<value_type>::type());
          return;
        }
        else
        {
          ctab_t r = zeros(extent(a0), meta::as_<cplx_type>()); //is it necessary ?
          r_type delta = 0.1;
          itab_t  ord(nt2::of_size(2u, nt2::size(a0,1)));
          blocking(diag_of(t),delta, ord);
//          NT2_DISPLAY(ord);
          uint32_t lord = nt2::size(ord, 2);
          itab_t terms(nt2::of_size(lord, 1));
          ctab_t ca0 = a0;

           for(uint32_t col=1; col <= lord ; ++col)
           {
             BOOST_AUTO_TPL(j, nt2::_(ord(1, col), ord(2, col)));
//              NT2_DISPLAY(j);
//              NT2_DISPLAY(a0(j, j));
             uint32_t maxsqrt = 100;
             itab_t terms(nt2::of_size(1, lord));
             uint32_t nj =  length(j);
             ctab_t rj(nt2::of_size(nj, nj));
//              NT2_DISPLAY("1d");
             terms(col) = logm_triang(a0(j, j), maxsqrt, rj);
//             NT2_DISPLAY("1dm");
             r(j, j) = rj;
//             NT2_DISPLAY("1df");
//             NT2_DISPLAY(r);
             for(uint32_t row=col-1; row >= 1; --row)
             {
//               NT2_DISPLAY(row);
               BOOST_AUTO_TPL(i, nt2::_(ord(1, row), ord(2, row)));
//               NT2_DISPLAY(i);
               if (length(i) == 1 && length(j) == 1)
               {
//               NT2_DISPLAY("Scalar case.");
                 size_t ii = i(1), jj = j(1);
                 BOOST_AUTO_TPL(k, nt2::_(ii+1, jj-1));
                 cplx_type temp = ca0(ii,jj)*(r(ii,ii) - r(jj,jj));
                 if (!isempty(k)) temp += mtimes(r(ii,k), ca0(k,jj)) - mtimes(ca0(ii,k), r(k,jj));
                 r(ii,jj) = temp/(ca0(ii,ii)-ca0(jj,jj));
               }
              else
              {
//                NT2_DISPLAY(ord);
                itab_t k(nt2::of_size(1, 0));
//                NT2_DISPLAY(k);
                for(uint32_t l = row+1; l < col; ++l)
                {
//                  NT2_DISPLAY(nt2::_(ord(1, l), ord(2, l)));
                  itab_t k1 = horzcat(k, nt2::_(ord(1, l), ord(2, l)));
                   //NT2_DISPLAY(k1);
                  k = k1;
                }
//                NT2_DISPLAY("icitte");
//                NT2_DISPLAY(r);
//                NT2_DISPLAY(ca0);
                ctab_t rhs =  mtimes(r(i,i), ca0(i,j)) - mtimes(ca0(i,j), r(j,j));
                if(!isempty(k)) rhs += mtimes(r(i,k), ca0(k,j)) -  mtimes(ca0(i,k), r(k,j));
//                 NT2_DISPLAY(mtimes(r(i,i), ca0(i,j)));
//                 NT2_DISPLAY(mtimes(ca0(i,j), r(j,j)));
//                 NT2_DISPLAY(i);
//                 NT2_DISPLAY(j);
//                 NT2_DISPLAY(k);
//                 if(!isempty(k))
//                 {
//                   NT2_DISPLAY(mtimes(r(i,k), ca0(k,j)));
//                   NT2_DISPLAY(ca0(i,k));
//                   NT2_DISPLAY(r(k, j));
//                   NT2_DISPLAY(mtimes(ca0(i,k), r(k,j)));
//                 }

//                 NT2_DISPLAY(rhs);
                r(i,j) = sylv_tri(ca0(i,i),-ca0(j,j),rhs);
//                 NT2_DISPLAY(r(i, j));
//                 NT2_DISPLAY(r);
              }

//             NT2_DISPLAY(r);
//             transtype(res, r, typename nt2::meta::is_complex<value_type>::type());
             }

             ctab_t z =  mtimes(mtimes(u, r), trans(conj(u)));
             transtype(res, z, typename nt2::meta::is_complex<value_type>::type());
//              NT2_DISPLAY(res);
//              NT2_DISPLAY(z);
// //         if (isreal(a0) && (norm(imag(r),1) <= 10*n*eps*norm(r,1)))
// //         {
// //           r = real(r);
// //         }


           }
        }
      }

      template < class T, class U, class B>
        static inline ctab_t sylv_tri(const T& t,const U& u, const B& b)
      {

        // sylv_tri    solve triangular sylvester equation.
        //    x = sylv_tri(t,u,b) solves the sylvester equation
        //  t*x + x*u = b, where t and u are square upper triangular matrices.

        uint32_t m = length(t);
        uint32_t n = length(u);
        ctab_t x = zeros(m,n, nt2::meta::as_<cplx_type>());
      // opts.ut = true;

      for(uint32_t i = 1;  i <= n; ++i)
      {
        ctab_t bb = b(nt2::_,i);
        BOOST_AUTO_TPL(ii, nt2::_(1u, i-1));
        if(!isempty(ii)) bb -= mtimes(x(nt2::_,ii),u(ii,i));
        x(nt2::_,i) = linsolve(t + u(i,i)*eye(m, meta::as_<cplx_type>()),
                               bb); //, opts);
      }

        return x;
      }

      template < class T1, class T2 >
        BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::false_ const &)
      {
        r =  real(z);
      }

      template < class T1, class T2 >
        BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::true_ const &)
      {
        r =  z;
      }
      template < class D> static inline void blocking(const D& a0, const r_type& delta, itab_t & ord)
      {
        uint32_t n = nt2::size(a0, 1);
        uint32_t j = 1;
        ord(1, 1) = 1;
        for(uint32_t i=2; i <= n; ++i)
        {
          if (nt2::abs(a0(i-1)-a0(i)) >= delta)
          {
            ord(2, j) = i-1;
            ord(1, ++j) = i;
          }
        }
        ord(2, j) = n;
        ord.resize(nt2::of_size(2u, j));
      }

      template < class D1, class D2> static inline
      uint32_t logm_triang(const D1& a0, uint32_t maxsqrt,
                           D2& rj)
      {
        uint32_t term = 0;
        if (size(a0, 1) == 1)
        {
//           NT2_DISPLAY("1111");
          rj(1) = log(a0(1));
        }
        else if(size(a0, 1) == 2)
        {
//           NT2_DISPLAY("2222");
          logm2by2(a0, maxsqrt, rj);
        }
        else
        {
           //NT2_DISPLAY("3333");
          logm_tr(a0, maxsqrt, rj, term);
        }
        return term;
      }

      template < class D1, class D2> static inline
      void logm2by2(const D1& a0,
                    uint32_t maxsqrt,
                    D2& rj)
      {
//        NT2_DISPLAY(a0);
        value_type a1 = a0(1,1);
        value_type a2 = a0(2,2);

        value_type loga1 = log(a1);
        value_type loga2 = log(a2);
        rj = nt2::cons(nt2::of_size(2, 2), loga1, Zero<value_type>(), Zero<value_type>(), loga2);
//        NT2_DISPLAY(rj);

        if (a1 == a2)
          rj(1,2) = a0(1,2)/a1;
        else if ((nt2::abs(a1) < nt2::Half<r_type>()*nt2::abs(a2)) ||
                 (nt2::abs(a2) < nt2::Half<r_type>()*nt2::abs(a1)))
          rj(1,2) =  a0(1,2) * (loga2 - loga1) / (a2 - a1);
        else// Close eigenvalues.
        {
          value_type dd = Two<value_type>()*nt2::atanh((a2-a1)/(a2+a1))+ unwind(loga2-loga1, meta::is_complex<value_type>());
          rj(1,2) = a0(1,2)*dd;
        }
//        NT2_DISPLAY(" ======== ");
//        NT2_DISPLAY(rj);
      }
      static inline r_type unwind(const value_type& z, boost::mpl::false_)
      {
        return Zero<r_type>();
      }
      static inline cplx_type unwind(const value_type& z, boost::mpl::true_)
      {static const cplx_type _2pi = nt2::Two<r_type>()*nt2::Pi<r_type>();
        return _2pi*cplx_type(Zero<r_type>(), nt2::ceil(imag(z)-nt2::Pi<r_type>())/_2pi);
      }


      template < class D1, class D2> static inline
      void logm_tr(const D1& a0,
                  uint32_t maxsqrt,
                  D2& rj,
                  uint32_t& term)
      {
        btab_t xvals = nt2::cons<r_type>(1.6206284795015669e-002,   // m = 3
                                         5.3873532631381268e-002,   // m = 4
                                         1.1352802267628663e-001,   // m = 5
                                         1.8662860613541296e-001,   // m = 6
                                         2.6429608311114350e-001    // m = 7
                                        );
        ctab_t t = a0;
        uint32_t k = 0, p = 0;
        uint32_t n = nt2::size(t, 1);
        uint32_t m = 0;
        while (true)
        {
          r_type normdiff = nt2::norm(t-eye(n, meta::as_<value_type>()),1);
          // NT2_DISPLAY(normdiff);
          //NT2_DISPLAY(t-eye(n, meta::as_<value_type>()));
          if (normdiff <= xvals(end_))
          {
            ++p;
            BOOST_AUTO_TPL( tj1, nt2::find(nt2::le(normdiff, xvals)));
            // NT2_DISPLAY(tj1);
            uint32_t j1 = tj1(1)+2;
             //NT2_DISPLAY(j1);
            normdiff /= 2;
            BOOST_AUTO_TPL( tj2, nt2::find(nt2::le(normdiff, xvals)));
            uint32_t j2 = tj2(1)+2;
            if ((j1-j2 < 2) || (p == 2))
            {
              m = j1;
              break;
            }
          }

          if (k == maxsqrt)
          {
            m = 16; break;
          }
           //NT2_DISPLAY("av sq");
          sqrtm_tri(t);
           //NT2_DISPLAY("ap sq");
          ++k;
        }
         //NT2_DISPLAY("av pf");
        logm_pf(t-eye(n, meta::as_<cplx_type>()),m, rj);
         //NT2_DISPLAY("ap pf");
         //NT2_DISPLAY(m);
         //NT2_DISPLAY(rj);
         //NT2_DISPLAY(twopower(k));
        rj *= r_type(twopower(k));
         //NT2_DISPLAY(rj);
         //NT2_DISPLAY("ap pf2");
      }
      template < class T > static inline void sqrtm_tri( T& t)
      {
        //       NT2_DISPLAY(size(t));
        uint32_t n = nt2::size(t, 1);
        ctab_t r = nt2::zeros(nt2::of_size(n, n), meta::as_<cplx_type>());
        // NT2_DISPLAY(size(r));
        for (uint32_t j=1; j <= n; ++j)
        {
          // NT2_DISPLAY(j);
          r(j,j) = nt2::sqrt(t(j,j));
          // NT2_DISPLAY(r);
          for(uint32_t  i=j-1;  i >= 1; --i)
          {
            // NT2_DISPLAY(j);
            // NT2_DISPLAY(i);
            r(i,j) = t(i,j);
            if (i+1 <= j-1)
            {
              ctab_t z1 = r(i,nt2::_(i+1, j-1));
              ctab_t z2 = r(nt2::_(i+1, j-1),j);
              // NT2_DISPLAY(z1);
              // NT2_DISPLAY(z2);
              ctab_t z3 = mtimes(z1, z2);
              r(i, j) -= z3;
              // NT2_DISPLAY(z3);
            }
            r(i,j) /= (r(i,i) + r(j,j));
            // NT2_DISPLAY(r);
          }
        }
         //NT2_DISPLAY("----");
         //NT2_DISPLAY(r);
        t = r;
      }

      template < class D, class S> static inline
        void logm_pf(const D& a0,
                     uint32_t m,
                     S& s)
        //    LOGM_PF   Pade approximation to matrix log by partial fraction expansion.
        //       LOGM_PF(A,m) is an [m/m] Pade approximant to LOG(EYE(SIZE(A))+A).
      {
        uint32_t n = nt2::size(a0, 1);
        btab_t nodes, wts;
        //NT2_DISPLAY("av gl");
        //NT2_DISPLAY(a0);
        gauss_legendre(m, nodes, wts);
         //NT2_DISPLAY("ap gl");
        //  Convert from [-1,1] to [0,1].
        nodes = oneplus(nodes)/nt2::Two<r_type>();
        wts /= Two<r_type>();
        s = zeros(n, meta::as_<cplx_type>());
        ctab_t p(nt2::of_size(n, n));
         //NT2_DISPLAY("ap gl1");
         for(uint32_t j=1;  j <= m; ++j)
         {
            //NT2_DISPLAY(j);
            //NT2_DISPLAY(trans(eye(n, meta::as_<r_type>())+nodes(j)*a0));
            //NT2_DISPLAY(trans(a0));
            //NT2_DISPLAY(nodes(j));
           p = trans(linsolve(trans(eye(n, meta::as_<r_type>())+nodes(j)*a0), trans(a0)));
            //NT2_DISPLAY(p);
           s +=  wts(j)*p;
         }
          //NT2_DISPLAY(s);
      }


    template < class X, class W> static inline void gauss_legendre( uint32_t n, X& x, W& w)
        //gauss_legendre  nodes and weights for gauss-legendre quadrature.
        //  gauss_legendre(n, x, w) computes the nodes x and weights w
        //  for n-point gauss-legendre quadrature.

        //reference:
        //G. H. Golub and J. H. Welsch, calculation of gauss quadrature
        //rules, math. comp., 23(106):221-230, 1969.
      {
        BOOST_AUTO_TPL(i,  nt2::_(nt2::One<r_type>(), r_type(n-1)));
        btab_t v = i/nt2::sqrt(nt2::minusone(nt2::sqr(nt2::Two<r_type>()*i)));
         //NT2_DISPLAY(v);
        btab_t d, vv;
         //NT2_DISPLAY(from_diag(v,-1)+from_diag(v,1));
        nt2::tie(vv, d) = nt2::symeig(from_diag(v,-1)+from_diag(v,1));
         //NT2_DISPLAY(vv);
         //NT2_DISPLAY(d);
        x = nt2::diag_of(d);
         //NT2_DISPLAY(x);
        w = nt2::Two<r_type>()*nt2::trans(nt2::sqr(vv(1,nt2::_)));
         //NT2_DISPLAY(w);

      }
    };


  }
}

#endif
