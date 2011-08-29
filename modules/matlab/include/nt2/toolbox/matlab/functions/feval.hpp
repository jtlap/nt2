//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_MATLAB_FUNCTIONS_FEVAL_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_FUNCTIONS_FEVAL_HPP_INCLUDED

#include <nt2/toolbox/matlab/details/array.hpp>
#include <nt2/toolbox/matlab/details/mcr.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace nt2
{
    namespace matlab
    {
        // not exception-safe, hard to fix in C++03
    
        #define M1(z, n, text) traits::to_matlab(a##n)
        
        #define M0(z, n, text)                                                 \
        template<typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>\
        R feval(const char* s BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_BINARY_PARAMS(n, const T, & a))\
        {                                                                      \
            details::mcr::instance();                                          \
                                                                               \
            mxArray* in[] = { mxCreateString(s) BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM(n, M1, ~) };\
            mxArray* out[1];                                                   \
                                                                               \
            mlxFeval(sizeof out / sizeof *out, out, sizeof in / sizeof *in, in);\
                                                                               \
            for(int i=0; i<sizeof in / sizeof *in; ++i)                        \
                mxDestroyArray(in[i]);                                         \
                                                                               \
            R r = traits::from_matlab<R>(out[0]);                              \
                                                                               \
            for(int i=0; i<sizeof out / sizeof *out; ++i)                      \
                mxDestroyArray(out[i]);                                        \
                                                                               \
            return r;                                                          \
        }
        
        BOOST_PP_REPEAT(BOOST_DISPATCH_MAX_ARITY, M0, ~)
        #undef M0
        #undef M1
    }
}

#endif
