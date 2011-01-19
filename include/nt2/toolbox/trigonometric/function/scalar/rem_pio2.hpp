//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_REM_PIO2_HPP_INCLUDED



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::rem_pio2_, tag::cpu_,
                          (A0),
                          (arithmetic_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::rem_pio2_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0; /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::rem_pio2_, tag::cpu_,
                          (A0),
                          (double_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::rem_pio2_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return a0; /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::rem_pio2_, tag::cpu_,
                          (A0),
                          (float_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::rem_pio2_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0; /*PUT CODE HERE*/
    }
  };
} }

#endif
// modified by jt the 26/12/2010