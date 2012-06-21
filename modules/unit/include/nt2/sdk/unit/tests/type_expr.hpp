//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_TYPE_EXPR_HPP_INCLUDED

#include <nt2/sdk/meta/type_id.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details
{
  template<class Lambda, class T>
  boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>
  expr_type(T const&)
  {
    return boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>();
  }

  template<class T, class U>
  typename boost::is_same<T, typename U::type>::type
  is_same_as(U const&)
  {
    return typename boost::is_same<T, typename U::type>::type();
  }

  template<class T>
  std::string type_id_identity(T const&)
  {
    return nt2::type_id<typename T::type>();
  }
} }

#define NT2_PP_STRINGIZE__(...) #__VA_ARGS__
#define NT2_PP_STRINGIZE_(text) NT2_PP_STRINGIZE__ text
#define NT2_PP_STRINGIZE(...) NT2_PP_STRINGIZE_((__VA_ARGS__))

#define NT2_TEST_EXPR_TYPE(Expression, Lambda, Type)                                               \
{                                                                                                  \
  nt2::details::test_count()++;                                                                    \
  std::cout << " * Test expression `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Expression))     \
                                      << "`\n"                                                     \
            << "       with lambda `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Lambda))         \
                                      << "`\n"                                                     \
            << "        is of type `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n"  \
            << "               aka `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";   \
  if(nt2::details::is_same_as<BOOST_DISPATCH_PP_STRIP(Type)>                                       \
     (nt2::details::expr_type<BOOST_DISPATCH_PP_STRIP(Lambda)>                                     \
                             (BOOST_DISPATCH_PP_STRIP(Expression))                                 \
     )                                                                                             \
    )                                                                                              \
  {                                                                                                \
    std::cout << " **passed**\n\n";                                                                \
  }                                                                                                \
  else                                                                                             \
  {                                                                                                \
    nt2::details::error_count()++;                                                                 \
    std::cout << " **failed**     is `"                                                            \
              << nt2::details::type_id_identity                                                    \
                 (nt2::details::expr_type<BOOST_DISPATCH_PP_STRIP(Lambda)>                         \
                                         (BOOST_DISPATCH_PP_STRIP(Expression))                     \
                 )                                                                                 \
              << "`\n\n";                                                                          \
  }                                                                                                \
}                                                                                                  \
/**/

#define NT2_TEST_TYPE_INFO(Info, Type)                                                             \
{                                                                                                  \
  nt2::details::test_count()++;                                                                    \
  std::cout << " * Test type info `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Info)) << "`\n"   \
            << "       is of type `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n"   \
            << "              aka `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";    \
  if(typeid(BOOST_DISPATCH_PP_STRIP(Type)) == Info)                                                \
  {                                                                                                \
    std::cout << " **passed**\n\n";                                                                \
  }                                                                                                \
  else                                                                                             \
  {                                                                                                \
    nt2::details::error_count()++;                                                                 \
    std::cout << " **failed**    is `"                                                             \
              << nt2::details::demangle((Info).name())                                             \
              << "`\n\n";                                                                          \
  }                                                                                                \
}                                                                                                  \
/**/

#define NT2_TEST_TYPE_IS(T, Type)                                                                  \
{                                                                                                  \
  nt2::details::test_count()++;                                                                    \
  std::cout << " * Test type   `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(T)) << "`\n"         \
            << "          is   `" << NT2_PP_STRINGIZE(BOOST_DISPATCH_PP_STRIP(Type)) << "`\n"      \
            << "         aka   `" << nt2::type_id<BOOST_DISPATCH_PP_STRIP(Type)>() << "`\n";       \
  if(boost::is_same<BOOST_DISPATCH_PP_STRIP(Type), BOOST_DISPATCH_PP_STRIP(T)>::value)             \
  {                                                                                                \
    std::cout << " **passed**\n\n";                                                                \
  }                                                                                                \
  else                                                                                             \
  {                                                                                                \
    nt2::details::error_count()++;                                                                 \
    std::cout << " **failed** is `"                                                                \
              << nt2::type_id<BOOST_DISPATCH_PP_STRIP(T)>()                                        \
              << "`\n\n";                                                                          \
  }                                                                                                \
}                                                                                                  \
/**/

#endif
