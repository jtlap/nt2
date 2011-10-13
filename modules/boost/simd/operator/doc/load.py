[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Load a data of type T from the memory zone given by (a0,a1)',
                          'with or without a sub-type level offset'],
         'template' : True,
         'param_3'  : ['this offset is optionnal'],
         'equalparams' : False,
         'special_synopsis' : [
                "template<class T,class A0,class A1> inline",
                "typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&",
                "                                              , boost::dispatch::meta::as_<T>",
                "                                               )",
                "                                    >::type",
                "load(A0 const& a0,A1 const& a1 );",
                ""
                "template<class T,int Offset,class A0,class A1> inline",
                "typename boost::dispatch::meta::call<tag::load_ ( A0 const&, A1 const&",
                "                                              , boost::dispatch::meta::as_<T>",
                "                                              , boost::mpl::int_<Offset>",
                "                                              )",
                "                                     >::type",
                "load(A0 const& a0,A1 const& a1 );",
                ],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['integer_','real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::Minf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::bitwise_and(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0&a1'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
