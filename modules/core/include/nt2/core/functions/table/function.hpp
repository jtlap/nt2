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
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/relative_index.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
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
            typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 0>::type
          , typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 1>::type
          , typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 2>::type
          , typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 3>::type
          , typename boost::fusion::result_of::at_c<typename boost::remove_reference<T>::type const, 4>::type
          )>
      {
      };

      template <typename T>
      typename result<relative_view_call(T const&)>::type
      operator()(T const& t) const
      {
        return nt2::relative_index( boost::fusion::at_c<0>(t)
                                  , boost::fusion::at_c<1>(t)
                                  , boost::fusion::at_c<2>(t)
                                  , boost::fusion::at_c<3>(t)
                                  , boost::fusion::at_c<4>(t)
                                  );
      }
    };

    template<class T>
    struct as_integer_target
    {
      // Remove any potential logical<> and turn into integers
      typedef typename boost::simd::meta::as_arithmetic<T>::type        arith_t;
      typedef typename boost::dispatch::meta::as_integer<arith_t>::type base_t;
      typedef boost::dispatch::meta::as_<base_t>                        type;
    };

    template<class T>
    struct as_integer_target< boost::dispatch::meta::as_<T> >
     : as_integer_target<T>
    {
    };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                              , (Expr)(State)(Data)(Arity)
                              , ((expr_< unspecified_<Expr>
                                       , nt2::tag::function_
                                       , Arity
                                       >
                                ))
                                (generic_< integer_<State> >)
                                (unspecified_<Data>)
                              )
    {
      typedef typename boost::proto::result_of::
                       child_c<Expr&, 0>::type                               child0;
      typedef typename boost::fusion::result_of::pop_front<Expr const>::type childN;

      typedef typename boost::
              remove_reference<child0>::type::index_type::type               index_type;
      typedef typename nt2::make_size< Arity::value-1 >::type                size_type;
      typedef size_type                                                      pos_type;

      typedef boost::array< boost::dispatch::meta::
                            as_< typename boost::dispatch::meta::
                                 as_integer< typename boost::dispatch::meta::
                                             scalar_of<Data>::type
                                           >::type
                               >
                          , Arity::value-2
                          >                                                  target_base;

      typedef typename boost::fusion::result_of::
              as_vector< typename boost::fusion::result_of::
                         push_front< target_base
                                   , typename as_integer_target<Data>::type
                                   >::type
                       >::type                                               target_type;

      typedef boost::fusion::vector< childN const&
                                   , index_type const&
                                   , size_type const&
                                   , pos_type const&
                                   , target_type const&
                                   > seq;

      typedef boost::fusion::zip_view<seq> zipped;
      typedef boost::fusion::transform_view<zipped const, relative_view_call> transformed;

      typedef typename meta::
              call<tag::sub2ind_( typename meta::call<tag::extent_(child0)>::type
                                , transformed const&
                                , index_type const&
                                )
                  >::type idx;

      typedef typename meta::call<tag::run_(child0, idx const&, Data const&)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr& expr, State const& state, Data const& data) const
      {
        // Retrieve children from the node that contain the indexers
        childN children       = boost::fusion::pop_front(expr);

        index_type indexes;
        size_type sz = boost::proto::child_c<0>(expr).extent();

        // Get the subscript from the linear position
        pos_type pos = ind2sub(expr.extent(), state, indexes);

        // Apply indexers to each subscript value
        target_type targets;
        transformed trs = boost::fusion::
                          transform( zipped( seq( children
                                                , indexes
                                                , sz
                                                , pos
                                                , targets
                                                )
                                           )
                                   , relative_view_call()
                                   );

        // Get the new linear position from the transformed subscript
        idx p = sub2ind( boost::proto::child_c<0>(expr).extent(), trs, indexes );

        // Evaluate the data
        return nt2::run( boost::proto::child_c<0>(expr), p, data );
      }
    };
  }
}

#endif
