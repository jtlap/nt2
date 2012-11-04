//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_POLYFIT_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_POLYFIT_HPP_INCLUDED
#include <nt2/toolbox/polynom/functions/polyfit.hpp>
#include <nt2/include/functions/vandermonde.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>    
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/subs.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/toolbox/polynom/category.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/stdev.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/core/container/table/table.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 {
  
  template < class T> struct polyfit_infos
  {   
    typedef T value_type; 
//      polyfit_infos is a structure containing three elements: the triangular factor from a
//      qr decomposition of the vandermonde matrix, the degrees of freedom and
//      the norm of the residuals.
    nt2::table<value_type> r;
    size_t df;
    value_type normr; 
  }; 
  
  
  namespace ext
  {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyfit_, tag::cpu_
//                             , (A0)(A1)
//                             , (unspecified_<A0>)(scalar_<floating_<A1> > )
//                             )
//   {
    
//     typedef typename A0::value_type value_type;
//     typedef A1 result_type; 
//     NT2_FUNCTOR_CALL(2)
//     {
//       if (isempty(a0)) return Zero<A1>(); 
//       A1 ans = a0(1);
//       for(size_t i = 2; i <= numel(a0); ++i)
//       {
//         ans = fma(ans, a1, a0(i));
//       }
//       return ans;
//     }
//   };
    
    
    //============================================================================
    // This version of balance is called whenever a tie(...) = balance(...) is captured
    // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
    // pair as inputs
    //============================================================================
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyfit_, tag::cpu_
                                , (A0)(N0)(A1)(N1)
                                , ((node_<A0, nt2::tag::polyfit_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
      )
    {
      typedef void                                                    result_type;
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       p_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::type       x_type; 
      typedef typename boost::proto::result_of::child_c<A0&,1>::type       y_type;
      typedef typename meta::strip<p_type>::type                              p_t;
      typedef typename p_t::value_type                                 value_type; 
      typedef polyfit_infos<value_type>                                    s_type;
      
      BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
      {
        // Copy data in output first
        x_type & x = boost::proto::child_c<0>(a0);
        y_type & y = boost::proto::child_c<1>(a0);
        size_t l = lval(a0, N0()); 
        polcoefs(a1, x, y, l, N1());
      }
      
    private:
      BOOST_FORCEINLINE
        int32_t lval(A0& a0, boost::mpl::long_<3> const &) const
      {
        return boost::proto::value(boost::proto::child_c<2>(a0))+1; 
      }
      template < class T > 
        BOOST_FORCEINLINE
        int32_t lval(A0& a0, T const &) const
      {
        return nt2::numel(boost::proto::child_c<0>(a0)); 
      }
      
      BOOST_FORCEINLINE
        void polcoefs(A1& a1, x_type const & x, y_type const &y, 
                      const int32_t & l, boost::mpl::long_<1> const &) const
      {
        p_type & p = boost::proto::child_c<0>(a1);
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        p = nt2::rowvect(nt2::linsolve(vnd, nt2::colvect(y))); 
      }
      
      BOOST_FORCEINLINE
        void polcoefs(A1 &a1, x_type const & x, y_type const &y, 
                      const size_t & l, boost::mpl::long_<2> const &) const
      {
        p_type & p = boost::proto::child_c<0>(a1);
        s_type & s = boost::proto::child_c<1>(a1);
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        typedef typename nt2::meta::call<nt2::tag::colvect_(y_type const &)>::type cy_t;
        typedef typename nt2::meta::call<nt2::tag::vandermonde_(cy_t const &, size_t const &)>::type vnd_t;
        typedef typename nt2::meta::call<nt2::tag::factorization::qr_(vnd_t const&, char)>::type qr_type;
        qr_type res = nt2::factorization::qr(vnd, 'N');
        s.r = res.r();
        nt2::rowvect(res.solve(colvect(y), p));
        p.resize(of_size(1u, numel(p))); 
        s.df = nt2::subs(nt2::length(y), nt2::oneplus(l)); 
        s.normr = nt2::norm(colvect(y)-nt2::mtimes(vnd, nt2::colvect(p)));
      }

      BOOST_FORCEINLINE
        void polcoefs(A1 &a1, x_type const & x, y_type const &y, 
                      const size_t & l, boost::mpl::long_<4> const &) const
      {
        typedef typename boost::proto::result_of::child_c<A1&,1>::type       r_type;
        typedef typename boost::proto::result_of::child_c<A1&,2>::type       df_type;
        typedef typename boost::proto::result_of::child_c<A1&,3>::type       nr_type;  
        p_type & p = boost::proto::child_c<0>(a1);
        r_type & r = boost::proto::child_c<1>(a1);
        df_type& df= boost::proto::child_c<2>(a1);
        nr_type& normr= boost::proto::child_c<3>(a1);
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        typedef typename nt2::meta::call<nt2::tag::colvect_(x_type const &)>::type cx_t;
        typedef typename nt2::meta::call<nt2::tag::vandermonde_(cx_t const &, size_t const &)>::type vnd_t;
        typedef typename nt2::meta::call<nt2::tag::factorization::qr_(vnd_t const&, char)>::type qr_type;
        qr_type res = nt2::factorization::qr(vnd, 'N');
        r = res.r();
        nt2::rowvect(res.solve(colvect(y), p));
        p.resize(of_size(1u, numel(p))); 
        df = nt2::subs(nt2::numel(y), l); 
        normr = nt2::norm(colvect(y)-nt2::mtimes(vnd, nt2::colvect(p)));
      }

      BOOST_FORCEINLINE
        void polcoefs(A1 &a1, x_type const & x, y_type const &y, 
                      const size_t & l, boost::mpl::long_<5> const &) const
      {
        typedef typename boost::proto::result_of::child_c<A1&,1>::type       r_type;
        typedef typename boost::proto::result_of::child_c<A1&,2>::type       df_type;
        typedef typename boost::proto::result_of::child_c<A1&,3>::type       nr_type;
        typedef typename boost::proto::result_of::child_c<A1&,4>::type       mu_type;
        mu_type & mu = boost::proto::child_c<4>(a1);
        mu.resize(nt2::of_size(1, 2)); 
        mu(1) = nt2::mean(nt2::colvect(x))(1);
        mu(2) = nt2::stdev(nt2::colvect(x))(1);
        
        
        p_type & p = boost::proto::child_c<0>(a1);
        r_type & r = boost::proto::child_c<1>(a1);
        df_type& df= boost::proto::child_c<2>(a1);
        nr_type& normr= boost::proto::child_c<3>(a1);
        BOOST_AUTO_TPL(vnd, nt2::vandermonde((nt2::colvect(x)-mu(1))/mu(2), l));
        typedef typename nt2::meta::call<nt2::tag::colvect_(x_type const &)>::type cx_t;
        typedef typename nt2::meta::call<nt2::tag::minus_(cx_t, value_type)>::type tmp1_t;
        typedef typename nt2::meta::call<nt2::tag::divides_(tmp1_t, value_type)>::type tmp2_t;
        typedef typename nt2::meta::call<nt2::tag::vandermonde_(tmp2_t const &, size_t const &)>::type vnd_t;
        typedef typename nt2::meta::call<nt2::tag::factorization::qr_(vnd_t const&, char)>::type qr_type;
        qr_type res = nt2::factorization::qr(vnd, 'N');
        r = res.r();
        res.solve(colvect(y), p);
        p.resize(of_size(1u, numel(p))); 
        df = nt2::subs(nt2::numel(y), l);
        normr = nt2::norm(colvect(y)-nt2::mtimes(vnd, nt2::colvect(p)));
      }

      
    };  
  }
}


#endif
