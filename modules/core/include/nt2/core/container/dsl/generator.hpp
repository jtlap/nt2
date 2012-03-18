//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/sdk/meta/container_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <nt2/core/container/dsl/details/trait_transform.hpp>

namespace nt2 { namespace container
{
  namespace ext
  {
    //==========================================================================
    /*!
     * This extension point specify the way a given expression is build when
     * entering a proto::generator. By default, all NT2 expressions are built
     * the following way:
     *
     *  - the value_type of the expression is computed
     *  - the size of the expression is computed
     *  - if the size is _0D, then the expression will behave as its value_type
     *    else, it will behave as a container of the domain.
     *
     * cref qualifiers and other peculiarities of type are conserved all along
     * so the type is actually the most optimized possible.
     *
     * \tparam Tag    Top most tag of the expression
     * \tparam Domain Domain of the expression
     * \tparam Arity  Number of children of the expression
     * \tparam Expr   The expression itself
     *
    **/
    //==========================================================================
    template<class Tag, class Domain, int Arity, class Expr> struct generator
    {
      typedef typename value_type<Tag, Domain, Arity, Expr>::type   value_type;
      typedef typename size_of<Tag,Domain,Arity,Expr>::result_type  extent_type;
      typedef typename meta::strip<extent_type>::type               size_type;

      typedef typename boost::mpl::
      if_< boost::is_same< size_type, _0D >
         , value_type
         , typename boost::dispatch::meta::
           transfer_qualifiers< typename meta::container_of<Domain>::type
                                ::template
                                apply< typename meta::
                                       strip<value_type>::type
                                     , nt2::settings(size_type)
                                     >::type
                              , value_type
                              >::type
         >::type                                                    type;
      typedef expression< typename boost::
                          remove_const<Expr>::type
                        , type>                                     result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        return result_type(e);
      }
    };
  }

  //============================================================================
  /*!
   * proto::transform performing the computation of the type and the generation
   * of a nt2::container::expression
   **/
  //============================================================================
  template<class Domain>
  struct  generator_transform
        : details::trait_transform< ext::generator, Domain > {};
} }

#include <nt2/core/container/dsl/details/terminal.hpp>
#include <nt2/core/container/dsl/details/nullary_function.hpp>

#endif

