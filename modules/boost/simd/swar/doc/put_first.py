[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['returns a vector equal to a0 except that',
                          'the first element of a0 is replaced  by its element of index a2 (scalar integer).',
                          'the other elements are not modified.'],              
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_','signed_int_','unsigned_int_'],
         'scalar_ints': 'True',   
         'special' : ['swar'],  
         'type_defs' : [],
         'types' : ['real_'],
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
                 'boost::simd::One<T>(),0' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),0' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>(),0' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>(),0' : {'result' : 'boost::simd::Minf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>(),0' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>(),0' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),0' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),0' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>(),0' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),0' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),0' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::put_first(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        NT2_TEST_EQUAL(v[0],a0[a1]);",
                            ]
               },
            },
        },
    },
]
