//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_UNIT_SDK_MEMORY_OBJECT_HPP_INCLUDED
#define NT2_UNIT_SDK_MEMORY_OBJECT_HPP_INCLUDED

#include <string>


namespace nt2
{
  struct object
  {
    object(const char* s_) : s(s_) {}
    object()              : s("default")  {}
    object(object const&) : s("copied")   {}

    object& operator=(object const&)
    {
      s = "assigned";
      return *this;
    }

    object& operator=(std::string const& src)
    {
      s = src;
      return *this;
    }

    ~object() {}

    std::string s;
  };

  inline void swap(object& l, object& r)
  {
    l.s = "left swapped";
    r.s = "right swapped";
  }
}

#endif
