/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_RECOGNITION_HPP_INCLUDED
#define NT2_SDK_DSL_RECOGNITION_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/dsl/compile.hpp>
#include <nt2/sdk/functor/forward.hpp>

namespace nt2
{

namespace tag
{
  NT2_HIERARCHY_CLASS(recognition_, formal_);
}
  
namespace meta
{
  template <class Tag>
  struct recognition_
      : boost::proto::
        unpack< boost::proto::
                call< functor<Tag, tag::recognition_> >(compile< recognition_ < boost::mpl::_1 >
                                                               >
                                                       )
              >
  {};

  template <>
  struct recognition_<tag::terminal_>
        : boost::proto::_
  {};
} }

namespace boost { namespace proto
{
  template<class Tag>
  struct  is_callable<nt2::meta::recognition_<Tag> >
        : boost::mpl::true_  {};
} }

#endif
