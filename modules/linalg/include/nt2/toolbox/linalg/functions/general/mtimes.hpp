//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/mtimes.hpp>
#include <nt2/toolbox/linalg/details/blas/mm.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/table/category.hpp>
//#include <nt2/core/settings/forward/size.hpp>
#include <boost/proto/traits.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace tag
{
  struct ctranspose_;
} }

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::mtimes_, Domain, 2, Expr>
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
} } }

namespace nt2 { namespace ext
{
  // Recognize scalar/matrix, matrix/scalar and scalar/scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((expr_< scalar_< unspecified_<A0> >, T0, N0 >))
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
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((expr_< generic_< unspecified_<A0> >, T0, N0 >))
                              ((expr_< scalar_< unspecified_<A1> >, T1, N1 >))
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((expr_< scalar_< unspecified_<A0> >, T0, N0 >))
                              ((expr_< scalar_< unspecified_<A1> >, T1, N1 >))
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  // FIXME: scalar/scalar duplicated for now
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

  // Recognize ctranspose
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(T1)(N1)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> >))
                              ((node_< A1, T1, N1 >))
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
                            , ((node_< A0, T0, N0 >))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> >))
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
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> >))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> >))
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
                            , (A0)(T0)(N0)(A1)
                            , ((expr_< scalar_< unspecified_<A0> >, T0, N0 >))
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<2> >))
                            )
  {
    typedef int result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return 0;
    }
  };

  // TODO: move this function to a better place
  template<class T>
  T* raw(T& t)
  {
    return &t;
  }

  template<class Container>
  typename memory::container_ref<Container>::pointer raw(memory::container_ref<Container> const& c)
  {
    return c.raw();
  }

  template<class Container, bool Own>
  typename memory::container_shared_ref<Container, Own>::pointer raw(memory::container_shared_ref<Container, Own> const& c)
  {
    return c.raw();
  }

  template<class T, class S>
  typename memory::container<T, S>::pointer raw(memory::container<T, S>& c)
  {
    return c.raw();
  }

  template<class T>
  typename boost::disable_if< boost::proto::is_expr<T>, T&>::type
  value(T& t)
  {
    return t;
  }

  template<class Expr>
  typename boost::lazy_enable_if< boost::proto::is_expr<Expr>,
                                  boost::proto::result_of::value<Expr&>
                                >::type
  value(Expr& expr)
  {
    return boost::proto::value(expr);
  }

  // run_assign
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<2> >))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      using boost::fusion::at_c;
      typedef typename A1::value_type value_type;
      typename meta::call<tag::run_(typename boost::proto::result_of::child_c<A1&, 0>::type)>::type child0 = nt2::run(boost::proto::child_c<0>(a1));
      typename meta::call<tag::run_(typename boost::proto::result_of::child_c<A1&, 1>::type)>::type child1 = nt2::run(boost::proto::child_c<1>(a1));
      typename meta::call<tag::run_(A0&)>::type result = nt2::run(a0);

      value_type alpha = One<value_type>();
      value_type beta = Zero<value_type>();
      nt2_la_int m = at_c<0>(child0.extent());
      nt2_la_int n = at_c<1>(child1.extent());
      nt2_la_int k = at_c<1>(child0.extent());
      nt2_la_int lda = at_c<0>(child0.extent());
      nt2_la_int ldb = at_c<0>(child1.extent());
      nt2_la_int ldc = at_c<0>(a1.extent());
      //    if((raw(value(result)) !=  child0.raw()) && (raw(value(result)) !=  child1.raw()))
      if(    ( raw(value(result)) >= child0.raw()+numel(child0) || raw(value(result))+numel(result) <  child0.raw())&&
             ( raw(value(result)) >= child1.raw()+numel(child0) || raw(value(result))+numel(result) <  child1.raw()))
      {
        a0.resize(a1.extent());
        nt2::details::
        gemm( "N", "N"
            , &m, &n, &k
            , &alpha
            , child0.raw(), &lda
            , child1.raw(), &ldb
            , &beta
            , raw(value(result)), &ldc
            );
      }
      else
      {
        // overlapping of input and output data is possible
        // so we provide space for result and put back in a0
        nt2::table<value_type> tmp(a1.extent());
        //tmp.resize(a1.extent());
        nt2::details::
        gemm( "N", "N"
            , &m, &n, &k
            , &alpha
            , child0.raw(), &lda
            , child1.raw(), &ldb
            , &beta
            , tmp.raw(), &ldc
            );
        result = tmp;
      }

      return a0 = result;
    }
  };

} }

#endif

