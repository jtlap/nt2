/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// This file is supposed to be included inside functors::functor code
////////////////////////////////////////////////////////////////////////////////
template<class This, class... Args>
struct  result<This(Args...)>
{
  typedef typename meta::dominant<Args...>::type::tag               dom;
  typedef meta::dispatch<Function,dom,Info>                         dispatching;
  typedef typename std::tr1::result_of<dispatching(Args...)>::type  callee;
  typedef typename std::tr1::result_of<callee(Args...)>::type       type;
};

template<class... Args> inline
typename meta::enable_call<Function(Args...)>::type
operator()( Args const& ...args ) const
{
  typedef   typename meta::dominant<Args...>::type::tag      dom;
  typedef   meta::dispatch<Function,dom,Info>                dispatching;
  typename  std::tr1::result_of<dispatching(Args...)>::type  callee;

  return callee( args... );
}
