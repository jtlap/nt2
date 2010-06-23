/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nt2/sdk/sys/string.hpp>
#include <nt2/sdk/config/compiler.hpp>

namespace nt2 { namespace sys
{
  //////////////////////////////////////////////////////////////////////////////
  // Lightweight string object
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Constructors
  //////////////////////////////////////////////////////////////////////////////
  string::string() : sz(0)
  {
    data = (char*)malloc(sizeof(char));
    *data = '\0';
  }

  string::string(string const& src) : sz(src.sz)
  {
    if(sz)  data = (char*)malloc(sizeof(char)*(sz+1));
    memcpy(data,src.data,sz+1);
  }

  string::string(std::size_t n) : data(0),sz(n)
  {
    if(sz)  data = (char*)malloc(sizeof(char)*(sz+1));
  }

  string::string(char const* format, ...) : data(0)
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

  //////////////////////////////////////////////////////////////////////////////
  // Destructor
  //////////////////////////////////////////////////////////////////////////////
  string::~string() { if(data) free(data); }

  //////////////////////////////////////////////////////////////////////////////
  // Assignement operators
  //////////////////////////////////////////////////////////////////////////////
  string& string::operator=( string src )
  {
    swap(src);
    return *this;
  }

  string& string::operator=( char const* src )
  {
    string tmp(src);
    swap(tmp);
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Swap method
  //////////////////////////////////////////////////////////////////////////////
  void string::swap( string& src )
  {
    std::swap(data,src.data);
    std::swap(sz,src.sz);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Swap function
  //////////////////////////////////////////////////////////////////////////////
  void swap( sys::string& a, sys::string& b ) { a.swap(b); }

  //////////////////////////////////////////////////////////////////////////////
  // Comparison operators
  //////////////////////////////////////////////////////////////////////////////
  bool operator==( sys::string const& a, char const* b )
  {
    return (strcmp(a.c_str(),b) == 0);
  }

  bool operator!=( sys::string const& a, char const* b )
  {
    return !(a==b);
  }

  bool operator==( sys::string const& a, sys::string const& b )
  {
    return a == b.c_str();
  }

  bool operator!=( sys::string const& a, sys::string const& b )
  {
    return !(a==b);
  }

  bool operator==( char const* a, sys::string const& b )
  {
    return b==a;
  }

  bool operator!=( char const* a, sys::string const& b )
  {
    return b!=a;
  }
} }
