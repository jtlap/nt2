    template<class This,class A0 , class A1> struct result<This(A0 , A1)> { NT2_DECLTYPE( 0 ? boost::declval<A0>() : boost::declval<A1>() , type ); }; template<class This,class A0 , class A1 , class A2> struct result<This(A0 , A1 , A2)> { NT2_DECLTYPE( 0 ? 0 ? boost::declval<A0>() : boost::declval<A1>() : boost::declval<A2>() , type ); }; template<class This,class A0 , class A1 , class A2 , class A3> struct result<This(A0 , A1 , A2 , A3)> { NT2_DECLTYPE( 0 ? 0 ? 0 ? boost::declval<A0>() : boost::declval<A1>() : boost::declval<A2>() : boost::declval<A3>() , type ); };
    
    
