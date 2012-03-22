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

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/transform.hpp>
#include <nt2/include/functions/fold.hpp>
#include <nt2/include/functions/terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <iostream>
namespace nt2 { namespace ext
{
  //============================================================================
  // Element-wise operations go to transform
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0>))
                              ((node_<A1, elementwise_<T1>, N1>))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());
      nt2::transform(a0, a1);
      return a0;
    }
  };

  //============================================================================
  // Reductions operations go to fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(T0)(N0)(A1)(T1)(O1)(Neutral1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0>))
                              ((node_<A1, reduction_<T1,O1,Neutral1>, N1 >))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      std::size_t reduced_dim = nt2::run(boost::proto::child_c<1>(a1));
      //      std::cout<< reduced_dim << "\n";

      a0.resize(a1.extent());

      // TODO
#if 0
      nt2::fold( a0
                 , boost::proto::child_c<0>(a1)
                 , typename nt2::make_functor<Neutral1>::type()
                 , typename nt2::make_functor<O1>::type()
                 , boost::proto::child_c<1>(a1)
                 );
#endif
      return a0;
    }
  };


  //============================================================================
  // Non-assign table expressions are reduced to assign expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)(T)(N)
                            , (mpl::not_< is_same<T, boost::simd::tag::assign_> >)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::
    remove_reference< typename boost::dispatch::meta::
                      terminal_of< typename boost::dispatch::meta::
                                   semantic_of<A0&>::type
                                 >::type
                    >::type                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      result_type tmp;
      run_assign(tmp, a0);
      return tmp;
    }
  };

  //============================================================================
  // Non-assign scalar expressions are evaluated directly
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(T)(N)
                            , (mpl::not_< is_same<T, boost::simd::tag::assign_> >)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0&>::type                                  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      typedef typename meta::strip<result_type>::type stype;
      return nt2::run( a0, boost::fusion::vector0<>(), meta::as_<stype>() );
    }
  };

  //============================================================================
  // Assign expressions call run_assign
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , ((node_< A0
                                     , boost::simd::tag::assign_
                                     , boost::mpl::long_<2>
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<tag::run_assign_( typename boost::proto::result_of::child_c<A0&, 0>::type
                                 , typename boost::proto::result_of::child_c<A0&, 1>::type
                                 )
                >::type                                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return nt2::run_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0));
    }
  };
} }

#endif
