#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/include/functions/run.hpp>
#include <iostream>
#include <boost/proto/debug.hpp>
#include <boost/dispatch/dsl/category.hpp>

#include <nt2/toolbox/operator/functions.hpp>

template<class T>
struct block
{
  boost::array<T, 4096> data;
};

namespace nt2 { namespace container
{
    
template<class Block>
struct table_container
{
    Block block;
};

template<class T>
struct is_container< table_container<T> >
  : boost::mpl::true_
{
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< nt2::container::table_container<T> >
  {
    typedef T type;
  };
    
  template<class T>
  struct value_of< ::block<T> >
  {
    typedef T type;
  };
    
  template<class T, class Origin>
  struct hierarchy_of< nt2::container::table_container<T>, Origin >
  {
    typedef container_< typename property_of<typename value_of<T>::type, Origin>::type > type;
  };
    
} } }

namespace nt2 { namespace container
{

template<class T, class S>
struct make_block
{
  typedef ::block<T> type;
};

template<class T, class S>
struct table 
: expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            >
{
  typedef
  expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            > parent;
  
  table() {}

  template<class Xpr,class Result> 
  BOOST_DISPATCH_FORCE_INLINE 
  table(expression<Xpr,Result> const& xpr) { static_cast<parent&>(*this) = xpr; }
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct semantic_of<nt2::container::table<T, S> >
    : semantic_of<typename nt2::container::table<T, S>::parent>
  {
  };
} } }

namespace nt2 { namespace ext
{
  // Functions for logical type deduction
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)
                            , (unspecified_<F>)
                              ((container_< unspecified_<A0> >))
                            )
  {
    typedef A0& result_type;
    result_type inline operator()(F const&, A0 const& a0) const
    {
      return const_cast<A0&>(a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)(A1)
                            , (unspecified_<F>)
                              (container_< unspecified_<A0> >)
                              (container_< unspecified_<A1> >)
                            )
  {
    typedef A0& result_type;
    result_type inline operator()(F const&, A0 const& a0, A1 const& a1) const
    {
      return const_cast<A0&>(a0);
    }
  };
} }

#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/array.hpp>
#include <cstdio>

namespace nt2
{
    template<std::size_t N>
    struct for_each_impl
    {
        template<class Bases, class Sizes, class Position, class F>
        BOOST_DISPATCH_FORCE_INLINE
        static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
        {
            for(pos[N-1] = bases[N-1]; pos[N-1] != bases[N-1] + sz[N-1]; ++pos[N-1])
                for_each_impl<N-1>::call(bases, sz, pos, f);
        }
    };
    
    template<>
    struct for_each_impl<0>
    {
        template<class Bases, class Sizes, class Position, class F>
        static void call(Bases const&, Sizes const&, Position& pos, F const& f)
        {
            return f(pos);
        }
    };
    
    template<class Bases, class Sizes, class F>
    BOOST_DISPATCH_FORCE_INLINE
    void for_each(Bases const& bases, Sizes const& sz, F const& f)
    {
        static const std::size_t nb_dims = boost::fusion::result_of::size<Sizes>::value;
        
        boost::array<std::size_t, nb_dims> position;
        for_each_impl<nb_dims>::call(bases, sz, position, f);
    }
    
    template<class T>
    boost::array<std::size_t, 1> sizes(T const&) { boost::array<std::size_t, 1> sz = { 4 }; return sz; }
    
    template<class T>
    boost::array<std::size_t, 1> base_indices(T const&) { boost::array<std::size_t, 1> sz = { 1 }; return sz; }
}

template<class A0>
struct call_compute
{
    call_compute(A0 a0_) : a0(a0_) {}
    
    typedef void result_type;
    
    template<class Position>
    result_type operator()(Position const& pos) const
    {
        nt2::run(a0, pos);
    }

    A0 a0;
};

namespace nt2 { namespace ext
{
  // terminal, does the load
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)(std::size_t N)
                            , (ast_<container_< unspecified_<A0> > >)
                              ((array_< scalar_< integer_<State> >, N>))
                            )
  {
    typedef typename boost::dispatch::meta::primitive_of<typename boost::dispatch::meta::semantic_of<A0>::type>::type scalar_type;
    typedef scalar_type& result_type;
    
    template<class A0_>
    result_type operator()(A0_& a0, State const& state) const
    {
       std::cout << "access to table " << (void*)&boost::proto::value(a0) << " in " << state[0] << std::endl;
       static scalar_type r;
       return r;
    }
  };
    
  // An expression is ran by running it for every position
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , (ast_<container_< unspecified_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      for_each(base_indices(a0), sizes(a0), call_compute<A0 const&>(a0));
      static typename boost::remove_reference<result_type>::type r;
      return r;
    }
  };
} }

int main()
{
  using nt2::container::table;
    
  table<double> a, b, c;
  a = b;
#if 0
  a = b + c*c/a;
  b += c;
#endif
  //c += !a; // problem with bool
  /*c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);*/
}
