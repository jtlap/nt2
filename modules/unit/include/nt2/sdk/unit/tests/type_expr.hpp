//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED

/*!
  @file
  @brief Type related testing macros
**/

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/expr_type.hpp>

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE__(...) #__VA_ARGS__

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE_(text) NT2_PP_STRINGIZE__ text

/// INTERNAL ONLY
#define NT2_PP_STRINGIZE(...) NT2_PP_STRINGIZE_((__VA_ARGS__))

/*!
  @brief Check for type equality

  For a given @c Expression, consider the test successful if and only if
  @code
  boost::is_same<boost::mpl::apply<Lambda,decltype(Expression)>::type,Type>::value == true
  @endcode

  @usage
  @include test_type_expr.cpp
**/
#define NT2_TEST_EXPR_TYPE(Expression, Lambda, Type)                                              \
{                                                                                                 \
  nt2::unit::test_count()++;                                                                      \
  std::cout << " * Test expression `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Expression))    \
                                      << "`\n"                                                    \
            << "       with lambda `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Lambda))        \
                                      << "`\n"                                                    \
            << "        is of type `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n" \
            << "               aka `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";  \
  if(nt2::details::is_same_as<BOOST_DISPATCH_PP_STRIP(Type)>                                      \
     (nt2::details::expr_type<BOOST_DISPATCH_PP_STRIP(Lambda)>                                    \
                             (BOOST_DISPATCH_PP_STRIP(Expression))                                \
     )                                                                                            \
    )                                                                                             \
  {                                                                                               \
    std::cout << " **passed**\n\n";                                                               \
  }                                                                                               \
  else                                                                                            \
  {                                                                                               \
    nt2::unit::error_count()++;                                                                   \
    std::cout << " **failed**     is `"                                                           \
              << nt2::details::type_id_identity                                                   \
                 (nt2::details::expr_type<BOOST_DISPATCH_PP_STRIP(Lambda)>                        \
                                         (BOOST_DISPATCH_PP_STRIP(Expression))                    \
                 )                                                                                \
              << "`\n\n";                                                                         \
  }                                                                                               \
}                                                                                                 \
/**/

/*!
  @brief Check for typeinfo equality

  For a given @c Type, consider the test successful if and only if
  @c typeid(Type) evaluates to @c Info.

  @usage
  @include test_type_info.cpp
**/
#define NT2_TEST_TYPE_INFO(Info, Type)                                                            \
{                                                                                                 \
  nt2::unit::test_count()++;                                                                      \
  std::cout << " * Test type info `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Info)) << "`\n"  \
            << "       is of type `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n"  \
            << "              aka `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";   \
  if(typeid(BOOST_DISPATCH_PP_STRIP(Type)) == Info)                                               \
  {                                                                                               \
    std::cout << " **passed**\n\n";                                                               \
  }                                                                                               \
  else                                                                                            \
  {                                                                                               \
    nt2::unit::error_count()++;                                                                   \
    std::cout << " **failed**    is `"                                                            \
              << nt2::details::demangle((Info).name())                                            \
              << "`\n\n";                                                                         \
  }                                                                                               \
}                                                                                                 \
/**/

/*!
  @brief Check for typeinfo equality

  For a given type @c T, consider the test successful if and only if
  @c boost::is_same<T,Type>::value evaluates to @c true.

  @usage
  @include test_type_is.cpp
**/
#define NT2_TEST_TYPE_IS(T, Type)                                                             \
{                                                                                             \
  nt2::unit::test_count()++;                                                                  \
  std::cout << " * Test type   `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(T)) << "`\n"    \
            << "          is   `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n" \
            << "         aka   `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";  \
  if(boost::is_same<BOOST_DISPATCH_PP_STRIP(Type), BOOST_DISPATCH_PP_STRIP(T)>::value)        \
  {                                                                                           \
    std::cout << " **passed**\n\n";                                                           \
  }                                                                                           \
  else                                                                                        \
  {                                                                                           \
    nt2::unit::error_count()++;                                                               \
    std::cout << " **failed** is `"                                                           \
              << nt2::type_id<BOOST_DISPATCH_PP_STRIP(T)>()                                   \
              << "`\n\n";                                                                     \
  }                                                                                           \
}                                                                                             \

#endif
