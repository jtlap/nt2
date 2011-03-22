/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_TERMINAL_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_TERMINAL_HPP_INCLUDED

#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

////////////////////////////////////////////////////////////////////////////////
// Terminal functor handling for pack based expressions
// Two flavors are presented : the native and boost::array one
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // We dispatch on T type for load
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct  dispatch<terminal_,Category,Info> : boost::mpl::always<fundamental_>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // vector terminal - native mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type, class Extension, class Category>
  struct  call< terminal_   , tag::ast_(Category)
              , fundamental_, simd::native<Type,Extension>
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef simd::native<Type,Extension> type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& , Data& ) const
    {
      return v.value();
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // vector terminal - array mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Cardinal, class Category>
  struct  call< terminal_   , tag::ast_(Category)
              , fundamental_, boost::array<Type,Cardinal>
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef Type type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& s, Data& ) const
    {
      return v[s];
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // scalar terminal - native mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Extension>
  struct call < terminal_
              , tag::scalar_(tag::arithmetic_)
              , fundamental_
              , simd::native<Type,Extension>
              >
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef simd::native<Type,Extension> type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& , Data& ) const
    {
      return splat<typename result<call(Value,State,Data)>::type>(v);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // named constant terminal - native mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Extension,class Constant>
  struct call < terminal_
              , tag::constant_(Constant)
              , fundamental_
              , simd::native<Type,Extension>
              >
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef simd::native<Type,Extension> type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& s, Data& d) const
    {
      functors::functor<typename Value::type> callee;
      return callee( meta::as_< simd::native<Type,Extension> >() );
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // scalar terminal - array mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal>
  struct call < terminal_
              , tag::scalar_(tag::arithmetic_)
              , fundamental_
              , boost::array<Type,Cardinal>
              >
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef Type type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& , Data& ) const
    {
      return v;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // named constant terminal - array mode
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal,class Constant>
  struct call < terminal_
              , tag::constant_(Constant)
              , fundamental_
              , boost::array<Type,Cardinal>
              >
  {
    template<class Sig> struct result;
    template<class This,class Value,class State,class Data>
    struct result<This(Value,State,Data)>
    {
      typedef Type type;
    };

    template<class Value,class State,class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()(Value& v, State& s, Data& d) const
    {
      functors::functor<typename Value::type> callee;
      return callee( meta::as_< Type >() );
    }
  };

} }

#endif
