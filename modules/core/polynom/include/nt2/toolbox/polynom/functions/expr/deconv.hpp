//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_DECONV_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_DECONV_HPP_INCLUDED
#include <nt2/toolbox/polynom/functions/deconv.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/tie.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{

  //============================================================================
  // This version of balance is called whenever a tie(...) = balance(...) is captured
  // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::deconv_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::deconv_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       q_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       a_type; 
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       b_type; 
    typedef typename A0::value_type                                  value_type; 
    
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      val(a0, a1, N1());
    }
    
  private:
    
//     template < class T > BOOST_FORCEINLINE
//       void val(A0& a0, A1& a1,
//                boost::mpl::long_<1> const &, const T&) const
//     {
//       p_type & p = boost::proto::child_c<0>(a0);
//       x_type & x = boost::proto::child_c<1>(a0);
//       v_type & v = boost::proto::child_c<0>(a1);
//       compute_val(p, x, v); 
//     }
    
    BOOST_FORCEINLINE
      void val(A0& a0, A1& a1,
               boost::mpl::long_<2> const &) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type r_type;
      a_type & a = boost::proto::child_c<0>(a0);
      b_type & b = boost::proto::child_c<1>(a0);
      size_t na =  nt2::numel(a);
      size_t nb =  nt2::numel(b); 
      q_type & q = boost::proto::child_c<0>(a1);
      r_type & r = boost::proto::child_c<1>(a1);
      if(na < nb)
      {
        q = nt2::zeros(1, 0); 
        r = b;
      }
      else
      {
        size_t nq =  na+1-nb; 
        nt2::table<value_type, nt2::_2D> m =   nt2::eye(numel(a),meta::as_<value_type>());
        for(size_t i=1; i <= nq; ++i)
        {
          m(nt2::_(i, (i-1)+nb), i) = colvect(b);  
        } 
        nt2::table<value_type, nt2::_2D> bb; //, aa = colvect(a);
        bb = nt2::linsolve(m, colvect(a)); 
        q = rowvect(bb)(nt2::_(1, nq));
        r = rowvect(bb)(nt2::_(nq+1, nt2::end_)); 
      }    
    } 
  };  
} }


#endif
