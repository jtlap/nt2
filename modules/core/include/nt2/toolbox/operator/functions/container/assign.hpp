//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_ASSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_CONTAINER_ASSIGN_HPP_INCLUDED

#include <nt2/toolbox/operator/functions/assign.hpp>
#include <nt2/core/container/dsl/generator.hpp>

namespace nt2 { namespace container { namespace ext
{
  // size is that of left-hand side
  template<class Domain, class Expr>
  struct size_of<tag::assign_, Domain, 2, Expr>
  {
    template<class A0, class A1, class Dummy = void>
    struct select;

    template<class A1, class Dummy>
    struct select<_0D, A1, Dummy>
    {
      typedef A1 type;
      BOOST_FORCEINLINE type operator()(_0D const&, A1 const& a1) const
      {
        return a1;
      }
    };

    template<class A0, class Dummy>
    struct select<A0, _0D, Dummy>
    {
      typedef A0 type;
      BOOST_FORCEINLINE type operator()(A0 const& a0, _0D const&) const
      {
        return a0;
      }
    };

    template<class Dummy>
    struct select<_0D, _0D, Dummy>
    {
      typedef _0D type;
      BOOST_FORCEINLINE type operator()(_0D const& a0, _0D const&) const
      {
        return a0;
      }
    };

    template<class A0, class A1, class Dummy>
    struct select
    {
      typedef typename boost::mpl::if_c< A0::static_status,A0,A1>::type type;

      BOOST_FORCEINLINE type operator()(A0 const& a0, A1 const& a1) const
      {
        return selection(a0,a1,boost::mpl::bool_<A0::static_status>());
      }

      BOOST_FORCEINLINE type
      selection(A0 const& a0, A1 const&, boost::mpl::true_ const&) const
      {
        return a0;
      }

      BOOST_FORCEINLINE type
      selection(A0 const& , A1 const& a1, boost::mpl::false_ const&) const
      {
        return a1;
      }
    };

    typedef typename boost::proto::result_of::
    child_c<Expr, 0>::type                          child0;

    typedef typename boost::proto::result_of::
    child_c<Expr, 1>::type                          child1;

    typedef typename child0::extent_type            size0_t;
    typedef typename child1::extent_type            size1_t;

    typedef select< typename meta::strip<size0_t>::type
                  , typename meta::strip<size1_t>::type
                  >                                       impl;
    typedef typename impl::type                           result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return impl() ( boost::proto::child_c<0>(e).extent()
                    , boost::proto::child_c<1>(e).extent()
                    );
    }
  };
} } }

#endif
