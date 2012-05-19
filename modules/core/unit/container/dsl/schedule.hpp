/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_UNIT_DSL_GENERATOR_SCHEDULE_INCLUDED
#define NT2_UNIT_DSL_GENERATOR_SCHEDULE_INCLUDED

struct scheduler
{
  template<class Sig>
  struct result;

  template<class This, class T>
  struct result<This(T)>
  {
    typedef typename boost::dispatch::meta::strip<T>::type stripped;
    typedef typename boost::dispatch::meta::semantic_of<stripped const&>::type semantic;

    typedef typename boost::mpl::eval_if< boost::is_same<typename boost::proto::tag_of<stripped>::type, boost::proto::tag::assign>
                                        , boost::proto::result_of::child_c<stripped const&, 0>
                                        , boost::dispatch::meta::terminal_of<semantic>
                                        >::type type;
  };

  template<class T>
  typename boost::disable_if< boost::is_same<typename boost::proto::tag_of<T>::type, boost::proto::tag::assign>
                            , typename result<scheduler(T const&)>::type
                            >::type
  operator()(T const&) const
  {
    trees.push_back(&typeid(typename as_node<T>::type));

    static typename boost::remove_reference<typename result<scheduler(T const&)>::type>::type r;
    return r;
  }

  template<class T>
  typename boost::enable_if< boost::is_same<typename boost::proto::tag_of<T>::type, boost::proto::tag::assign>
                           , typename result<scheduler(T const&)>::type
                           >::type
  operator()(T const& t) const
  {
    trees.push_back(&typeid(typename as_node<T>::type));

    return boost::proto::child_c<0>(t);
  }

  mutable std::vector<std::type_info const*> trees;
};

#define SCHEDULE(Expr, f, N, Ret)                                              \
f.trees.clear();                                                               \
std::cout << "\nScheduling `" << NT2_PP_STRINGIZE(Expr) << "`\n";              \
NT2_TEST_EXPR_TYPE( nt2::schedule(Expr, f), as_node<boost::mpl::_>, Ret );     \
NT2_TEST_EQUAL( f.trees.size(), N )                                            \
/**/

#endif
