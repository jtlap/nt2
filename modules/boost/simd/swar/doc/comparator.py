[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['Compute the min and the max of the first two inputs if the third non zero,',
                         ' or by the max and the min if the third is zero.'
                         'The function returns a value indicating if anything has changed',    
                           ],
            'return' :[ 'a bool value or a fusion vector of the bool and the two other results'],
            'param_2':['a scalar integer value'],
            'param_3':['min or max of a0 and a1, according a2 is non zero'],
            'param_4':['max or min of a0 and a1, according a2 is non zero'],
          'special_synopsis' : [
                "template<class A0,class A1> inline",
                "typename boost::dispatch::meta::call<tag::comparator_(A0 const&,A0 const&,A1 const&)",
                "                                    >::type",
                "comparator(A0 const& a0,A0 const& a1,A1 const& a2);",
                " ",
                "template<class A0,class A1> inline",
                "bool comparator(A0 const& a0,A0 const& a1,A1& a2,A0& a3,A0& a4);",
                 ],
            'max_arity' :'5',
         'module' : 'boost',
         'arity' : '3',
         'call_types' : ['T', 'T', 'iT'],
         'ret_arity' : '3',
         'rturn' : {
             'default' : 'boost::fusion::tuple<T,T,bool>',
            },
         'scalar_ints': 'True',   
         'simd_types' : ['real_'],
         'special' : ['swar'],  
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'simd_included' : ['#include <boost/simd/include/functions/all.hpp>',
                           '#include <boost/simd/include/functions/max.hpp>',
                           '#include <boost/simd/include/functions/min.hpp>',],
             'cover_included' : ['#include <boost/simd/include/functions/all.hpp>',
                           '#include <boost/simd/include/functions/max.hpp>',
                           '#include <boost/simd/include/functions/min.hpp>',],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()'],['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()'],['iT(0)', 'iT(1)']],
             'real_' : [['T(-100)', 'T(100)'],['T(-100)', 'T(100)'],['iT(0)', 'iT(1)']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : ['boost::simd::One<r_t0>()', 'boost::simd::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : ['boost::simd::Zero<r_t0>()', 'boost::simd::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : ['boost::simd::Inf<r_t0>()', 'boost::simd::Inf<r_t1>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : ['boost::simd::Minf<r_t0>()', 'boost::simd::Minf<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : ['boost::simd::Mone<r_t0>()', 'boost::simd::Mone<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : ['boost::simd::Nan<r_t0>()', 'boost::simd::Nan<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : ['boost::simd::One<r_t0>()', 'boost::simd::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : ['boost::simd::Zero<r_t0>()', 'boost::simd::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : {'result' : ['boost::simd::Mone<r_t0>()', 'boost::simd::Mone<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : ['boost::simd::One<r_t0>()', 'boost::simd::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : ['boost::simd::Zero<r_t0>()', 'boost::simd::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::comparator(a0,a1,a2)'],
                },
             'property_value' : {
                 'default' : [['boost::simd::max(a0,a1)', 'boost::simd::min(a0,a1)', 'a0<=a1']],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        vT ma = boost::simd::max(a0,a1);",
                        "        vT mi = boost::simd::min(a0,a1);",
                        "        NT2_TEST(boost::simd::all(boost::simd::eq(boost::fusion::get<0>(v),(a2)?ma:mi)));",
                        "        NT2_TEST(boost::simd::all(boost::simd::eq(boost::fusion::get<1>(v),(a2)?mi:ma)));",
                            ]
               },
            },
        },
    },
]
