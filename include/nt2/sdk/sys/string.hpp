/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SYS_STRING_HPP_INCLUDED
#define NT2_SDK_SYS_STRING_HPP_INCLUDED

#include <cstddef>
#include <stdarg.h>
#include <nt2/sdk/config/compiler.hpp>

namespace nt2 { namespace sys
{
  //////////////////////////////////////////////////////////////////////////////
  // Lightweight, read-only, string class with formating constructor
  //////////////////////////////////////////////////////////////////////////////
  struct string
  {
              string();
              string(string const& src);
    explicit  string(std::size_t n);
    explicit  string(char const* format, ...);

    ~string();

    string& operator=( string src );
    string& operator=( char const* src );

    void swap( string& src );
    char const* c_str() const { return data; }
    std::size_t size() const { return sz; }

    private:
    char*       data;
    std::size_t sz;
  };

  void swap( sys::string& a, sys::string& b );

  bool operator==( sys::string const& a, sys::string const& b );
  bool operator!=( sys::string const& a, sys::string const& b );
  bool operator==( sys::string const& a, char const* b );
  bool operator!=( sys::string const& a, char const* b );
  bool operator==( char const* a, sys::string const& b );
  bool operator!=( char const* a, sys::string const& b );
} }

#endif
