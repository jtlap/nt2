//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/core/functions/table/details/function/size.hpp>
#include <nt2/core/functions/table/details/function/value_type.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/make_position.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <nt2/core/utility/of_size/of_size.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/sub2sub.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace nt2
{
  namespace ext
  {
    struct relative_view_call
    {
      template<typename T>
      struct result;

      template<typename T>
      struct result<relative_view_call(T)>
        : nt2::meta::call<nt2::tag::relative_index_(
            typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 0>::type,
            typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 1>::type
          )>
      {
      };

      template <typename T>
      typename result<relative_view_call(T const&)>::type
      operator()(T const& t) const
      {
        return nt2::relative_index(boost::fusion::at_c<0>(t), boost::fusion::at_c<1>(t));
      }
    };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                              , (Expr)(State)(Data)(Arity)
                              , ((expr_< unspecified_<Expr>
                                       , nt2::tag::function_
                                       , Arity
                                       >
                                ))
                                (fusion_sequence_<State>)
                                (unspecified_<Data>)
                              )
    {
      typedef typename boost::proto::result_of::
                       child_c<Expr&, 0>::type                               child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type childN;

      typedef typename nt2::make_size< boost::fusion::result_of::size<State>::type::value >::type reinterpreted_size;

      typedef typename meta::
              call<tag::sub2sub_( reinterpreted_size const&
                                , State
                                , typename meta::call<tag::extent_(Expr&)>::type
                                )
                  >::type pos;

      typedef typename nt2::make_size< Arity::value-1 >::type reinterpreted_pos;

      typedef boost::fusion::vector< childN const&
                                   , reinterpreted_pos const&
                                   > seq;
      typedef boost::fusion::zip_view<seq> zipped;
      typedef boost::fusion::transform_view<zipped const, relative_view_call> transformed;

      typedef typename nt2::meta::make_position<child0, transformed, unaligned_>::type position_type;
      typedef typename meta::call<tag::run_(child0, position_type const&, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr& expr, State& state, Data const& data) const
      {
        childN children = boost::fusion::pop_front(expr);
        reinterpreted_pos pos = sub2sub(reinterpreted_size(expr.extent()), state, expr.extent());
        position_type p( boost::fusion::transform(zipped(seq(children, pos)), relative_view_call()) );

        return nt2::run( boost::proto::child_c<0>(expr), p, data );
      }
    };
  }
}

#endif
