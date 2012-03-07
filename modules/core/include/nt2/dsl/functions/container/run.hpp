//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/make_position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Assignment of tables evaluates the right-hand-side in read mode and passes
  // the result to the left-hand-side for writing
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(Position)(Target)
                            , ((expr_< unspecified_<A0>
                                     , nt2::tag::assign_
                                     , boost::mpl::long_<2>
                                     >
                              ))
                              (fusion_sequence_<Position>)
                              (target_<unspecified_<Target> >)
                            )
  {
    typedef typename boost::proto::result_of::
            child_c<A0 const&, 0>::type                             result_type;
    typedef typename nt2::meta::make_position<result_type, Position>::type position_type;

    result_type operator()(A0 const& a0, Position const& pos, Target const&) const
    {
      position_type p(pos);

      nt2::run( boost::proto::child_c<0>(a0)
              , as_aligned(p)
              , nt2::run( boost::proto::child_c<1>(a0)
                        , as_aligned(p)
                        , Target()
                        )
              );
      return boost::proto::child_c<0>(a0);
    }
  };

  //============================================================================
  // When an assign(lhs,rhs) expression is run, we perform the evaluation of rhs
  // then store it in lhs. Depending on the lhs nature (real terminal or a node
  // containing a call to any indexing function, the result of the evaluation is
  // returned, usually as non-const reference.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::assign_
                                     , boost::mpl::long_<2>
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      boost::proto::child_c<0>(a0).resize(a0.extent());

      typename A0::index_type::type bs;
      std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
      std::ptrdiff_t bound  = boost::fusion::at_c<0>(a0.extent()) + ilow;
      std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(a0.extent()));

      for(std::ptrdiff_t j=olow; j!=obound; ++j)
        for(std::ptrdiff_t i=ilow; i!=bound; ++i)
          nt2::run(a0, boost::fusion::vector_tie(i,j), meta::as_<stype>());

      return boost::proto::child_c<0>(a0);
    }
  };

  //============================================================================
  // When an arbitrary expression is run, we perform its evaluation into a
  // local temporary container of proper type. This temporary is then returned by
  // value.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)(T)(N)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::
    remove_reference< typename boost::dispatch::meta::
                      terminal_of< typename boost::dispatch::meta::
                                   semantic_of<A0 const&>::type
                                 >::type
                    >::type                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type tmp;
      run(assign(tmp, a0));
      return tmp;
    }
  };

  //============================================================================
  // When an assign(lhs,rhs) scalar expression is run, we perform a single
  // assignment of said scalar value.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_, (A0)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , nt2::tag::assign_
                                     , boost::mpl::long_<2>
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::scalar_of<result_type>::type>::type
            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      boost::proto::child_c<0>(a0).resize(a0.extent());

      nt2::run(a0, boost::fusion::vector0<>(), meta::as_<target_type>());
      return boost::proto::child_c<0>(a0);
    }
  };

  //============================================================================
  // When a scalar expression is run, we don't perform the operation into
  // a temporary, but rather directly return it.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(T)(N)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0 const&>::type                            result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::strip<result_type>::type stype;
      return nt2::run( a0, boost::fusion::vector0<>(), meta::as_<stype>() );
    }
  };
} }

#endif
