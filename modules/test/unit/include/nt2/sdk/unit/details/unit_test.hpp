//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_UNIT_TEST_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_UNIT_TEST_HPP_INCLUDED

namespace nt2 { namespace details
{
  struct test_suite;

  /// INTERNAL ONLY - RAII class for registering a test into a test suite
  struct unit_test
  {
    typedef void (*ptr_fun_t)();

    unit_test (test_suite const* s = 0, ptr_fun_t c = 0, const char* n = 0);

    virtual ~unit_test();

    virtual   void    process() const;
    unit_test const*  link(unit_test const* n)  const;
    void              advance() const;

            ptr_fun_t         call;
            const char*       name;
    mutable unit_test const*  next;
  };
} }

#endif
