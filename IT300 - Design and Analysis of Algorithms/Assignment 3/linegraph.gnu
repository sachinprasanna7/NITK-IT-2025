# Gnuplot script for line graph
set terminal pngcairo enhanced font 'Verdana,12'
set output 'line_graph.png'

set title 'Sorting Algorithms Time Comparison'
set xlabel 'Input Size'
set ylabel 'Time (ms)'
set key left top

# Defining line styles and colors
set style line 1 lc rgb 'red' lt 1 lw 2
set style line 2 lc rgb 'green' lt 1 lw 2
set style line 3 lc rgb 'blue' lt 1 lw 2
set style line 4 lc rgb 'yellow' lt 1 lw 2
set style line 5 lc rgb 'cyan' lt 1 lw 2

plot 'results.dat' using 1:2 with lines ls 1 title 'Selection', \
     'results.dat' using 1:3 with lines ls 2 title 'Insertion', \
     'results.dat' using 1:4 with lines ls 3 title 'Bubble', \
     'results.dat' using 1:5 with lines ls 4 title 'Merge', \
     'results.dat' using 1:6 with lines ls 5 title 'Quick'
