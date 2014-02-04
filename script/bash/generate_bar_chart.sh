nb_data_types=$1
NUM_TEST=$2
nb_sizes=$3
LEGEND=$4
TITLE=$5
PLOT_NAME=$6
kk=$7

i=0
filename="create_plot${kk}.m"
count=0
for ((jj=0;jj<${NUM_TEST};jj++));do
  for ((ll=1;ll<=${nb_sizes};ll++));do
    ((pos=${jj}*${nb_sizes}*${nb_data_types}+${ll}+${kk}*${nb_sizes}))
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

gap=5
((size_x_axis=${gap}*(${nb_sizes}+1)+(${NUM_TEST})*${nb_sizes}))
cyc='cyc=['

echo "hold on" > ${filename}
X="x=["

for ((i = 1 ; i <= ${size_x_axis} ; i++)); do
  X="$X $i"
done

for ((ii=0;ii<${nb_sizes};ii++));do
  for ((jj=10#0;jj<${gap}+(${NUM_TEST});jj++));do
    if ((jj<${gap}));then
      cyc="${cyc} 0"
    else
      ((q= (${jj}-${gap}) + ${ii}*(${NUM_TEST})))
      cyc="${cyc} ${CYC2[${q}]}"
    fi
  done
done
for ((ii=0;ii<${gap};ii++));do
  cyc="${cyc} 0"
done
cyc="${cyc} ];"

echo ${cyc} >> ${filename}
echo ${TITLE[kk]} >> ${filename}
X="$X ];"
echo $X>>${filename}

echo "num_y_ticks = round(max(cyc))">>${filename}
((q=${gap}+1))
echo "num_div=1;">>${filename}

echo "max_y=max(cyc)*1.2">>${filename}
echo "y_inc = floor(max_y/num_y_ticks)">>${filename}
echo "x_points=ones(1,num_y_ticks);">>${filename}
echo "y_points=zeros(1,num_y_ticks);">>${filename}
echo "  y_dist=2;">>${filename}
echo "if (max(cyc)>1000)">>${filename}
echo "  num_div=100;">>${filename}
echo "  y_dist=3;">>${filename}
echo "elseif (max(cyc)>500)">>${filename}
echo "  num_div=50;">>${filename}
echo "  y_dist=2;">>${filename}
echo "elseif (max(cyc)>160)">>${filename}
echo "  num_div=16;">>${filename}
echo "elseif (max(cyc)>80)">>${filename}
echo "  num_div=8;">>${filename}
echo "elseif (max(cyc)>40)">>${filename}
echo "  num_div=4;">>${filename}
echo "elseif (max(cyc)>20)">>${filename}
echo "  num_div=2;">>${filename}
echo "elseif (max(cyc)>10)">>${filename}
echo "  num_div=1;">>${filename}
echo "endif">>${filename}
echo "num_y_ticks/=num_div;">>${filename}
echo "y_points(1)=y_inc*num_div;">>${filename}
echo "for i=2:num_y_ticks">>${filename}
echo "  y_points(i)=y_points(i-1)+y_inc*num_div;">>${filename}
echo "endfor">>${filename}

echo "w=0.4;">>${filename}

COLORS[0]=" 'r' "
COLORS[1]=" 'g' "
COLORS[2]=" 'b' "
COLORS[3]=" 'c' "
COLORS[4]=" 'y' "
COLORS[5]=" \"4\" "
COLORS[6]=" \"5\" "
COLORS[7]=" \"6\" "
COLORS[8]=" 'r' "
COLORS[9]=" 'g' "
COLORS[10]=" 'b' "
j=0
for ((ii=gap;ii<${size_x_axis};ii+=${gap}+(${NUM_TEST})));do
  for ((jj=10#;jj<(${NUM_TEST});jj++));do
    ((q=${ii}+1+${jj}))
    echo "bar(x(${q}),cyc(${q}),w,${COLORS[jj]});">>${filename}
  done
done

for ((ii=0;ii<${nb_sizes};ii++));do
  for ((jj=${gap}+1;jj<${gap}+(${NUM_TEST});jj++));do
    ((q= ${jj} + 1 + ${ii}*(${gap}+(${NUM_TEST}))))
    ((r=(${ii})*(${gap}+(${NUM_TEST}))+${gap}+1))
    if [ "$UNIT" ==  "GFLOPS" ];then
      echo "t=strcat(\"x\",mat2str(cyc(${q})/cyc(${r}),2));">>${filename}
    else
      echo "t=strcat(\"x\",mat2str(cyc(${r})/cyc(${q}),2));">>${filename}
    fi
    echo "H=text(x(${q}),cyc(${q})+num_div*0.05,t,\"rotation\",90)">>${filename}
    echo "set(H,'fontsize',7)">>${filename}
  done
done

echo "max_x = max(x)+${gap};">>${filename}

echo ${LEGEND}>>${filename}
echo "xx=[1 max_x max_x 1 1];">>${filename}
echo "text(-y_dist,max_y/2-num_div,\"${UNIT}\",\"rotation\",90)">>${filename}
echo "yy=[0 0 max_y max_y 0];">>${filename}
echo "plot(xx,yy,'k')">>${filename}
echo "ylim([-num_div*0.5 max_y])">>${filename}
echo "axis off" >>${filename}
echo "xlim([-y_dist max_x]);">>${filename}

for ((ii=1;ii<=${nb_sizes};ii++));do
  ((q=${gap}+(${ii}-1)*(${gap}+(${NUM_TEST}))))
  echo "text(x(${q}),-num_div*0.3,\"${SIZE[ii-1]}\")">>${filename}
done

echo "box on" >>${filename}
echo "plot(x_points,y_points,'+k')" >>${filename}
echo "for i=1:num_y_ticks" >>${filename}
echo "  text(x_points(i)-y_dist,y_points(i),mat2str(i*num_div));" >>${filename}
echo "endfor" >>${filename}
echo "print ('-dpng','-color',\"${PLOT_NAME}.png\")">>${filename}
echo "h = figure;">>${filename}
echo "W = 12; H = 3;">>${filename}
echo "set(h,'PaperUnits','inches')">>${filename}
echo "set(h,'PaperOrientation','portrait');">>${filename}
echo "set(h,'PaperSize',[H,W])">>${filename}
echo "set(h,'PaperPosition',[0,0,W,H])">>${filename}
echo "refresh">>${filename}


octave ${filename} &>  /dev/null; display "${PLOT_NAME}.png" &
