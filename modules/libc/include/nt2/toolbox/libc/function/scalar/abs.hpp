//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_LIBC_FUNCTION_SCALAR_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_LIBC_FUNCTION_SCALAR_ABS_HPP_INCLUDED


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(libc::tag::abs_, tag::cpu_,
                     (A0),
                     (arithmetic_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<libc::tag::abs_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return ::abs(a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(libc::tag::abs_, tag::cpu_,
                     (A0),
                     (double_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<libc::tag::abs_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1){ return ::fabs(a0); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(libc::tag::abs_, tag::cpu_,
                     (A0),
                     (float_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<libc::tag::abs_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1){ return ::fabs(a0); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is long double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(libc::tag::abs_, tag::cpu_,
                     (A0),
                     (long_double_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<libc::tag::abs_(tag::long_double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1){ return ::fabsl(a0); }
  };
} }

#endif
// modified by jt the 29/12/2010