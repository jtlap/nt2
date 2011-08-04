[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'special' : ['ieee'],
         'tpl'   : '<boost::simd::tag::Pi>',   
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/03/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 20/03/2011',
            },
         'ranges' : {
             'default' : [['-boost::simd::Ten<T>()', 'boost::simd::Ten<T>()']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['saturate_at<boost::simd::tag::Pi>(a0)'],
                },
             'property_value' : {
                 'default' : ['a0>boost::simd::Pi<T>() ? boost::simd::Pi<T>() : (a0<-boost::simd::Pi<T>() ? -boost::simd::Pi<T>() :a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
