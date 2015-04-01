//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SWAR_CSORT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SWAR_CSORT_HPP_INCLUDED

#include <nt2/include/functions/csort.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/linesstride.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <algorithm>

namespace nt2 { namespace ext
{
  //============================================================================
  //CSORT Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( csort_, tag::cpu_
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

  BOOST_DISPATCH_IMPLEMENT  ( csort_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<integer_<A1>>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( csort_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<integer_<A1>>)
                              (unspecified_<A2>)
                           )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      return a0;
    }
  };

  //============================================================================
  //CSORT
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( csort_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::csort_
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
      std::size_t dim = getdirection(a0, N0());
      boost::proto::child_c<0>(a1) =  boost::proto::child_c<0>(a0);
      eval(a0, a1, dim, N0(), N1());
    }
  private:
    BOOST_FORCEINLINE
    std::size_t getdirection ( A0& a0, boost::mpl::long_<1> const&
                             ) const
    {
      return firstnonsingleton(boost::proto::child_c<0>(a0));
    }

    BOOST_FORCEINLINE
    std::size_t getdirection ( A0& a0, boost::mpl::long_<2> const&
                             ) const
    {
      return boost::proto::value(boost::proto::child_c<1>(a0));
    }

    BOOST_FORCEINLINE
    std::size_t getdirection ( A0& a0, boost::mpl::long_<3> const&
                             ) const
    {
      return boost::proto::value(boost::proto::child_c<1>(a0));
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      auto cmp = boost::proto::value(boost::proto::child_c<2>(a0));
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        std::sort(tmp.begin(), tmp.end(), cmp);
        res(p+range) = tmp;
        ++p;
      }
    }

    template < long N> BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<N> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      auto cmp = [](type_t a, type_t b){ return a < b; };
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        std::sort(tmp.begin(), tmp.end(), cmp);
        res(p+range) = tmp;
        ++p;
      }
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT (i_semantic, indices
                          , boost::proto::child_c<1>(a1));
      indices.resize(res.extent());
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      auto cmp = boost::proto::value(boost::proto::child_c<2>(a0));
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        itab_t idx = _(1u, numel(tmp));
        auto cmpi = [&tmp, &cmp](size_t i1, size_t i2) {return cmp(tmp(i1), tmp(i2));};

        std::sort(idx.begin(), idx.end(), cmpi);
        indices(p+range) = idx;
        res(p+range) = tmp(idx);
        ++p;
      }
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT (i_semantic, indices
                          , boost::proto::child_c<1>(a1));
      indices.resize(res.extent());
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        itab_t idx = _(1u, numel(tmp));
        auto cmpi = [&tmp](size_t i1, size_t i2) {return (tmp(i1) < tmp(i2));};

        std::sort(idx.begin(), idx.end(), cmpi);
        indices(p+range) = idx;
        res(p+range) = tmp(idx);
        ++p;
      }
    }
  };
} }

#endif
