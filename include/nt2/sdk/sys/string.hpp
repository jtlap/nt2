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

#include <stdio.h>
#include <cstddef>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <algorithm>
#include <nt2/sdk/config/compiler.hpp>

namespace nt2 { namespace sys
{
  //////////////////////////////////////////////////////////////////////////////
  // Lightweight, read-only, string class with formating constructor
  //////////////////////////////////////////////////////////////////////////////
  struct string
  {
    string() : sz(0)
    {
      data = (char*)malloc(sizeof(char));
      *data = '\0';
    }

    string(string const& src) : sz(src.sz)
    {
      if(sz)  data = (char*)malloc(sizeof(char)*(sz+1));
      std::copy(src.data,src.data+sz,data);
    }

    string(std::size_t n) : data(0),sz(n)
    {
      if(sz)  data = (char*)malloc(sizeof(char)*(sz+1));
    }

    ~string() { if(data) free(data); }

    string(char const* format, ...) : data(0)
    {
      va_list ap;
      va_start( ap, format );

      #if defined(NT2_COMPILER_MSVC)
      sz  = _vscprintf( format, ap );
      #else
      sz = vsnprintf( 0, 0, format, ap );
      #endif

      if(sz) data = (char*)malloc(sizeof(char)*(sz+1));

      #if defined(NT2_COMPILER_MSVC)
      _vsnprintf_s( data, sz, _TRUNCATE, format, ap );
      #else
      vsnprintf( data, sz+1, format, ap );
      #endif

      va_end( ap );
    }

    string& operator=( string src ) { swap(src); return *this; }

    string& operator=( char const* src )
    {
      string tmp(src);
      swap(tmp);
      return *this;
    }

    void swap( string& src )
    {
      std::swap(data,src.data);
      std::swap(sz,src.sz);
    }

    char const* c_str() const { return data; }

    std::size_t size() const { return sz; }

    private:
    char*       data;
    std::size_t sz;
  };

  void swap( sys::string& a, sys::string& b ) { a.swap(b); }

  bool operator==( sys::string const& a, sys::string const& b )
  {
    return (strcmp(a.c_str(),b.c_str()) == 0);
  }

  bool operator!=( sys::string const& a, sys::string const& b )
  {
    return !(a==b);
  }

  bool operator==( sys::string const& a, char const* b )
  {
    return (strcmp(a.c_str(),b) == 0);
  }

  bool operator!=( sys::string const& a, char const* b )
  {
    return !(a==b);
  }
} }

#endif
