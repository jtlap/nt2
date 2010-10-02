//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_DSL_LOW_LEVEL_HPP_INCLUDED
#define NT2_SDK_DSL_LOW_LEVEL_HPP_INCLUDED

#include <boost/proto/proto.hpp>

namespace nt2 { namespace meta
{
  ////////////////////////////////////////////////////////////////////////////
  /// Proto grammar gathering 'low level' C++ operators
  ////////////////////////////////////////////////////////////////////////////
  template<class Grammar>
  struct low_level
       : boost::proto::or_< boost::proto::address_of<Grammar>
                          , boost::proto::dereference<Grammar>
                          > {};
} }

#endif
