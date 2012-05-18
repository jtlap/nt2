//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_CONSTRUCT_HPP_INCLUDED

#include <nt2/core/functions/construct.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/category.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <nt2/sdk/memory/copy.hpp>

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::iterator_;

  //============================================================================
  // Construct a terminal from a size
  //  * Perform a resize on the table's container
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename A0::extent_type    extent_type;
    typedef typename A0::container_type container_type;
    typedef void                        result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      boost::proto::value(a0).resize(a1);
    }
  };

  //============================================================================
  // Construct a terminal from a size and some unspecified allocator
  //  * Construct a proper container from size and allocator
  //  * Swap with the table's container
  // This is done even if swap sounds bad with automatic storage table. Good
  // news are that automatic_ storage table usually don't require allocators ;)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (fusion_sequence_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename A0::extent_type    extent_type;
    typedef typename A0::allocator_type allocator_type;
    typedef typename A0::container_type container_type;
    typedef void                        result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, A1 const& a1, A2 const& a2) const
    {
      container_type that((extent_type(a1)),(allocator_type(a2)));
      boost::proto::value(a0).swap(that);
    }
  };

  //============================================================================
  // Construct a terminal from another expression
  // Non trivial assignment is passed to the parent expression type that will
  // select hwo to perform the expression evaluation.
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (ast_<A1>)
                            )
  {
    typedef void result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      typedef typename A0::parent parent;
      static_cast<parent&>(a0) = a1;
    }
  };
  //============================================================================
  // Construct a terminal from a scalar:
  //  * Resize table to [1 1]
  //  * Copy the scalar to the table memory (*raw() is the easiest way)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef void result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      boost::proto::value(a0).resize(of_size_<1,1>());
      *(a0.raw()) = a1;
    }
  };

  //============================================================================
  // Construct a terminal from a size and a Iterator pair
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              (fusion_sequence_<A1>)
                              (iterator_< scalar_< arithmetic_<A2> > >)
                              (iterator_< scalar_< arithmetic_<A3> > >)
                            )
  {
    typedef void result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0& a0, A1 const& a1, A2 const& a2, A3 const& a3) const
    {
      typedef typename boost::proto::result_of::value<A0>::type type;
      std::size_t range_size = std::distance(a2,a3);

      BOOST_ASSERT_MSG
      ( nt2::numel(a1) >= range_size
      , "Source range is larger than destination container."
      );

      boost::proto::value(a0).resize(a1);
      nt2::memory::copy( a0.raw(), a0.raw()+range_size, a2 );
    }
  };
} }

#endif
