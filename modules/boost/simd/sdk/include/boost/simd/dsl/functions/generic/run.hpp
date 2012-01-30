//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED

#include <boost/simd/dsl/functions/run.hpp>
#include <boost/dispatch/dsl/proto/unpack.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/include/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Run an expression without state nor data
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::formal_
                                    , (A0)
                                    , (ast_< unspecified_<A0> >)
                                    )
  {
    typedef proto::
    unpack< proto::
            call< dispatch::
                  functor< typename proto::tag_of<A0>::type >
                > ( proto::call< typename dispatch::
                                 make_functor<tag::run_, A0>::type
                               >
                  )
          >
    transform;
    
    template<class Sig> struct result;
    
    template<class This, class A0_>
    struct result<This(A0_)> : transform::template result<transform(A0_)> {};
    
    template<class A0_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&)>::type
    operator()(A0_& a0) const
    {
      return transform()(a0);
    }
  };

  //============================================================================
  // Run an expression with a state and no data
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)
                                    , (ast_< unspecified_<A0> >)
                                      (unspecified_<State>)
                                    )
  {
    typedef proto::
    unpack< proto::
            call< dispatch::
                  functor< typename proto::tag_of<A0>::type >
                > ( proto::
                    when< proto::_
                        , proto::call< typename dispatch::
                                       make_functor< tag::run_, A0>
                                                    ::type  ( proto::_expr
                                                            , proto::_state
                                                            )
                                     >
                        >
                  )
          >
    transform;
    
    template<class Sig> struct result;
    
    template<class This, class A0_, class State_>
    struct  result<This(A0_, State_)>
          : transform::template result<transform(A0_, State_)> {};
    
    template<class A0_, class State_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, State_&)>::type
    operator()(A0_& a0, State_& state) const
    {
      return transform()(a0, state);
    }
  };
  
  //============================================================================
  // Run an expression with a state and no data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(Domain)(State)
                                    , ((expr_ < unspecified_<A0>
                                              , Domain
                                              , boost::simd::tag::terminal_
                                              >
                                      ))
                                      (unspecified_<State>)
                                    )
  {
    template<class Sig> struct result;
    
    template<class This, class A0_, class State_>
    struct  result<This(A0_, State_)>
          : dispatch::meta::call<tag::terminal_(A0_, State_)> {};
      
    template<class A0_, class State_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, State_&)>::type
    operator()(A0_& a0, State_& state) const
    {
      typename dispatch::make_functor<tag::terminal_, A0>::type callee;
      return callee(a0, state);
    }
  };


  //============================================================================
  // Run an expression with a state and a data
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)(Data)
                                    , (ast_< unspecified_<A0> >)
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef proto::
    unpack< proto::
            call< dispatch::
                  functor< typename proto::tag_of<A0>::type >
                > ( proto::
                    when< proto::_
                        , proto::call< typename dispatch::
                                       make_functor< tag::run_, A0>                                       
                                                   ::type ( proto::_expr
                                                          , proto::_state
                                                          , proto::_data
                                                          )
                                     >
                        >
                  )
          >
    transform;
    
    template<class Sig> struct result;
    
    template<class This, class A0_, class State_, class Data_>
    struct  result<This(A0_, State_, Data_)>
          : transform::template result<transform(A0_, State_, Data_)> {};
    
    template<class A0_, class State_, class Data_> BOOST_DISPATCH_FORCE_INLINE     
    typename result<implement(A0_&, State_&, Data_&)>::type
    operator()(A0_& a0, State_& state, Data_& data) const
    {
      return transform()(a0, state, data);
    }
  };

  //============================================================================
  // Run an expression with a state and data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================    
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(Domain)(State)(Data)
                                    , ((expr_ < unspecified_<A0>
                                              , Domain
                                              , boost::simd::tag::terminal_
                                              >
                                      ))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    template<class Sig> struct result;
    
    template<class This, class A0_, class State_, class Data_>
    struct  result<This(A0_, State_, Data_)>
          : dispatch::meta::call<tag::terminal_(A0_, State_, Data_)>
    {};
      
    template<class A0_, class State_, class Data_> BOOST_DISPATCH_FORCE_INLINE 
    typename result<implement(A0_&, State_&, Data_&)>::type
    operator()(A0_& a0, State_& state, Data_& data) const
    {
      typename dispatch::make_functor<tag::terminal_, A0>::type callee;
      return callee(a0, state,data);
    }
  }; 
} } }

#endif
