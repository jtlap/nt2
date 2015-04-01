//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SWAR_CGLOBALCSORT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SWAR_CGLOBALCSORT_HPP_INCLUDED

#include <nt2/include/functions/globalcsort.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/linesstride.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <algorithm>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //GLOBALCSORT Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( globalcsort_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( globalcsort_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                           )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };

  //============================================================================
  //GLOBALCSORT
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( globalcsort_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::globalcsort_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                  type_t;
    typedef typename container::table<type_t>                             tab_t;
    typedef typename meta::as_real<type_t>::type                        rtype_t;
    typedef typename container::table<std::size_t>                       itab_t;
    typedef typename child0::extent_type                                  ext_t;
    typedef typename nt2::result_of::as_subscript<ext_t,size_t>::type     sub_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>    o_semantic;
    typedef nt2::memory::container<tag::table_,std::size_t, nt2::_2D> i_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      boost::proto::child_c<0>(a1) =  boost::proto::child_c<0>(a0);
      eval(a0, a1, N0(), N1());
    }
  private:

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      tab_t tmp =  boost::proto::child_c<0>(a0);
      std::sort(tmp.begin(), tmp.end(), cmp);
      boost::proto::child_c<0>(a1) =  tmp;
    }

    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      auto cmp = [](type_t a, type_t b){ return a < b; };
      tab_t tmp =  boost::proto::child_c<0>(a0);
      std::sort(tmp.begin(), tmp.end(), cmp);
      boost::proto::child_c<0>(a1) = tmp;
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1
                , boost::mpl::long_<2> const&
                , boost::mpl::long_<2> const&
                ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      auto cmpi = [&cmp, &res](size_t i1, size_t i2) {return cmp(res(i1), res(i2));};
      itab_t idx = _(One<std::size_t>(), numel(res));
      std::sort(idx.begin(), idx.end(), cmpi);
      tab_t tmp = res(idx); //aliasing
      boost::proto::child_c<0>(a1) = reshape(tmp, res.extent());
      boost::proto::child_c<1>(a1) = reshape(idx, res.extent());
    }


    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1
                , boost::mpl::long_<1> const&
                , boost::mpl::long_<2> const&
                ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmpi = [&res](size_t i1, size_t i2) {return (res(i1) < res(i2));};
      itab_t idx = _(One<std::size_t>(), numel(res));
      std::sort(idx.begin(), idx.end(), cmpi);
      boost::proto::child_c<0>(a1) = res(idx);
      boost::proto::child_c<1>(a1)  = reshape(idx, res.extent());
    }
  };
} }

#endif
