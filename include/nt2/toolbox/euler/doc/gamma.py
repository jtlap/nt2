[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
         'simd_ulp_thresh' : '25.0'   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 22/02/2011',
             'included' : ['extern "C" {long double cephes_gammal(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 22/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::gamma(a0)'],
                },
             'property_value' : {
                 'default' : ['cephes_gammal(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['25.0'],
                },
            },
        },
    },
]
