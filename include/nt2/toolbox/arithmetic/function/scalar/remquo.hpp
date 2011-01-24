//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMQUO_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/mpl/vector.hpp>
<<<<<<< HEAD
#include <nt2/include/functions/idivfix.hpp> 
namespace nt2 { namespace functors
=======


namespace nt2 { namespace details
>>>>>>> functor2
{
  template <class T,class Dummy> struct remquo;
  
  template <class Dummy> struct remquo<double,Dummy>{
    typedef double                                          rem; 
    typedef typename meta::as_integer<double,signed>::type  quo;
    typedef boost::fusion::tuple<rem,quo>                 rtype;
    
    static inline rtype eval(const double& a0, const double& a1)
    {
      rtype res;
      int rt; 
      boost::fusion::at_c<0>(res) = ::remquo(a0, a1, &rt);
      boost::fusion::at_c<1>(res) = rt;
      return res; 
    }
  }; 
    
  template <class Dummy> struct remquo<float,Dummy>{
    typedef float                                           rem; 
    typedef typename meta::as_integer<double,signed>::type  quo;
    typedef boost::fusion::tuple<rem,quo>                 rtype;
    
    static inline rtype eval(const float& a0, const float& a1)
    {
      rtype res;
      int rt; 
      boost::fusion::at_c<0>(res) = ::remquof(a0, a1, &rt);
      boost::fusion::at_c<1>(res) = rt;
      return res; 
    }
  }; 
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when A0 and A1 types are fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::remquo_, tag::cpu_,
                        (A0)(A1),
                        (fundamental_<A0>)(fundamental_<A1>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::remquo_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename boost::result_of<meta::floating(A0,A1)>::type rem;
      typedef typename meta::as_integer<rem,signed>::type            quo;
      typedef boost::fusion::tuple<rem,quo>                         type;
    };

    NT2_FUNCTOR_CALL(2)
    {
<<<<<<< HEAD
      typename NT2_CALL_RETURN_TYPE(2)::type res;
      typedef meta::find_type<A0,float,double,empty_> set_t;
      eval( a0, a1
          , boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)
          , typename set_t::type()
          );
      return res;
    }
  private :
    template<class A0,class A1,class R0,class R1> inline void
    eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1, double const &)const
    {
      r1 = idivfix(a0, a1);
      r0 = a0-r1*a1;
      //int rt;
      //       r0 = ::remquo(a0, a1, &rt);
      //        r1 = rt;
    }

    template<class A0,class A1,class R0,class R1> inline void
    eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1, float const &)const
    {
      r1 = idivfix(a0, a1);
      r0 = a0-r1*a1;
      //int rt;
      //       r0 = ::remquof(a0, a1, &r1);
=======
      typedef typename boost::result_of<meta::floating(A0,A1)>::type ftype;
      return  details::remquo<ftype,void>::eval(ftype(a0), ftype(a1));
>>>>>>> functor2
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// manually modified  by jt the 28/12/2010
