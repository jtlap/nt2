[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['shuffles the elements of a1 using indices in a2'],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'special' : ['swar'],
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()'],['0','boost::dispatch::meta::cardinal_of<T>::value-1']],
             'real_' : [['T(-100)', 'T(100)'],['0','boost::dispatch::meta::cardinal_of<T>::value-1']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Minf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::Zero<ivT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::lookup(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        for(uint32_t i=0; i<cardinal_of<n_t>::value; i++)",
                        "        {",
                        "           NT2_TEST_EQUAL(v[i],a0[a1[i]]);",
                        "        }",
                            ]
               },
           },
        },
    },
]
