//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_COUNTER_HPP_INCLUDED
#define BOOST_DISPATCH_META_COUNTER_HPP_INCLUDED

#include <boost/dispatch/details/typeof.hpp>
#include <boost/preprocessor/cat.hpp>

#ifndef BOOST_DISPATCH_COUNTER_MAX
#define BOOST_DISPATCH_COUNTER_MAX 32
#endif

namespace boost { namespace dispatch { namespace details
{
  template<int N>
  struct depth_;

  template<>
  struct depth_<0>
  {
  };

  template<int N>
  struct depth_ : depth_<N-1>
  {
  };
  
  template<class T, class U = T>
  struct identity
  {
    typedef T type;
  };
}

namespace meta
{
  struct adl_helper {};
}
} }

#define BOOST_DISPATCH_COUNTER_INIT(name)                                                          \
namespace boost { namespace dispatch { namespace meta                                              \
{                                                                                                  \
  boost::mpl::int_<0> name( details::depth_<0>, adl_helper const& );                               \
} } }                                                                                              \
/**/

#define BOOST_DISPATCH_COUNTER_VALUE(name)                                                         \
boost::dispatch::details::                                                                         \
identity< BOOST_DISPATCH_TYPEOF(name                                                               \
                                ( boost::dispatch::details::depth_<BOOST_DISPATCH_COUNTER_MAX>()   \
                                , boost::dispatch::meta::adl_helper()                              \
                                )                                                                  \
                               )                                                                   \
        >::type::value                                                                             \
/**/

#define BOOST_DISPATCH_COUNTER_VALUE_TPL(name, dummy)                                              \
boost::dispatch::details::                                                                         \
identity< BOOST_DISPATCH_TYPEOF(name                                                               \
                                ( (typename boost::dispatch::details::                             \
                                   identity< boost::dispatch::details::                            \
                                             depth_<BOOST_DISPATCH_COUNTER_MAX>                    \
                                           , dummy                                                 \
                                           >::type()                                               \
                                  )                                                                \
                                , boost::dispatch::meta::adl_helper()                              \
                                )                                                                  \
                               )                                                                   \
        >::type::value                                                                             \
/**/
 
#define BOOST_DISPATCH_COUNTER_INCREMENT(name)                                                     \
namespace boost { namespace dispatch { namespace meta                                              \
{                                                                                                  \
  boost::mpl::int_< BOOST_DISPATCH_COUNTER_VALUE(name) + 1 >                                       \
  name( details::depth_< BOOST_DISPATCH_COUNTER_VALUE(name) + 1 >                                  \
                              , adl_helper const&                                                  \
                              );                                                                   \
} } }                                                                                              \
/**/

#endif
