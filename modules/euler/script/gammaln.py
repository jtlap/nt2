[ ## this file was manually modified by jt
    {
     'functor' : {
           'description' :['Natural logarithm of the absolute value of the Gamma function'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 22/02/2011',
             'included' : ['extern "C" {long double cephes_gammal(long double);}',
                           'extern "C" {long double cephes_logl  (long double);}' ],
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
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::gammaln(a0)'],
                },
             'property_value' : {
                 'default' : ['cephes_logl(std::abs(cephes_gammal(a0)))'],
                },
             'ulp_thresh' : {
                 'default' : ['1.5'],
                },
            },
        },
    },
]
