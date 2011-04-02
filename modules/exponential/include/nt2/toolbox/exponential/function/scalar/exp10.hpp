//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXP10_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXP10_HPP_INCLUDED
#include <nt2/toolbox/exponential/function/scalar/impl/expo.hpp>

namespace nt2 {  namespace details
  {
    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 values
    // ///////////////////////////////////////////////////////////////////////////
    template<class T, int N> struct static_exp10
    {
      static const T value = T(10)*static_exp10<T,N-1>::value;
    };

    template<class T> struct static_exp10<T,0>  { static const T value = 1; };
    template<class T> struct static_exp10<T,-1> { static const T value = 0; };

    #define NT2_CREATE_FAST_EXP10_LIMIT(T,L)                          \
    template<> struct static_exp10<T,L> { static const T value = 0; } \
    /**/

    NT2_CREATE_FAST_EXP10_LIMIT(int8_t      , 3);
    NT2_CREATE_FAST_EXP10_LIMIT(uint8_t     , 3);
    NT2_CREATE_FAST_EXP10_LIMIT(int16_t     , 5);
    NT2_CREATE_FAST_EXP10_LIMIT(uint16_t    , 5);
    NT2_CREATE_FAST_EXP10_LIMIT(int32_t     ,10);
    NT2_CREATE_FAST_EXP10_LIMIT(uint32_t    ,10);
    NT2_CREATE_FAST_EXP10_LIMIT(int64_t     ,19);
    NT2_CREATE_FAST_EXP10_LIMIT(uint64_t    ,20);
    #undef NT2_CREATE_FAST_EXP10_LIMIT

    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 linearization
    // ///////////////////////////////////////////////////////////////////////////
    template<class T,int D, int F, bool STOP = (F==D+1)> struct s_exp10
    {
      static const T pivot = (F+D)/2;
      static inline T Eval(const T& x)
      {
        return (x<pivot) ? s_exp10<T,D,pivot>::Eval(x) : s_exp10<T,pivot,F>::Eval(x);
      }
    };

    template<class T,int D, int F> struct s_exp10<T,D,F,true>
    {
      static inline T Eval(const T& ) { return static_exp10<T,D>::value; }
    };

    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 entry-point
    // ///////////////////////////////////////////////////////////////////////////
    #define NT2_FAST_EXP10(T,D,F) \
    inline T specExp10( const T& x ) { return s_exp10<T,D,F>::Eval(x); }

    NT2_FAST_EXP10(int8_t      , -1, 4)
    NT2_FAST_EXP10(uint8_t     ,  0, 4)
    NT2_FAST_EXP10(int16_t     , -1, 6)
    NT2_FAST_EXP10(uint16_t    ,  0, 6)
    NT2_FAST_EXP10(int32_t     , -1,11)
    NT2_FAST_EXP10(uint32_t    ,  0,11)
    NT2_FAST_EXP10(int64_t     , -1,20)
    NT2_FAST_EXP10(uint64_t    ,  0,21)
    #undef NT2_FAST_EXP10
  }
}

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exp10_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::exp10_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> :
        std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
      {
        return details::specExp10(a0);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exp10_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::exp10_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> :
        std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
      {
         return impl::exponential<A0,ten_tag, tag::not_simd_type, accu_tag>::expa(a0);
      }
  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 29/12/2010
