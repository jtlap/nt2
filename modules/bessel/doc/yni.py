[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['iT', 'T'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type'
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
         'simd_ulp_thresh'   : '4096.0',
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 16/02/2011',
             'included' : ['extern "C" {long double cephes_ynl(int,long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 16/02/2011',
            },
         'ranges' : {
             'real_' : [['1', '10'],['T(0)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 '1,nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 '1,nt2::Zero<T>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0.5',},
                 '0,nt2::Zero<T>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0.5',},
                 '0,nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::yni(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['::cephes_ynl(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['200'],
                },
            },
        },
    },
]
