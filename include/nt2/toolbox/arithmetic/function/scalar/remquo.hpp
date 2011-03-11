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
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/idivround.hpp>

namespace nt2 { namespace details
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
    typedef typename meta::as_integer<float,signed>::type  quo;
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
      typedef typename std::tr1::result_of<meta::floating(A0,A1)>::type rem;
      typedef typename meta::as_integer<rem,signed>::type            quo;
      typedef boost::fusion::tuple<rem,quo>                         type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename std::tr1::result_of<meta::floating(A0,A1)>::type ftype;
      typedef typename NT2_RETURN_TYPE(2)::type rtype; 
      rtype res;
      boost::fusion::at_c<0>(res) = nt2::remainder(ftype(a0), ftype(a1));
      boost::fusion::at_c<1>(res) = nt2::idivround(ftype(a0), ftype(a1));
      return res; 
    }
    
  };
} }

#endif
// modified by jt the 26/12/2010
// manually modified  by jt the 28/12/2010
