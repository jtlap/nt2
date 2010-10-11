#ifndef BOOST_PP_IS_ITERATING
/*******************************************************************************
 *               Copyright 2010 Thomas Heller
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef BOOST_PROTO_TRANSFORM_TRANSFORM_EXPR_HPP
#define BOOST_PROTO_TRANSFORM_TRANSFORM_EXPR_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>

namespace boost { namespace proto {

namespace detail {

    template <typename Fun, typename Expr, typename State, typename Data, long Arity = arity_of<Expr>::value>
    struct transform_expr_impl;

    template <typename Fun, typename Expr, typename State, typename Data>
    struct transform_expr_impl<Fun, Expr, State, Data, 0>
        : transform_impl<Expr, State, Data>
    {
        typedef typename
            uncvref<
                typename when<_, Fun>::template impl<Expr, State, Data>::result_type
            >::type
            transform_result;
        
        typedef typename domain_of<Expr>::type expr_domain;
        typedef typename tag_of<Expr>::type expr_tag;

        typedef typename
            result_of::make_expr<
                expr_tag
              , expr_domain
              , transform_result
            >::type
            result_type;

        result_type const
        operator()(
            typename transform_expr_impl::expr_param e
          , typename transform_expr_impl::state_param s
          , typename transform_expr_impl::data_param d
        ) const
        {
            return make_expr<expr_tag, expr_domain>(typename when<_, Fun>::template impl<Expr, State, Data>()(e,s,d));
        }

    };

#define BOOST_PROTO_TRANSFORM_RESULT_TYPE(Z, N, __) \
        typedef typename \
            uncvref< \
                    typename when<_, Fun>::template impl< \
                    typename result_of::child_c<Expr, N>::type \
                  , State \
                  , Data \
                >::result_type \
            >::type \
            BOOST_PP_CAT(transform_result, N);
    /**/

#define BOOST_PROTO_TRANSFORM_RESULT(Z, N, __) \
        BOOST_PP_CAT(transform_result, N) \
        BOOST_PP_CAT(tr, N) \
            = typename when<_, Fun>::template impl< \
                typename result_of::child_c<Expr, N>::type \
              , State \
              , Data \
            >()(proto::child_c<N>(e), s, d);
    /**/

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/transform_expr.hpp>))
    #include BOOST_PP_ITERATE()

#undef BOOST_PROTO_TRANSFORM_RESULT_TYPE
#undef BOOST_PROTO_TRANSFORM_RESULT
}

template <typename Fun>
struct transform_expr
    : transform<transform_expr<Fun> >
{
    template <typename Expr, typename State, typename Data>
    struct impl
        : detail::transform_expr_impl<Fun, Expr, State, Data>
    {};
};

template <typename Fun>
struct is_callable<transform_expr<Fun> >
    : mpl::true_
{};

}}

#endif

#else /* BOOST_PP_IS_ITERATING */

#define N BOOST_PP_ITERATION()

    template <typename Fun, typename Expr, typename State, typename Data>
    struct transform_expr_impl<Fun, Expr, State, Data, N>
        : transform_impl<Expr, State, Data>
    {
        BOOST_PP_REPEAT(N, BOOST_PROTO_TRANSFORM_RESULT_TYPE, _)

        typedef typename domain_of<Expr>::type expr_domain;
        typedef typename tag_of<Expr>::type expr_tag;

        typedef typename
            result_of::make_expr<
                expr_tag
              , expr_domain
              , BOOST_PP_ENUM_PARAMS(N, transform_result)
            >::type
            result_type;

        result_type const
        operator()(
            typename transform_expr_impl::expr_param e
          , typename transform_expr_impl::state_param s
          , typename transform_expr_impl::data_param d
        ) const
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_TRANSFORM_RESULT, _)

            return make_expr<expr_tag, expr_domain>(BOOST_PP_ENUM_PARAMS(N, tr));
        }
    };

#endif
