/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Register terminal handlers for SIMD expression - native case
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::terminal_,tag::cpu_
                     ,(A0)(A1)(A2)(X)(Y)
                     ,((simd_<arithmetic_<A0>,X>))
                      ((target_<simd_<arithmetic_<A1>,Y> >))
                      (int32_<A2>)
                     )

NT2_REGISTER_DISPATCH(tag::terminal_,tag::cpu_
                     ,(A0)(A1)(A2)(X)
                     ,(arithmetic_<A0>)
                      ((target_<simd_<arithmetic_<A1>,X> >))
                      (int32_<A2>)
                     )

NT2_REGISTER_DISPATCH(tag::terminal_,tag::cpu_
                    ,(A0)(A1)(A2)(X)
                    ,(constant_<A0>)
                     ((target_<simd_<arithmetic_<A1>,X> >))
                     (int32_<A2>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy,class X,class Y>
  struct call<tag::terminal_( tag::simd_<tag::arithmetic_,X>
                            , tag::target_< tag::simd_<tag::arithmetic_,Y> >
                            , tag::int32_
                            ),tag::cpu_,Dummy>
  : callable
  {
    template<class Sig> struct result;

    template<class This, class Value, class State, class Data>
    struct result<This(Value,State,Data)>
    {
      typedef typename meta::strip<Value>::type::parent type;
    };

    template<class Value, class State, class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()( Value& v, State& , Data&  ) const
    {
      return v.value();
    }
  };

  template<class Dummy,class X>
  struct call<tag::terminal_( tag::arithmetic_
                            , tag::target_< tag::simd_<tag::arithmetic_,X> >
                            , tag::int32_
                            ),tag::cpu_,Dummy>
  : callable
  {
    template<class Sig> struct result;

    template<class This, class Value, class State, class Data>
    struct result<This(Value,State,Data)> :  meta::strip<State>::type {};

    template<class Value, class State, class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()( Value& v, State& , Data&  ) const
    {
      typedef typename result<call(Value,State,Data)>::type type;
      return splat<type>(v);
    }
  };

  template<class Dummy,class ID, class X>
  struct call<tag::terminal_( tag::constant_<ID>
                            , tag::target_< tag::simd_<tag::arithmetic_,X> >
                            , tag::int32_
                            ),tag::cpu_,Dummy>
  : callable
  {
    template<class Sig> struct result;

    template<class This, class Value, class State, class Data>
    struct result<This(Value,State,Data)> :  meta::strip<State>::type {};

    template<class Value, class State, class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()( Value& , State& , Data&  ) const
    {
      functor<ID> callee;
      typedef typename result<call(Value,State,Data)>::type type;
      return callee( meta::as_<type>() );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register terminal handlers for SIMD expression - emulated case
////////////////////////////////////////////////////////////////////////////////

#endif
