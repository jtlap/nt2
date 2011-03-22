//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>


  extern "C"{
    extern double fd_frexp ( double,int* );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::frexp_, tag::cpu_,
                       (A0),
                       (double_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::frexp_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)>
    {
      typedef typename meta::strip<A0>::type         f_type;
      typedef typename meta::as_integer<A0>::type    i_type; 
      typedef boost::fusion::vector<f_type, i_type>    type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type rtype;
      rtype res; 
      int r1t;
      boost::fusion::at_c<0>(res) = fd_frexp(a0, &r1t);
      boost::fusion::at_c<1>(res) = r1t;
      return res;
    }

  };
} }

#endif
// modified by jt the 29/12/2010
