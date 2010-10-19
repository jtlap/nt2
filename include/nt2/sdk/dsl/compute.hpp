/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPUTE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/dsl/proto/transform/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compile take any NT2 AST and evaluate them based on actions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace dsl
{
  template<class Actions>
  struct  compile
        : boost::proto::when< boost::proto::_
                            , Actions::template action<boost::proto::_>
                            >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // computation action
  //////////////////////////////////////////////////////////////////////////////

/*
  //////////////////////////////////////////////////////////////////////////////
  // Forward functor into compute for most tag
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class Locality = void>
  struct  compute : functors::functor<Tag,Locality>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Proto visitor for computing
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Locality = void>
  struct  compute_transform
        : boost::proto::
          unpack< compute<Tag,Locality> ( boost::proto::
                                          visitor <
                                              compute_transform < boost::mpl::_1
                                                                , Locality
                                                                >
                                            , grammar<boost::mpl::_1>
                                                  >
                                        )
                >
  {};

  template<class Locality>
  struct  compute_transform<functors::terminal_,Locality>
        : boost::proto::
          call<compute<functors::terminal_,Locality>( boost::proto::_value
                                                    , boost::proto::_state
                                                    , boost::proto::_data
                                                    )
                      >
  {};
  */
} }

/*
namespace boost { namespace proto
{
  template<class Tag, class Locality>
  struct is_callable<nt2::dsl::compute<Tag,Locality> > : boost::mpl::true_  {};
} }
*/

#endif
