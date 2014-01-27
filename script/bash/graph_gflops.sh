#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Usage: `basename $0` <program>..."
    echo "If program is -, use content of existing res.txt file"
    echo "RUN_CMD may be defined to an arbitrary prefix command"
    echo "RUN_ARGS may be defined to an arbitrary list of arguments"
    exit 65
fi

# run all programs, filter undesired output
# count number of experiments and sizes
# validate number of sizes
# compute legend

prev_nb_sizes=0
nb_sizes=0
nb_experiments=0
prev_nb_experiments=0
LEGEND=""
TYPES=""
if [ "$1" != "-" ]
then
  rm -f res.txt
  for i in "$@"
  do
    $RUN_CMD $i $RUN_ARGS | stdbuf -o0 grep -Ev "CTEST_FULL_OUTPUT|---" | tee exp.txt | stdbuf -o0 tail -n +3 | tee temp.txt | tee -a res.txt
    nb_experiments=$(sed -n 1p exp.txt | awk  '{ print $5 }')
    ((nb_sizes=$(wc -l < temp.txt)/nb_experiments))
    EXTENSION=$(sed -n 1p exp.txt | awk  '{ print $2 }' | tr "_" ".")
    TEMP=$(head -n 1 temp.txt |   tr "_"  "\n" | sed 1d | tr "<" "\n" | sed -n 1p)
    if [ "${TEMP}" == "scalar" ];then
      EXTENSION="scalar"
    elif [ "${TEMP}" == "mkl" ];then
      EXTENSION="${EXTENSION} mkl"
    elif [ "${TEMP}" == "nt2" ];then
      EXTENSION="${EXTENSION} nt2"
    fi
    if [ "$LEGEND" == "" ]
      then
        LEGEND="legend(\"${EXTENSION}\""
      else
        LEGEND="$LEGEND, \"${EXTENSION}\""
    fi
    if [ $nb_sizes -ne $prev_nb_sizes ] && [ $prev_nb_sizes -ne 0 ]
    then
      echo "inconsistent number of sizes, has $nb_sizes, previous had $prev_nb_sizes" >&2
      exit 1
    fi
    if [ $nb_experiments -ne $prev_nb_experiments ] && [ $prev_nb_experiments -ne 0 ]
    then
      echo "inconsistent number of experiments, has $nb_experiments, previous had $prev_nb_experiments" >&2
      exit 1
    fi
    prev_nb_sizes=$nb_sizes
    prev_nb_experiments=$nb_experiments
  done
  LEGEND="${LEGEND} )"
  NUM_TEST=$#
  for ((ii=0;ii<${nb_experiments};ii++));do
      ((pos=${ii}*${nb_sizes}+1))
      BENCH_NAME[ii]=$(sed -n ${pos}p res.txt | awk '{ print $1 }' | tr "_" " " | tr "<" " " | tr ">" "\000")
      PLOT_NAME[ii]=$(sed -n ${pos}p res.txt | awk '{ print $1 }' | tr "_" "." | tr "<" "." | tr ">" "\000" )
      TITLE[ii]="title(\"${BENCH_NAME[${ii}]}\")"
  done
  for ((ii=0;ii<${nb_experiments};ii++));do
    filename="data${ii}.txt"
    echo ${NUM_TEST}>${filename}
    echo ${LEGEND}>>${filename}
    echo ${PLOT_NAME[ii]}>>${filename}
    echo ${TITLE[${ii}]}>>${filename}
    echo ${nb_sizes}>>${filename}
    echo ${nb_experiments}>>${filename}
  done
else
  nb_experiments=$(sed -n 6p data0.txt)
  for ((ii=0;ii<${nb_experiments};ii++));do
    filename="data${ii}.txt"
    NUM_TEST=$(sed -n 1p ${filename})
    LEGEND=$(sed -n 2p ${filename})
    PLOT_NAME[ii]=$(sed -n 3p ${filename})
    TITLE[ii]=$(sed -n 4p ${filename})
    nb_sizes=$(sed -n 5p ${filename})
  done
fi

i=0

