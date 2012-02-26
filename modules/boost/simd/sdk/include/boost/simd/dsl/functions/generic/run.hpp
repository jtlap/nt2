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
                                    , (ast_<A0>)
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
    
    typedef typename transform::template
            result<transform(A0&)>::type                    result_type;
    
    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return transform()(a0);
    }
  };

  //============================================================================
  // Run an expression with a state and no data
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)
                                    , (ast_<A0>)
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
    
    typedef typename transform::template
            result<transform(A0&, State&)>::type            result_type;
    
    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State& state) const
    {
      return transform()(a0, state);
    }
  };
  
  //============================================================================
  // Run an expression with a state and no data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)
                                    , ((expr_ < unspecified_<A0>
                                              , boost::simd::tag::terminal_
                                              , mpl::long_<0>
                                              >
                                      ))
                                      (unspecified_<State>)
                                    )
  {
    typedef typename dispatch::meta::
            call<boost::proto::tag::terminal(A0&, State&)>::type result_type;
      
    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State& state) const
    {
      typename dispatch::make_functor<boost::proto::tag::terminal, A0>::type()
               (a0, state);
    }
  };


  //============================================================================
  // Run an expression with a state and a data
  //============================================================================  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)(Data)
                                    , (ast_<A0>)
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
    
    typedef typename transform::template
            result<transform(A0&, State&, Data const&)>::type     result_type;
    
    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State& state, Data const& data) const
    {
      return transform()(a0, state, data);
    }
  };

  //============================================================================
  // Run an expression with a state and data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================    
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(State)(Data)
                                    , ((expr_ < unspecified_<A0>
                                              , boost::simd::tag::terminal_
                                              , mpl::long_<0>
                                              >
                                      ))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef typename dispatch::meta::
            call<boost::proto::tag::terminal(A0&, State&, Data const&)>::type result_type;
      
    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State& state, Data const& data) const
    {
      typename dispatch::make_functor<boost::proto::tag::terminal, A0>::type()
               (a0, state,data);
    }
  }; 
} } }

#endif
