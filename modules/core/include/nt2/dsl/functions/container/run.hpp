//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/runner.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/loop_nest.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Assignment of tables evaluates the right-hand-side in read mode and passes
  // the result to the left-hand-side for writing
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(Position)(Target)
                            , ((expr_< unspecified_<A0>
                                     , nt2::container::domain
                                     , nt2::tag::assign_
                                     >
                              ))
                             (fusion_sequence_<Position>)
                             (target_<unspecified_<Target> >)
                            )
  {
    typedef typename boost::proto::result_of::
            child_c<A0 const&, 0>::type                             result_type;
      
    result_type operator()(A0 const& a0, Position const& pos, Target const&) const
    {
      nt2::run( boost::proto::child_c<0>(a0)
              , pos
              , nt2::run( boost::proto::child_c<1>(a0)
                        , pos
                        , Target()
                        )
              );
              
      return boost::proto::child_c<0>(a0);
    }
  };
    
  //============================================================================
  // When an assign(lhs,rhs) expression is run, we perform the evaluation of rhs
  // then store it in lhs. Depending on the lhs nature (real terminal or a node
  // containing a call to any indexing function, the result of the evaluation is
  // returned, usually as non-const reference.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , ((expr_< unspecified_<A0>
                                     , nt2::container::domain
                                     , nt2::tag::assign_
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

#if !defined(BOOST_SIMD_NO_SIMD)
    //==========================================================================
    // If some SIMD is detected, then return a native
    //==========================================================================
    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;
#else
    //==========================================================================
    // If no SIMD is detected, stay in scalar mode
    //==========================================================================
    typedef stype                                           target_type;
#endif

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      boost::proto::child_c<0>(a0).resize(a0.extent());

      //==========================================================================
      // Generate a loop nest of proper depth running the expression evaluator
      // as its body and using indices/extent as loop bounds
      //==========================================================================
      meta::for_each( typename A0::index_type::type()
                    , nt2::extent(a0)
                    , typename boost::simd::meta::cardinal_of<target_type>::type()
                    , meta::runner<A0, stype>(a0)
                    );

      //==========================================================================
      // Once done, return the newly computed result
      //==========================================================================
      return boost::proto::child_c<0>(a0);
    }
  };
  
  //============================================================================
  // When an arbitrary expression is run, we perform its evaluation into a
  // local temporary container of proper type.This temporary is then returned by
  // value.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                            )
  {
    typedef typename boost::
    remove_reference< typename boost::dispatch::meta::
                      terminal_of< typename boost::dispatch::meta::
                                   semantic_of<A0 const&>::type
                                 >::type
                    >::type                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type tmp;
      run(assign(tmp, a0));
      return tmp;
    }
  };

  //============================================================================
  // When an assign(lhs,rhs) scalar expression is run, we perform a single
  // assignment of said scalar value.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_, (A0)
                            , ((expr_< scalar_< fundamental_<A0> >
                                     , nt2::container::domain
                                     , nt2::tag::assign_
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::scalar_of<result_type>::type>::type
            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      if( boost::proto::child_c<0>(a0).extent() != a0.extent() )
        boost::proto::child_c<0>(a0).resize(a0.extent());

      nt2::run(a0, of_size_<>(), meta::as_<target_type>());
      return boost::proto::child_c<0>(a0);
    }
  };

  //============================================================================
  // When a scalar expression is run, we don't perform the operation into
  // a temporary, but rather directly return it.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , (ast_<scalar_< unspecified_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0 const&>::type                            result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::run( a0
                     , of_size_<>()
                     , meta::as_<typename meta::strip<result_type>::type>()
                     );
    }
  };
} }

#endif
