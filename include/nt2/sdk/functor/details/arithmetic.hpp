/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_ARITHMETIC_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_ARITHMETIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// boolean operators implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//////////////////////////////////////////////////////////////////////////////
// Dispatch for classical operators
//////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::unary_plus_ , tag::cpu_, (A0)
                      , (fundamental_<A0>)
                      )
NT2_REGISTER_DISPATCH ( tag::unary_minus_        , tag::cpu_, (A0)
                      , (arithmetic_<A0>)
                      )
NT2_REGISTER_DISPATCH ( tag::plus_       , tag::cpu_, (A0)(A1)
                      , (arithmetic_<A0>)(arithmetic_<A1>)
                      )
NT2_REGISTER_DISPATCH ( tag::minus_      , tag::cpu_, (A0)(A1)
                      , (arithmetic_<A0>)(arithmetic_<A1>)
                      )
NT2_REGISTER_DISPATCH ( tag::multiplies_ , tag::cpu_, (A0)(A1)
                      , (arithmetic_<A0>)(arithmetic_<A1>)
                      )
NT2_REGISTER_DISPATCH ( tag::divides_    , tag::cpu_, (A0)(A1)
                      , (arithmetic_<A0>)(arithmetic_<A1>)
                      )
NT2_REGISTER_DISPATCH ( tag::modulo_     , tag::cpu_, (A0)(A1)
                      , (integer_<A0>)(integer_<A1>)
                      )
NT2_REGISTER_DISPATCH ( tag::if_else_ , tag::cpu_, (A0)(A1)(A2)
                      , (fundamental_<A0>)(fundamental_<A1>)(fundamental_<A2>)
                      )

////////////////////////////////////////////////////////////////////////////////
// Generating implementation for operators
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // Ternary operator
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct call < tag::if_else_(tag::fundamental_,tag::fundamental_,tag::fundamental_)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>  struct
    result<This(A0,A1,A2)>
    {
      static A0 a0; static A1 a1; static A2 a2;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0 ? a1 : a2)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3) { return a0 ? a1 : a2; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Unary minus
  //////////////////////////////////////////////////////////////////////////////
  #ifdef BOOST_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4146) // unary minus applied to unsigned
  #endif

  template<class Dummy>
  struct call<tag::unary_minus_(tag::arithmetic_), tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>  struct
    result<This(A0)>
    {
      static A0 a0;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,-a0)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(1) { return -a0; }
  };

  #ifdef BOOST_MSVC
    #pragma warning(pop)
  #endif

  //////////////////////////////////////////////////////////////////////////////
  // Unary plus
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct call<tag::unary_plus_(tag::fundamental_), tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>  struct
    result<This(A0)>
    {
      static A0 a0;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,+a0)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(1) { return +a0; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Binary plus
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call<tag::plus_(tag::arithmetic_,tag::arithmetic_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0+a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0+a1; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Binary minus
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call<tag::minus_(tag::arithmetic_,tag::arithmetic_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0-a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0-a1; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Multiplies
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call<tag::multiplies_(tag::arithmetic_,tag::arithmetic_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0*a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0*a1; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Divides
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call<tag::divides_(tag::arithmetic_,tag::arithmetic_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0/a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0/a1; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Modulo
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call<tag::modulo_(tag::integer_,tag::integer_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0%a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0 % a1; }
  };
} }

#endif
