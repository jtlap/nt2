[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Modified Bessel function of the first kind of order 0.'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 16/02/2011',
             'included' : ['extern "C" {double cephes_i0( double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 16/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Minf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Nan<T>()'  : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Inf<T>()'  : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::One<T>()'  : {'result' : 'r_t(1.266065877752008e+00)','ulp_thresh' : '1.0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '1.0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::i0(a0)'],
                },
             'property_value' : {
                 'default' : ['cephes_i0(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['2'],
                },
            },
        },
    },
]
