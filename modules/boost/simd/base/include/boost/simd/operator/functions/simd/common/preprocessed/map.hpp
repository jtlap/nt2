namespace boost { namespace simd { namespace ext
{
  template<class A0 = int , class A1 = int , class A2 = int , class A3 = int , class A4 = int , class A5 = int>
  struct map_cardinal_size
  {
    static const std::size_t value = meta::cardinal_of<A0>::value != 1u ? meta::cardinal_of<A0>::value : meta::cardinal_of<A1>::value != 1u ? meta::cardinal_of<A1>::value : meta::cardinal_of<A2>::value != 1u ? meta::cardinal_of<A2>::value : meta::cardinal_of<A3>::value != 1u ? meta::cardinal_of<A3>::value : meta::cardinal_of<A4>::value != 1u ? meta::cardinal_of<A4>::value : meta::cardinal_of<A5>::value != 1u ? meta::cardinal_of<A5>::value : 1u;
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0>::value; ++i)
        insert(f(extract(a0, i)), that, i);
      return that;
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0 , A1>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0 , A1 const & a1) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0 , A1>::value; ++i)
        insert(f(extract(a0, i) , extract(a1, i)), that, i);
      return that;
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0 , A1 , A2>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0 , A1 , A2>::value; ++i)
        insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i)), that, i);
      return that;
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0 , A1 , A2 , A3>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0 , A1 , A2 , A3>::value; ++i)
        insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i)), that, i);
      return that;
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , generic_< unspecified_<A4> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0 , A1 , A2 , A3 , A4>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0 , A1 , A2 , A3 , A4>::value; ++i)
        insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i) , extract(a4, i)), that, i);
      return that;
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , generic_< unspecified_<A4> > const , generic_< unspecified_<A5> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type , typename meta::scalar_of<A5>::type )
             >::type
    rtype;
    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<A0 , A1 , A2 , A3 , A4 , A5>::value
                     >::type result_type;
    result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5) const
    {
      result_type that;
      for(size_t i = 0; i != map_cardinal_size<A0 , A1 , A2 , A3 , A4 , A5>::value; ++i)
        insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i) , extract(a4, i) , extract(a5, i)), that, i);
      return that;
    }
  };
} } }
