//==============================================================================
// Local macro to generate the fall-through dispatch overload
// What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
// it is mandated by the standard so ADL kicks in on resolving calls to
// dispatching without having to order them BEFORE the actual dispatch_call
// class definitions. Without it, the whole system brittles.
//==============================================================================
//==============================================================================
// Actual dispatching mechanism implementation
//==============================================================================
namespace nt2 { namespace meta
{
  struct adl_helper {};
  //============================================================================
  // Default dispatch overload set for catching calls to unsupported functor
  // overload or unregistered types.
  //============================================================================
  template<class Tag, class Site, class A0> nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(A0)> dispatching ( Tag const&, meta::unknown_<Site> const&, meta::unknown_<A0> const& , adl_helper = adl_helper() ); template<class Tag, class Site, class A0 , class A1> nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(A0 , A1)> dispatching ( Tag const&, meta::unknown_<Site> const&, meta::unknown_<A0> const& , meta::unknown_<A1> const& , adl_helper = adl_helper() ); template<class Tag, class Site, class A0 , class A1 , class A2> nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(A0 , A1 , A2)> dispatching ( Tag const&, meta::unknown_<Site> const&, meta::unknown_<A0> const& , meta::unknown_<A1> const& , meta::unknown_<A2> const& , adl_helper = adl_helper() ); template<class Tag, class Site, class A0 , class A1 , class A2 , class A3> nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(A0 , A1 , A2 , A3)> dispatching ( Tag const&, meta::unknown_<Site> const&, meta::unknown_<A0> const& , meta::unknown_<A1> const& , meta::unknown_<A2> const& , meta::unknown_<A3> const& , adl_helper = adl_helper() ); template<class Tag, class Site, class A0 , class A1 , class A2 , class A3 , class A4> nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(A0 , A1 , A2 , A3 , A4)> dispatching ( Tag const&, meta::unknown_<Site> const&, meta::unknown_<A0> const& , meta::unknown_<A1> const& , meta::unknown_<A2> const& , meta::unknown_<A3> const& , meta::unknown_<A4> const& , adl_helper = adl_helper() );
} }
//==============================================================================
// Local macro to generate the dispatch selector
//==============================================================================
/**/
namespace nt2 { namespace meta
{
  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Sig, class Site> struct dispatch_call; 
  template<class Tag, class A0, class Site> struct dispatch_call<Tag(A0), Site> { typedef typename strip<A0>::type arg0; typedef typename hierarchy_of<arg0>::type elem0; NT2_DECLTYPE( dispatching ( Tag(), Site() , elem0() , adl_helper() ) , type ); }; template<class Tag, class A0 , class A1, class Site> struct dispatch_call<Tag(A0 , A1), Site> { typedef typename strip<A0>::type arg0; typedef typename hierarchy_of<arg0>::type elem0; typedef typename strip<A1>::type arg1; typedef typename hierarchy_of<arg1>::type elem1; NT2_DECLTYPE( dispatching ( Tag(), Site() , elem0() , elem1() , adl_helper() ) , type ); }; template<class Tag, class A0 , class A1 , class A2, class Site> struct dispatch_call<Tag(A0 , A1 , A2), Site> { typedef typename strip<A0>::type arg0; typedef typename hierarchy_of<arg0>::type elem0; typedef typename strip<A1>::type arg1; typedef typename hierarchy_of<arg1>::type elem1; typedef typename strip<A2>::type arg2; typedef typename hierarchy_of<arg2>::type elem2; NT2_DECLTYPE( dispatching ( Tag(), Site() , elem0() , elem1() , elem2() , adl_helper() ) , type ); }; template<class Tag, class A0 , class A1 , class A2 , class A3, class Site> struct dispatch_call<Tag(A0 , A1 , A2 , A3), Site> { typedef typename strip<A0>::type arg0; typedef typename hierarchy_of<arg0>::type elem0; typedef typename strip<A1>::type arg1; typedef typename hierarchy_of<arg1>::type elem1; typedef typename strip<A2>::type arg2; typedef typename hierarchy_of<arg2>::type elem2; typedef typename strip<A3>::type arg3; typedef typename hierarchy_of<arg3>::type elem3; NT2_DECLTYPE( dispatching ( Tag(), Site() , elem0() , elem1() , elem2() , elem3() , adl_helper() ) , type ); }; template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class Site> struct dispatch_call<Tag(A0 , A1 , A2 , A3 , A4), Site> { typedef typename strip<A0>::type arg0; typedef typename hierarchy_of<arg0>::type elem0; typedef typename strip<A1>::type arg1; typedef typename hierarchy_of<arg1>::type elem1; typedef typename strip<A2>::type arg2; typedef typename hierarchy_of<arg2>::type elem2; typedef typename strip<A3>::type arg3; typedef typename hierarchy_of<arg3>::type elem3; typedef typename strip<A4>::type arg4; typedef typename hierarchy_of<arg4>::type elem4; NT2_DECLTYPE( dispatching ( Tag(), Site() , elem0() , elem1() , elem2() , elem3() , elem4() , adl_helper() ) , type ); };
} }
