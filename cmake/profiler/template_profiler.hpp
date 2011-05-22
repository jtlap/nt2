// template_profiler.hpp
//
// Copyright (c) 2008
// Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEMPLATE_PROFILER_HPP_INLUCDED
#define TEMPLATE_PROFILER_HPP_INLUCDED

namespace template_profiler {
    struct incomplete_enter;
    struct incomplete_exit;
    template<int N>
    struct int_ {
        enum { value = N };
        typedef int type;
    };
    template<class T>
    struct make_zero {
        enum { value = 0 };
    };
    extern int enter_value;
    extern int exit_value;
}

char template_profiler_size_one(...);

#if defined(_MSC_VER)
    #define TEMPLATE_PROFILE_ENTER() enum template_profiler_test_enter { template_profiler_value_enter = sizeof(delete ((::template_profiler::incomplete_enter*)0),0) };
    #define TEMPLATE_PROFILE_EXIT() enum template_profiler_test_exit { template_profiler_value_exit = sizeof(delete ((::template_profiler::incomplete_exit*)0),0) };
#elif defined(__GNUC__)
    #if (__GNUC__ < 4) || (__GNUC_MINOR__ < 3)
        #define TEMPLATE_PROFILE_ENTER()\
        struct template_profiler_test_enter {};\
        enum {template_profiler_size_enter = sizeof(template_profiler_size_one(static_cast<template_profiler_test*>(0))) };\
        typedef ::template_profiler::int_<\
            sizeof(\
                ::template_profiler::enter_value /\
                ::template_profiler::make_zero<\
                    ::template_profiler::int_<\
                        template_profiler_size\
                    >\
                >::value\
            )\
        > template_profiler_test_result_enter;
        #define TEMPLATE_PROFILE_EXIT()\
        struct template_profiler_test_exit {};\
        enum {template_profiler_size_exit = sizeof(template_profiler_size_one(static_cast<template_profiler_test*>(0))) };\
        typedef ::template_profiler::int_<\
            sizeof(\
                ::template_profiler::exit_value /\
                ::template_profiler::make_zero<\
                    ::template_profiler::int_<\
                        template_profiler_size\
                    >\
                >::value\
            )\
        > template_profiler_test_result_exit;
    #else
        namespace template_profiler {
            __attribute__((deprecated)) int enter(int);
            int begin(double);
            __attribute__((deprecated)) int exit(int);
            int end(double);
        }
        #define TEMPLATE_PROFILE_ENTER() enum { template_profiler_size_enter = sizeof(::template_profiler::enter(1)) };
        #define TEMPLATE_PROFILE_EXIT() enum { template_profiler_size_exit = sizeof(::template_profiler::exit(1)) };
    #endif
#else
    #error Unknown compiler
#endif

#endif
