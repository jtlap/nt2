/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_DSL_COMPUTE_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_COMPUTE_HPP_INCLUDED

#include <boost/dispatch/dsl/compile.hpp>
#include <boost/dispatch/functor/functor.hpp>

////////////////////////////////////////////////////////////////////////////////
// compute evaluates an AST by passing its elements through a raw functor
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
    template <typename Tag, typename Target>
    struct compute;
    
    namespace detail
    {
        template <typename Tag, typename Target, typename Expr, typename State, typename Data>
        struct compute_impl;
        
        template <typename Tag, typename Target, typename Expr>
        struct compute_impl<Tag, Target, Expr, int, int>
            : boost::proto::transform_impl<Expr, int, int>
        {
            typedef 
                boost::proto::unpack<
                    boost::proto::call<
                        functor<Tag, Target>
                    >(
                        compile<
                            compute<
                                boost::mpl::_1
                              , Target
                            >
                        >
                    )
                >
                what;
            
            typedef
                typename what::template impl<Expr, int, int>::result_type
                result_type;
            
            result_type
            operator()(
                typename compute_impl::expr_param expr
              , typename compute_impl::state_param
              , typename compute_impl::data_param
            ) const
            {
                return what()(expr);
            }
        };
        
        template <typename Tag, typename Target, typename Expr, typename State>
        struct compute_impl<Tag, Target, Expr, State, int>
            : boost::proto::transform_impl<Expr, State, int>
        {
            typedef 
                boost::proto::unpack<
                    boost::proto::call<
                        functor<Tag, Target>
                    >(
                        compile<
                            compute<
                                boost::mpl::_1
                              , Target
                            >
                        >
                      , proto::_state
                    )
                >
                what;
            
            typedef
                typename what::template impl<Expr, State, int>::result_type
                result_type;
            
            result_type
            operator()(
                typename compute_impl::expr_param expr
              , typename compute_impl::state_param state
              , typename compute_impl::data_param
            ) const
            {
                return what()(expr, state);
            }
        };
        
        template <typename Tag, typename Target, typename Expr, typename State, typename Data>
        struct compute_impl
            : boost::proto::transform_impl<Expr, State, Data>
        {
            typedef 
                boost::proto::unpack<
                    boost::proto::call<
                        functor<Tag, Target>
                    >(
                        compile<
                            compute<
                                boost::mpl::_1
                              , Target
                            >
                        >
                      , proto::_state
                      , proto::_data
                    )
                >
                what;
            
            typedef
                typename what::template impl<Expr, State, Data>::result_type
                result_type;
            
            result_type
            operator()(
                typename compute_impl::expr_param expr
              , typename compute_impl::state_param state
              , typename compute_impl::data_param data
            ) const
            {
                return what()(expr, state, data);
            }
        };
    }
    
    template <typename Tag, typename Target>
    struct compute
        : boost::proto::transform<compute<Tag, Target> >
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : detail::compute_impl<Tag, Target, Expr, State, Data>
        {};
    };
    
} } }

namespace boost { namespace proto
{
    template<class Tag, class Target>
    struct  is_callable<boost::dispatch::meta::compute<Tag, Target> >
        : boost::mpl::true_
    {};
} }

#endif
