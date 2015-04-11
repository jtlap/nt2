//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SWAR_CSORT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SWAR_CSORT_HPP_INCLUDED

#include <nt2/include/functions/csort.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/is_less.hpp>
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
#include <boost/type_traits/is_integral.hpp>
#include <boost/mpl/not.hpp>
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

  BOOST_DISPATCH_IMPLEMENT  ( csort_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A2>)
                              (scalar_<integer_<A1>>)
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
//    typedef typename nt2::result_of::as_subscript<ext_t,size_t>::type     sub_t;

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
      typedef typename boost::proto::result_of::child_c<A0&,1>::value_type       child1;
      typedef typename boost::dispatch::meta::semantic_of<child1>::type      semantic_t;
      typedef typename boost::is_integral<semantic_t>::type                    is_int_t;
      typedef typename boost::mpl::not_<is_int_t>::type                    not_is_int_t;
      return getdirection2(a0, not_is_int_t());
    }

    BOOST_FORCEINLINE
    std::size_t getdirection2 ( A0& a0, boost::mpl::true_ const&
                             ) const
    {
      return firstnonsingleton(boost::proto::child_c<1>(a0));
    }

    BOOST_FORCEINLINE
    std::size_t getdirection2 ( A0& a0, boost::mpl::false_ const&
                             ) const
    {
      return boost::proto::child_c<1>(a0);
    }


    BOOST_FORCEINLINE
    std::size_t getdirection ( A0& a0, boost::mpl::long_<3> const&
                             ) const
    {
      return boost::proto::value(boost::proto::child_c<2>(a0)); //dim is always last or absent
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<3> const&   // 3 inputs
              , boost::mpl::long_<1> const&   // 1 output
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      do_sort1(res, dim, cmp);
    }

    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<1> const&   // 1 input
              , boost::mpl::long_<1> const&   // 1 output
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = [](type_t a, type_t b)->bool{ return le(a, b); };
      do_sort1(res, dim, cmp);
    }

    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<2> const&   // 2 inputs
              , boost::mpl::long_<1> const&   // 1 output
              ) const
    {
      typedef typename boost::proto::result_of::child_c<A0&,1>::value_type       child1;
      typedef typename boost::dispatch::meta::semantic_of<child1>::type      semantic_t;
      typedef typename boost::is_integral<semantic_t>::type                    is_int_t;
      typedef typename boost::mpl::not_<is_int_t>::type                    not_is_int_t;
      return eval1(a0, a1, dim, not_is_int_t());
    }

    BOOST_FORCEINLINE
    void eval1 ( A0& a0, A1& a1, std::size_t dim
               , boost::mpl::false_ const & // 2nd parameter is direction
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = [](type_t a, type_t b)->bool{ return le(a, b); };
      do_sort1(res, dim, cmp);
    }

    BOOST_FORCEINLINE
    void eval1 ( A0& a0, A1& a1, std::size_t dim
               , boost::mpl::true_ const & // 2nd parameter is comp
              ) const
    {
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      do_sort1(res, dim, cmp);
    }

    template < class RES, class CMP> static BOOST_FORCEINLINE
    void do_sort1( RES & res, std::size_t dim, CMP & cmp)
    {
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        auto pos = nt2::as_subscript(res.extent(), p);
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
      NT2_AS_TERMINAL_OUT (i_semantic, inds
                          , boost::proto::child_c<1>(a1));
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      do_sort2(inds, res, dim, cmp);
    }

    BOOST_FORCEINLINE
      void eval ( A0& a0, A1& a1, std::size_t dim
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      typedef typename boost::proto::result_of::child_c<A0&,1>::value_type       child1;
      typedef typename boost::dispatch::meta::semantic_of<child1>::type      semantic_t;
      typedef typename boost::is_integral<semantic_t>::type                    is_int_t;
      typedef typename boost::mpl::not_<is_int_t>::type                    not_is_int_t;
      return eval2(a0, a1, dim, not_is_int_t());

    }


    BOOST_FORCEINLINE
    void eval2 ( A0& a0, A1& a1, std::size_t dim
               , boost::mpl::false_ const & // 2nd parameter is direction
               ) const
    {
      NT2_AS_TERMINAL_OUT (i_semantic, inds
                          , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = [](type_t a, type_t b)->bool{ return le(a, b); };
      do_sort2(inds, res, dim, cmp);
    }

    BOOST_FORCEINLINE
    void eval2 ( A0& a0, A1& a1, std::size_t dim
               , boost::mpl::true_ const & // 2nd parameter is comp
              ) const
    {
      NT2_AS_TERMINAL_OUT (i_semantic, inds
                          , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_INOUT (o_semantic, res
                            , boost::proto::child_c<0>(a0)
                            , boost::proto::child_c<0>(a1));
      auto cmp = boost::proto::value(boost::proto::child_c<1>(a0));
      do_sort2(inds, res, dim, cmp);
    }


    template < class IND,  class RES, class CMP> static BOOST_FORCEINLINE
    void do_sort2(IND & inds, RES & res, std::size_t dim, CMP & cmp)
    {
      inds.resize(res.extent());
      std::size_t h =  size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  nt2::numel(res)/h;
      std::size_t stride = nt2::linesstride(res, dim);
      std::size_t decal =  stride*(nt2::size(res, dim)-1);
      std::size_t p = 0;
      auto range = evaluate(oneplus(_(0u, h-1)*stride));
      for(size_t i=0; i < nbslice; ++i)
      {
        auto pos = nt2::as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0) p += decal;
        tab_t tmp = res(p+range);
        itab_t idx = _(One<std::size_t>(), numel(tmp));
        auto cmpi = [&cmp, &tmp](size_t i1, size_t i2) {return cmp(tmp(i1), tmp(i2));};

        std::sort(idx.begin(), idx.end(), cmpi);
        inds(p+range) = idx;
        res(p+range) = tmp(idx);
        ++p;
      }
    }


  };
} }

#endif
