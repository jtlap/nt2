////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename meta::extension_of<A0>::type X;
    static const std::size_t N = meta::cardinal_of<A0>::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0) const
    {
      return impl::call(a0);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> , unspecified_<A1> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename ext_common< typename meta::extension_of<A0>::type , typename meta::extension_of<A1>::type >::type X;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , meta::cardinal_of<A1>::value >::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const & , A1 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 , a1 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1) const
    {
      return impl::call(a0 , a1);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename meta::extension_of<A2>::type >::type >::type X;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , meta::cardinal_of<A2>::value >::value >::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const & , A1 const & , A2 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 , a1 , a2 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2) const
    {
      return impl::call(a0 , a1 , a2);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename meta::extension_of<A3>::type >::type >::type >::type X;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , meta::cardinal_of<A3>::value >::value >::value >::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const & , A1 const & , A2 const & , A3 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3) const
    {
      return impl::call(a0 , a1 , a2 , a3);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 , A4 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3 , class A4,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename ext_common< typename meta::extension_of<A3>::type , typename meta::extension_of<A4>::type >::type >::type >::type >::type X;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , meta::cardinal_of<A4>::value >::value >::value >::value >::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u) || (meta::cardinal_of<A4>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3) , splat<typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type>(a4));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const & , A1 const & , A2 const & , A3 const & , A4 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 , a4 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4) const
    {
      return impl::call(a0 , a1 , a2 , a3 , a4);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 , A4 , A5 > > , :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> , unspecified_<A5> ) , tag::formal_ > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , unspecified_<A5> const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< elementwise_<Tag> ( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> , unspecified_<A5> ) , tag::formal_ >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5,class Tag, class Dummy>
  struct implement< elementwise_<Tag>( unspecified_<A0> , unspecified_<A1> , unspecified_<A2> , unspecified_<A3> , unspecified_<A4> , unspecified_<A5> )
                  , tag::formal_, Dummy
                  >
  {
    typedef typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename ext_common< typename meta::extension_of<A3>::type , typename ext_common< typename meta::extension_of<A4>::type , typename meta::extension_of<A5>::type >::type >::type >::type >::type >::type X;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , cardinal_common< meta::cardinal_of<A4>::value , meta::cardinal_of<A5>::value >::value >::value >::value >::value >::value;
    static const bool is_splat_case = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u) || (meta::cardinal_of<A4>::value == 1u) || (meta::cardinal_of<A5>::value == 1u));
    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type)>::type Callee;
      typedef typename boost::dispatch::meta::
      result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type , typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type)>::type type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3) , splat<typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type>(a4) , splat<typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type>(a5));
      }
    };
    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)
      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const &
                        )
             >::type
      type;
      BOOST_FORCEINLINE static type
      call(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 , a4 , a5 );
      }
    };
    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5) const
    {
      return impl::call(a0 , a1 , a2 , a3 , a4 , a5);
    }
  };
} } }
