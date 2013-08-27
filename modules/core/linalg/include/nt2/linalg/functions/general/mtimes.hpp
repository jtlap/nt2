//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED

#include <nt2/linalg/functions/mtimes.hpp>
#include <nt2/linalg/details/blas/mm.hpp>
#include <nt2/core/functions/ctranspose.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/alias.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <boost/proto/traits.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, int N,class Expr>
  struct size_of<tag::mtimes_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;

    typedef typename child0::extent_type sz0;
    typedef typename child1::extent_type sz1;

    typedef of_size_< mpl_value< typename boost::fusion::result_of::at_c<sz0, 0>::type>::value
                    , mpl_value< typename boost::fusion::result_of::at_c<sz1, 1>::type>::value
                    >  result_type;

    result_type operator()(Expr& e) const
    {
      sz0 const& size0 = boost::proto::child_c<0>(e).extent();
      sz1 const& size1 = boost::proto::child_c<1>(e).extent();

      BOOST_ASSERT_MSG( ndims(size0) <= 2 && ndims(size1) <= 2
                      , "Inputs must be 2-D, or at least one input must be scalar"
                      );

      BOOST_ASSERT_MSG( boost::fusion::at_c<1>(size0) == boost::fusion::at_c<0>(size1)
                      , "Inner dimensions must agree"
                      );

      return result_type( boost::fusion::at_c<0>(size0)
                        , boost::fusion::at_c<1>(size1)
                        );
    }
  };
} }

namespace nt2 { namespace ext
{
  // Recognize scalar/matrix, matrix/scalar and scalar/scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(T1)(N1)
                            , (scalar_< unspecified_<A0> >)
                              ((expr_< generic_< unspecified_<A1> >, T1, N1 >))
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(T0)(N0)(A1)
                            , ((expr_< generic_< unspecified_<A0> >, T0, N0 >))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  #if 0
  // Recognize transpose
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::mtimes_, tag::cpu_
                               , (A0)(A1)(T1)(N1)
                               , (is_real<typename A0::value_type>)
                               , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                                 ((node_< A1, T1, N1 , nt2::container::domain>))
                               )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::mtimes_, tag::cpu_
                               , (A0)(T0)(N0)(A1)
                               , (is_real<typename A1::value_type>)
                               , ((node_< A0, T0, N0 , nt2::container::domain>))
                                 ((node_< A1, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                               )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::mtimes_, tag::cpu_
                               , (A0)(A1)
                               , (mpl::and_< is_real<typename A0::value_type>
                                           , is_real<typename A1::value_type>
                                           >)
                               , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                                 ((node_< A1, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                               )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  // Recognize ctranspose
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(T1)(N1)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((node_< A1, T1, N1 , nt2::container::domain>))
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(T0)(N0)(A1)
                            , ((node_< A0, T0, N0 , nt2::container::domain>))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  // Recognize alpha
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<2> , nt2::container::domain>))
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_
                            , (A0)(A1)
                            , ((node_< A0, nt2::tag::mtimes_, boost::mpl::long_<2> , nt2::container::domain>))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };
  #endif

  // run_assign
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<2> , nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      using boost::fusion::at_c;
      typedef typename A1::value_type value_type;

      if(at_c<1>(boost::proto::child_c<0>(a1).extent()) == 0u)
      {
        a0 = zeros(a1.extent(), meta::as_<value_type>());
        return a0;
      }

      typedef typename meta::kind_<A1>::type container_kind;
      typedef nt2::memory::container<container_kind,value_type, nt2::_2D> desired_semantic;
      typename container::as_terminal<desired_semantic, typename boost::proto::result_of::child_c<A1&, 0>::type>::type child0 = boost::proto::child_c<0>(a1);
      typename container::as_terminal<desired_semantic, typename boost::proto::result_of::child_c<A1&, 1>::type>::type child1 = boost::proto::child_c<1>(a1);
      typename container::as_terminal<desired_semantic, A0&>::type result = container::as_terminal<desired_semantic, A0&>::init(a0);

      value_type alpha = One<value_type>();
      value_type beta = Zero<value_type>();
      nt2_la_int m = at_c<0>(child0.extent());
      nt2_la_int n = at_c<1>(child1.extent());
      nt2_la_int k = at_c<1>(child0.extent());
      nt2_la_int lda = at_c<0>(child0.extent());
      nt2_la_int ldb = at_c<0>(child1.extent());
      nt2_la_int ldc = at_c<0>(a1.extent());

      typedef typename container::as_terminal<desired_semantic>::type dummy_type;
      typedef typename container::as_view_impl<dummy_type>::type view_type;

      dummy_type dummy;
      view_type result_view;
      bool swap = (void*)&result != (void*)&a0;

      if( swap || ( container::alias(result, child0) || container::alias(result, child1) ) )
      {
        // overlapping of input and output data
        // so we provide dummy space and put it back in result later
        dummy.resize(a1.extent());
        result_view.reset(dummy);
        swap = true;
      }
      else
      {
        result.resize(a1.extent());
        result_view.reset(result);
      }

      nt2::details::
      gemm( "N", "N"
          , &m, &n, &k
          , &alpha
          , child0.raw(), &lda
          , child1.raw(), &ldb
          , &beta
          , result_view.raw(), &ldc
          );

      if(swap)
        container::assign_swap(a0, dummy);
      return a0;
    }
  };

} }

#endif

