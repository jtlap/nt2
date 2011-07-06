//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/mpl/vector.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/idivround.hpp>

// namespace nt2 { namespace details
// {
//   template <class T,class Dummy> struct remquo;
  
//   template <class Dummy> struct remquo<double,Dummy>{
//     typedef double                                          rem; 
//     typedef typename meta::as_integer<double,signed>::type  quo;
//     typedef boost::fusion::tuple<rem,quo>                 rtype;
    
//     static inline rtype eval(const double& a0, const double& a1)
//     {
//       rtype res;
//       int rt; 
//       boost::fusion::at_c<0>(res) = ::remquo(a0, a1, &rt);
//       boost::fusion::at_c<1>(res) = rt;
//       return res; 
//     }
//   }; 
    
//   template <class Dummy> struct remquo<float,Dummy>{
//     typedef float                                           rem; 
//     typedef typename meta::as_integer<float,signed>::type  quo;
//     typedef boost::fusion::tuple<rem,quo>                 rtype;
    
//     static inline rtype eval(const float& a0, const float& a1)
//     {
//       rtype res;
//       int rt; 
//       boost::fusion::at_c<0>(res) = ::remquof(a0, a1, &rt);
//       boost::fusion::at_c<1>(res) = rt;
//       return res; 
//     }
//   }; 
// } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when A0 and A1 types are fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::remquo_, tag::cpu_,
			     (A0)(A1),
			     (scalar_ < fundamental_<A0> > )
			     (scalar_ < fundamental_<A1> > )
			     )
  {
    typedef typename meta::result_of<meta::floating(A0,A1)>::type ftype;
    typedef typename meta::as_integer<ftype,signed>::type           quo;
    typedef boost::fusion::tuple<ftype,quo>                 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      result_type res;
      nt2::remquo(a0, a1, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res; 
    }
    
  };

  NT2_FUNCTOR_IMPLEMENTATION(tag::remquo_, tag::cpu_,
			     (A0)(A1)(A2)(A3),
			     (scalar_ < arithmetic_<A0> > )
			     (scalar_ < arithmetic_<A1> > )
			     (scalar_ < real_<A2> > )
			     (scalar_ < arithmetic_<A3> > )
			     )
  {
    typedef void result_type;    
    inline void operator()(A0 const& a0,A1 const& a1,A2 & a2,A3 & a3) const
    {
      a2 = nt2::remainder(A2(a0), A2(a1));
      a3 = nt2::idivround(A2(a0), A2(a1));
    }
    
  };  
} }

#endif
