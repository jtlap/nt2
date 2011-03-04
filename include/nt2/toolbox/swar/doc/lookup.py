[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T','iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],
             'no_ulp' : True,   
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [],
             'unsigned_int_' : [],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>(),0' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),0' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>(),0' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>(),0' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>(),0' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::Nan<T>(),0' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),0' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),0' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>(),0' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),0' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),0' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::lookup(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]
