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
#include <nt2/include/functions/numel.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/core/functions/table/details/function/size.hpp>
#include <nt2/core/functions/table/details/function/value_type.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/make_position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform_view.hpp>

namespace nt2
{
  namespace ext
  {
    namespace details
    {
      template <typename T>
      inline
      T get_pos(boost::fusion::vector0<void> const&)
      {
        return T();
      }

      template <typename T>
      inline
      T const& get_pos(T const& s)
      {
        return s;
      }
    }

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
                       child_c<Expr&, 0>::type child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type pop_front_expr_type;

      typedef typename boost::fusion::result_of::
                       as_vector<typename boost::array<int const, Arity::value-1> >::type scalar_access_type;
      typedef typename nt2::meta::strip<State>::type stripped_sequence_type;

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

      typedef typename boost::mpl::if_<boost::is_same< typename meta::strip<State>::type, boost::fusion::vector0<void> >,
          scalar_access_type, State>::type new_type;
      typedef boost::fusion::vector<const pop_front_expr_type&, const new_type&> seq;
      typedef boost::fusion::zip_view<seq> zipped;
      typedef boost::fusion::transform_view<zipped const, relative_view_call> view_type;

      typedef typename nt2::meta::make_position<child0, view_type>::type position_type;
      typedef typename meta::call<tag::run_(child0, position_type const&, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr const& expr, State const& state, Data const& data) const
      {
        position_type p(transform(zipped(seq(boost::fusion::pop_front(expr), details::get_pos<new_type>(state))), relative_view_call()));

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
                       child_c<Expr&, 0>::type child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type pop_front_expr_type;

      typedef typename boost::fusion::result_of::
                       as_vector<typename boost::array<int const, Arity::value-1> >::type scalar_access_type;
      typedef typename nt2::meta::strip<typename Seq::sequence_type>::type stripped_sequence_type;

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

      typedef typename boost::mpl::if_<boost::is_same< typename meta::strip<typename Seq::sequence_type>::type, boost::fusion::vector0<void> >,
      scalar_access_type, typename Seq::sequence_type>::type new_type;
      typedef boost::fusion::vector<const pop_front_expr_type&, const new_type&> seq;
      typedef boost::fusion::zip_view<seq> zipped;
      typedef boost::fusion::transform_view<zipped const, relative_view_call> view_type;

      typedef typename nt2::meta::make_position<child0, view_type>::type position_type;
      typedef typename meta::call<tag::run_(child0, position_type const&, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr const& expr, Seq const& state, Data const& data) const
      {
        position_type p( transform(zipped(seq(boost::fusion::pop_front(expr), details::get_pos<new_type>(state.seq_))), relative_view_call()) );

        return nt2::run( boost::proto::child_c<0>(expr), as_unaligned(p), data );
      }
    };
  }
}

#endif
