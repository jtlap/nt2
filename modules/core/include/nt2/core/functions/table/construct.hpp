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
#include <nt2/core/container/table/category.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/fusion/include/fold.hpp>

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::iterator_;

  //============================================================================
  // Construct a terminal from a size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::tag::terminal_
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
      container_type that((extent_type(a1)));
      boost::proto::value(a0).swap(that);
    }
  };

  //============================================================================
  // Construct a terminal from a size and some unspecified allocator
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::tag::terminal_
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
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(Tag)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < unspecified_<A1>
                                      , Tag
                                      , boost::mpl::long_<0>
                                      >
                              ))
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
  // Construct a terminal from a scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::tag::terminal_
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
      typedef typename A0::parent parent;
      static_cast<parent&>(a0) = a1;
    }
  };

  //============================================================================
  // Construct a terminal from a size and a Iterator pair
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::tag::terminal_
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
      //========================================================================
      // Check we don't copy more than expected
      //========================================================================
      BOOST_ASSERT_MSG
      ( boost::fusion::fold ( a1
                            , boost::mpl::size_t<1>()
                            , functor<tag::multiplies_>()
                            )
        >= static_cast<size_t>(std::distance(a2,a3))
      , "Source range is larger than destination container."
      );

      //========================================================================
      // Resize to target extent
      //========================================================================
      boost::proto::value(a0).resize(a1);

      //========================================================================
      // copy elementwisely
      //========================================================================
      boost::array<std::size_t,1> pos;
      pos[0] = boost::mpl::at_c<typename A0::index_type::type,0>::type::value;

      for(A2 beg_ = a2; beg_ != a3; ++pos[0], ++beg_)
        boost::proto::value(a0)[ pos ] = *beg_;
    }
  };
} }

#endif
