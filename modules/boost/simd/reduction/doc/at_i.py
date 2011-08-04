[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T','iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'sT',
            },
         'simd_types' : ['real_'],
         'special' : ['reduction'],  
         'type_defs' : ['typedef typename boost::dispatch::meta::scalar_of<T>::type sT;'],
         'types' : ['integer_'],
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
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()'],['0','0']],
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
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::at_i(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        NT2_TEST_EQUAL( v,a0[a1]);",
                        ]
                    },
             },
        },
    },
]