# generate M-file
i=0
for ((kk=0;kk<${nb_experiments};kk++));do
  filename="create_plot${kk}.m"
  count=0
  for ((jj=0;jj<${NUM_TEST};jj++));do
    for ((ll=1;ll<=${nb_sizes};ll++));do
      ((pos=${jj}*${nb_sizes}*${nb_experiments}+${ll}+${kk}*${nb_sizes}))
      SIZE[count]=$(sed -n ${pos}p res.txt | tr "(" "\n" | tr ")" "\n" | sed -n 2p)
      CYC[count]=$(sed -n ${pos}p res.txt | cut -f3 )
      UNIT=$(sed -n ${pos}p res.txt | cut -f4 | tr " " "\n" | sed -n 1p)
      ((count++))
    done
  done

  for ((ii=10#0;ii<${nb_sizes};ii++));do
    for ((jj=10#0;jj<(${NUM_TEST});jj++));do
      q=(${ii}+${jj}*${nb_sizes})
      CYC2[${jj}+${ii}*(${NUM_TEST})]=${CYC[q]}
    done
  done

  for ((ii=0;ii<${nb_sizes};ii++));do
    declare "cyc${ii}=cyc${ii}"
  done
  ((size_x_axis=${nb_sizes}))
  for ((ii=0;ii<${NUM_TEST};ii++));do
    eval cyc${ii}='cyc${ii}=['
  done

  echo "hold on" > ${filename}
  echo "CYC2=[">>${filename}
  for ((ii=10#0;ii<${nb_sizes};ii++));do
    for ((jj=10#0;jj<(${NUM_TEST});jj++));do
      echo ${CYC2[${jj}+${ii}*(${NUM_TEST})]}>>${filename}
    done
  done
  echo "]">>${filename}
  X="x=["

  for ((i = 1 ; i <= ${size_x_axis} ; i++)); do
    X="$X $i"
  done
  for ((ii=10#0;ii<(${NUM_TEST});ii++));do
    for ((jj=10#0;jj<${nb_sizes};jj++));do
      ((q= ${jj} + ${ii}*${nb_sizes}))
      var=cyc${ii}
      temp="${!var} ${CYC[${q}]}"
      eval cyc${ii}='$temp'
      var=cyc${ii}
    done
  done

  for ((ii=0;ii<${NUM_TEST};ii++));do
    var=cyc${ii}
    temp="${!var} ]"
    eval cyc${ii}='$temp'
  done

  for ((ii=10#0;ii<(${NUM_TEST});ii++));do
    var=cyc${ii}
    echo ${!var} >> ${filename}
  done
  echo ${TITLE[kk]}  >> ${filename}

  X="$X ];"
  echo $X>>${filename}

  echo "num_y_ticks = round(max(CYC2))">>${filename}
  ((q=${gap}+1))
  echo "num_div=1;">>${filename}

  echo "max_y=max(CYC2)*1.2">>${filename}
  echo "y_inc = max_y/num_y_ticks">>${filename}
  echo "x_points=ones(1,num_y_ticks);">>${filename}
  echo "y_points=zeros(1,num_y_ticks);">>${filename}
  echo "if (max(CYC2)>1000)">>${filename}
  echo "  num_div=100;">>${filename}
  echo "elseif (max(CYC2)>160)">>${filename}
  echo "  num_div=16;">>${filename}
  echo "elseif (max(CYC2)>80)">>${filename}
  echo "  num_div=8;">>${filename}
  echo "elseif (max(CYC2)>40)">>${filename}
  echo "  num_div=4;">>${filename}
  echo "elseif (max(CYC2)>20)">>${filename}
  echo "  num_div=2;">>${filename}
  echo "elseif (max(CYC2)>10)">>${filename}
  echo "  num_div=1;">>${filename}
  echo "endif">>${filename}
  echo "num_y_ticks/=num_div;">>${filename}
  echo "y_points(1)=y_inc*num_div;">>${filename}
  echo "for i=2:num_y_ticks">>${filename}
  echo "  y_points(i)=y_points(i-1)+y_inc*num_div;">>${filename}
  echo "endfor">>${filename}

  echo "w=0.4;">>${filename}

  COLORS[0]=" '+r' "
  COLORS[1]=" '+g' "
  COLORS[2]=" '+b' "
  COLORS[3]=" '+c' "
  COLORS[4]=" '+y' "
  COLORS[5]=" \"+4\" "
  COLORS[6]=" '+','color',[255/255,140/255,0] "
  COLORS[7]=" '+','color',[0,0,0] "
  COLORS[8]=" '+','color',[34/255,139/255,34/255] "
  COLORS[9]=" '+','color',[218/255,165/255,32/255] "
  COLORS[10]=" '+','color',[255/255,140/255,0] "
  j=0
  for ((ii=0;ii<(${NUM_TEST});ii++));do
      echo "plot(x,cyc${ii},${COLORS[${ii}]},\"linestyle\",'-',\"linewidth\",2);">>${filename}
  done

  for ((ii=0;ii<${nb_sizes};ii++));do
    for ((jj=${gap}+1;jj<${gap}+(${NUM_TEST});jj++));do
      ((q= ${jj} + 1 + ${ii}*(${gap}+(${NUM_TEST}))))
      ((r=(${ii})*(${gap}+(${NUM_TEST}))+${gap}+1))
    done
  done

  echo "max_x = max(x)+0.25;">>${filename}
  echo ${LEGEND}>>${filename}
  echo "xx=[1 max_x max_x 1 1];">>${filename}
  echo "text(0.8,max_y/2-num_div,\"${UNIT}\",\"rotation\",90)">>${filename}
  echo "yy=[0 0 max_y max_y 0];">>${filename}
  echo "plot(xx,yy,'k')">>${filename}
  echo "ylim([-num_div*0.5 max_y])">>${filename}
  echo "axis off" >>${filename}
  echo "xlim([0.75 max_x]);">>${filename}

  for ((ii=1;ii<=${nb_sizes};ii++));do
    echo "text(x(${ii}),-num_div*0.3,\"${SIZE[ii-1]}\")">>${filename}
  done

  echo "box on" >>${filename}
  echo "plot(x_points,y_points,'+k')" >>${filename}
  echo "for i=1:num_y_ticks" >>${filename}
  echo "  text(x_points(i)-0.1,y_points(i),mat2str(i*num_div));" >>${filename}
  echo "endfor" >>${filename}
  echo "print ('-dpng','-color',\"${PLOT_NAME[kk]}.png\")">>${filename}
  echo "h = figure;">>${filename}
  echo "W = 12; H = 3;">>${filename}
  echo "set(h,'PaperUnits','inches')">>${filename}
  echo "set(h,'PaperOrientation','portrait');">>${filename}
  echo "set(h,'PaperSize',[H,W])">>${filename}
  echo "set(h,'PaperPosition',[0,0,W,H])">>${filename}
  echo "refresh">>${filename}

  octave ${filename} &>  /dev/null; display "${PLOT_NAME[kk]}.png" &
done
