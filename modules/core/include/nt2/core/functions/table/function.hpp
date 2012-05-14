//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <nt2/core/functions/table/details/reindex.hpp>
#include <nt2/core/functions/table/details/function_size.hpp>
#include <nt2/core/functions/table/details/function_value_type.hpp>

namespace nt2 { namespace ext
{
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
    // Get the indexed expression
    typedef typename boost::proto::result_of::
                     child_c<Expr&, 0>::type                  child0;

    // ... and its base index types
    typedef typename boost::
            remove_reference<child0>::type::index_type::type  index_type;

    // Get the indexing expression pack
    typedef typename boost::proto::result_of::
                     child_c<Expr&, 1>::type                  childN;

    // ... and computes its number of index_t
    typedef typename meta::strip<childN>::type                      index_t;
    typedef typename boost::fusion::result_of::size<index_t>::type arity_t;

    // Compute a type able to hold the position we look for
    typedef typename nt2::make_size<arity_t::value>::type dims_t;
    typedef dims_t                                     source_subscript_t;

    // Once set, we build a type with evaluation targets
    typedef boost::array< boost::dispatch::meta::
                          as_< typename boost::dispatch::meta::
                               as_integer< typename boost::dispatch::meta::
                                           scalar_of<Data>::type
                                         >::type
                             >
                        , arity_t::value-1
                        >                                     target_base;

    typedef typename boost::fusion::result_of::
            as_vector< typename boost::fusion::result_of::
                       push_front< target_base
                                 , typename details::as_integer_target<Data>::type
                                 >::type
                     >::type                                  target_type;

    // We use a zip_view for passign all those informations to relative_index
    typedef boost::fusion::vector< childN const&
                                 , index_type const&
                                 , dims_t const&
                                 , source_subscript_t const&
                                 , target_type const&
                                 >                            seq;

    typedef boost::fusion::zip_view<seq>                      zipped;
    typedef boost::fusion::
            transform_view<zipped const, details::reindex>  transformed;

    // Compute the result type for index computation
    typedef typename meta::
            call<tag::sub2ind_
                  ( typename meta::call<tag::extent_(child0)>::type
                  , transformed const&
                  , index_type const&
                  )
                >::type                                       idx;

    // Finally, we compute the actual return type after indexing
    typedef typename meta::call < tag::run_ ( child0
                                            , idx const&
                                            , Data const&
                                            )
                                >::type                       result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, State const& state, Data const& data) const
    {
      // Compute base index of the source expression
      index_type indexes;

      // Grab the destination subscript
      source_subscript_t pos = ind2sub(expr.extent(), state, indexes);

      // Apply index_t to each subscript value
      transformed trs = boost::fusion::
                        transform(  zipped
                                    ( seq ( boost::proto::child_c<1>(expr)
                                          , indexes
                                          , boost::proto::value
                                            (boost::proto::child_c<2>(expr))
                                          , pos
                                          , target_type()
                                          )
                                    )
                                 , details::reindex()
                                 );

      // Get the linear position from the transformed subscript and evaluate
      return nt2::run ( boost::proto::child_c<0>(expr)
                      , sub2ind ( boost::proto::child_c<0>(expr).extent()
                                , trs
                                , indexes
                                )
                      , data
                      );
    }
  };
} }

#endif
