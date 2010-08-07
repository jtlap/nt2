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
  typedef typename std::tr1::result_of<meta::dominant(Args...)>::type::tag      dom;
  typedef typename std::tr1::result_of<call<Function,dom,Info>(Args...)>::type  type;
};

template<class... Args> inline
typename meta::enable_call<Function(Args...)>::type
operator()( Args const& ...args ) const
{
  typedef typename std::tr1::result_of<meta::dominant(Args...)>::type::tag dom;
  call<Function,dom,Info> callee;
  return callee( args... );
}
