/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_RECOGNITION_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_RECOGNITION_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <boost/dispatch/dsl/compile.hpp>
#include <boost/dispatch/functor/forward.hpp>

namespace boost { namespace simd
{

namespace tag
{
  BOOST_DISPATCH_HIERARCHY_CLASS(recognition_, boost::dispatch::tag::formal_);
}
  
namespace meta
{
  template <class Tag>
  struct recognition_
      : boost::proto::
        unpack< boost::proto::
                call< boost::dispatch::functor<Tag, tag::recognition_> >(dispatch::meta::compile< recognition_ < boost::mpl::_1 >
                                                               >
                                                       )
              >
  {};

  template <>
  struct recognition_<boost::dispatch::tag::terminal_>
        : boost::proto::_
  {};
} } }

namespace boost { namespace proto
{
  template<class Tag>
  struct  is_callable<boost::simd::meta::recognition_<Tag> >
        : boost::mpl::true_  {};
} }

#endif
