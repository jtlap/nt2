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
#include <nt2/include/functions/inner_fold.hpp>
#include <nt2/include/functions/outer_fold.hpp>
//#include <nt2/include/functions/partial_fold.hpp>
//#include <nt2/include/functions/reshape.hpp>
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
      a0.resize(a1.extent());

      typename boost::proto::result_of::child_c<A1&, 0>::type input = boost::proto::child_c<0>(a1);
      std::size_t dim = input.extent().size();
      std::size_t red = reduction_dim(a1
                                      , boost::mpl::bool_<!(boost::proto::arity_of<A1>::value <= 1)>());

      std::cout<< "red " << red << "\n";


      if(red > dim)
        return a0;

#if 0
      if(dim == 1)
      {
        nt2::run( a0, boost::fusion::vector0<>()
                  , nt2::fold( input
                               , typename nt2::make_functor<Neutral1, A0>::type()
                               , typename nt2::make_functor<O1, A0>::type()
                               )
                );
      }
      else if(red == 1)
      {
        nt2::inner_fold( a0
                       , input
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       );
      }
      else if(red == dim)
      {
        nt2::outer_fold( a0
                       , input
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       );
      }
      else
      {
      #if 0
        std::size_t lo = std::accumulate( input.extent().data()
                                        , input.extent().data()+red-1
                                        , std::size_t(1)
                                        , std::multiplies<std::size_t>()
                                        );

        std::size_t hi = std::accumulate( input.extent().data()+red
                                        , input.extent().data()+dim
                                        , std::size_t(1)
                                        , std::multiplies<std::size_t>()
                                        );

        nt2::partial_fold( reshape(a0, of_size(lo, hi))
                         , reshape(input, of_size(lo, input.extent()[red-1], hi))
                         , typename nt2::make_functor<Neutral1, A0>::type()
                         , typename nt2::make_functor<O1, A0>::type()
                         );
      #endif
      }
#endif
      return a0;
    }
    
    inline std::size_t reduction_dim(A1&, boost::mpl::false_)
    {
      return 1;
    }
    
    inline std::size_t reduction_dim(A1& a1, boost::mpl::true_)
    {
      return nt2::run(boost::proto::child_c<1>(a1));
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
