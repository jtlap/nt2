//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED

#include <nt2/core/functions/along.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/functions/table/details/reindex.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <boost/array.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<nt2::tag::along_, Domain, 3 ,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename nt2::make_size < c0_t::extent_type
                                      ::static_size
                                    >::type result_type;

    result_type operator()(Expr& expr) const
    {
      result_type sz = boost::proto::child_c<0>(expr).extent();
      std::size_t i = boost::proto::value(boost::proto::child_c<2>(expr));
      if(i <= result_type::static_size)
        sz[i-1] = numel(boost::proto::child_c<1>(expr));
      return sz;
    }
  };

  template<class Domain, class Expr>
  struct value_type<nt2::tag::along_, Domain, 3, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename meta::scalar_of<c0_t>::type type;
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0& a0, A1 const& a1),
      along(a0, a1, nt2::firstnonsingleton(a0))
    )
  };

  // TODO: take into account indexes
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_,
                              (A0)(State)(Data),
                              ((node_<A0, nt2::tag::along_, boost::mpl::long_<3> , nt2::container::domain>))
                              (generic_< arithmetic_<State> > )
                              (unspecified_<Data>)
                            )
  {
    typedef typename details::as_integer_target<Data>::type   i_t;
    typedef typename meta::as_signed<i_t>::type               si_t;
    typedef boost::array<si_t, A0::extent_type::static_size>  pos_type;

    typedef typename boost::proto::result_of::
                     child_c<A0&, 0>::value_type              child0;
    typedef typename meta::call< tag::run_( child0
                                          , i_t
                                          , Data const&
                                          )
                               >::type                        result_type;

    result_type operator()(A0& a0, State const& state, Data const& data) const
    {
      pos_type p = ind2sub(a0.extent(), nt2::enumerate<i_t>(state));
      std::size_t i = boost::proto::value(boost::proto::child_c<2>(a0));
      if(i <= pos_type::static_size)
        p[i-1] = relative_index( boost::proto::child_c<1>(a0)
                               , std::ptrdiff_t(1)
                               , a0.extent()[i-1]
                               , p[i-1]
                               , boost::dispatch::meta::as_<si_t>()
                               );
      return nt2::run ( boost::proto::child_c<0>(a0)
                      , sub2ind(boost::proto::child_c<0>(a0).extent(), p)
                      , data
                      );
    }
  };

} }

#endif
