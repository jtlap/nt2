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

#include <nt2/include/functor.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/function.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/is_colon.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <nt2/core/functions/table/details/function/size.hpp>
#include <nt2/core/functions/table/details/function/value_type.hpp>

#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/make_position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <nt2/core/functions/table/details/relative_view/relative_view.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/include/as_vector.hpp>

namespace nt2
{
  namespace ext
  {
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
                       child_c<Expr const&, 0>::type child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type pop_front_expr_type;
        
      typedef typename boost::fusion::result_of::
                       as_vector<typename boost::array<int, Arity::value-1> >::type scalar_access_type;
      typedef typename nt2::meta::make_position<child0, scalar_access_type>::type position_type;
      typedef typename nt2::relative_view<pop_front_expr_type, boost::mpl::int_<Arity::value-1>, scalar_access_type> relative_view_type;

      typedef typename meta::call<tag::run_(child0, position_type const&, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr const& expr, State const& state, Data const& data) const
      {
        position_type p( relative_view_type( boost::fusion::pop_front(expr), boost::mpl::int_<Arity::value-1>(), scalar_access_type() ) );

        return nt2::run( boost::proto::child_c<0>(expr), as_unaligned(p), data );
      }
    };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                              , (Expr)(Seq)(A)(Data)(Arity)
                              , ((expr_< unspecified_<Expr>
                                       , nt2::tag::function_
                                       , Arity
                                       >
                                ))
                                ((position_<Seq, A>))
                                (unspecified_<Data>)
                              )
    {
      typedef typename boost::proto::result_of::
                       child_c<Expr const&, 0>::type child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type pop_front_expr_type;

      typedef typename boost::fusion::result_of::
                       as_vector<typename boost::array<int, Arity::value-1> >::type scalar_access_type;
      typedef typename nt2::meta::make_position<child0, scalar_access_type>::type position_type;
      typedef typename nt2::relative_view<pop_front_expr_type, boost::mpl::int_<Arity::value-1>, scalar_access_type> relative_view_type;

      typedef typename meta::call<tag::run_(child0, Seq const&, Data const&)>::type result_type;        

      BOOST_FORCEINLINE result_type
      operator()(Expr const& expr, Seq const& state, Data const& data) const
      {
        position_type p( relative_view_type( boost::fusion::pop_front(expr), boost::mpl::int_<Arity::value-1>(), scalar_access_type() ) );

        return nt2::run( boost::proto::child_c<0>(expr), as_unaligned(p), data );
      }
    };
  }
}

#endif
