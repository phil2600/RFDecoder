#! /bin/sh

rrdtool graph ../THGR810-55_hyg.png -a PNG --title="Humidity" \
--height=200 --width=750 --base=1000  \
--alt-autoscale \
--interlaced \
--color 'CANVAS#000000'				  \
--color 'BACK#101010'				  \
--color 'FONT#C0C0C0'				  \
--color 'MGRID#80C080'				  \
--color 'GRID#808020'				  \
--color 'FRAME#808080'				  \
--color 'ARROW#FFFFFF'				  \
--color 'SHADEA#404040'				  \
--color 'SHADEB#404040'				  \
--start end-1d \
--vertical-label '%' \
'DEF:probe1=hygDB.rrd:THGR810-55:AVERAGE' \
'LINE1:probe1#ff0000:Chamber (THGR810-55)' \
'GPRINT:probe1:LAST:Last\: %2.1lf\n'



rrdtool graph ../all_temp.png -a PNG --title="Temperatures" \
--height=200 --width=750 --base=1000  \
--alt-autoscale \
--interlaced \
--color 'CANVAS#000000'				  \
--color 'BACK#101010'				  \
--color 'FONT#C0C0C0'				  \
--color 'MGRID#80C080'				  \
--color 'GRID#808020'				  \
--color 'FRAME#808080'				  \
--color 'ARROW#FFFFFF'				  \
--color 'SHADEA#404040'				  \
--color 'SHADEB#404040'				  \
--start end-1d \
--vertical-label "Deg C" \
'DEF:probe1=tempDB.rrd:THN132N-AC:AVERAGE' \
'DEF:probe2=tempDB.rrd:THN132N-5E:AVERAGE' \
'DEF:probe3=tempDB.rrd:THGR810-55:AVERAGE' \
'LINE1:probe1#ff0000:Outdoor (THN132N-AC)' \
VDEF:p1_MIN=probe1,MINIMUM \
VDEF:p2_MIN=probe2,MINIMUM \
VDEF:p3_MIN=probe3,MINIMUM \
VDEF:p1_MAX=probe1,MAXIMUM \
VDEF:p2_MAX=probe2,MAXIMUM \
VDEF:p3_MAX=probe3,MAXIMUM \
VDEF:p1_AVG=probe1,AVERAGE \
VDEF:p2_AVG=probe2,AVERAGE \
VDEF:p3_AVG=probe3,AVERAGE \
'GPRINT:p1_MIN:Min\: %8.2lf%s' \
'GPRINT:p1_AVG:Avg\: %8.2lf%s' \
'GPRINT:p1_MAX:Max\: %8.2lf%s' \
'GPRINT:probe1:LAST:Last\: %2.1lf\n' \
'LINE1:probe2#0000ff:Kitchen (THN132N-5E)' \
'GPRINT:p2_MIN:Min\: %8.2lf%s' \
'GPRINT:p2_AVG:Avg\: %8.2lf%s' \
'GPRINT:p2_MAX:Max\: %8.2lf%s' \
'GPRINT:probe2:LAST:Last\: %2.1lf\n' \
'LINE1:probe3#00cc4a:Chamber (THGR810-55)' \
'GPRINT:p3_MIN:Min\: %8.2lf%s' \
'GPRINT:p3_AVG:Avg\: %8.2lf%s' \
'GPRINT:p3_MAX:Max\: %8.2lf%s' \
'GPRINT:probe3:LAST:Last\: %2.1lf'



rrdtool graph ../THN132N-AC_temp.png -a PNG --title="Temperature" \
--height=200 --width=750 \
--color 'CANVAS#000000'				  \
--color 'BACK#101010'				  \
--color 'FONT#C0C0C0'				  \
--color 'MGRID#80C080'				  \
--color 'GRID#808020'				  \
--color 'FRAME#808080'				  \
--color 'ARROW#FFFFFF'				  \
--color 'SHADEA#404040'				  \
--color 'SHADEB#404040'				  \
--start end-1d --vertical-label "Deg C" \
'DEF:probe1=tempDB.rrd:THN132N-AC:AVERAGE' \
"CDEF:under_0=probe1,0,LT,probe1,0,IF" 		\
"CDEF:over_15=probe1,15,GT,probe1,0,IF"             \
"CDEF:right=probe1,0,GE,probe1,15,GT,0,probe1,IF,0,IF"             \
'HRULE:15#0000FF' \
'HRULE:0#0000FF' \
'COMMENT: Outdoor (THN132N-AC)\j' \
'COMMENT:\n' \
'AREA:over_15#00FF00:Potentially Go Out'            \
'AREA:under_0#FF0000:Freeeeeze'            \
'AREA:right#0000FF:Damn Too cold !'            \
'GPRINT:probe1:LAST: %2.1lf C\j'

rrdtool graph ../THN132N-5E_temp.png -a PNG --title="Temperature" \
--height=200 --width=750 \
--color 'CANVAS#000000'				  \
--color 'BACK#101010'				  \
--color 'FONT#C0C0C0'				  \
--color 'MGRID#80C080'				  \
--color 'GRID#808020'				  \
--color 'FRAME#808080'				  \
--color 'ARROW#FFFFFF'				  \
--color 'SHADEA#404040'				  \
--color 'SHADEB#404040'				  \
--start end-1d --vertical-label "Deg C" \
'DEF:probe1=tempDB.rrd:THN132N-5E:AVERAGE' \
"CDEF:under_18=probe1,18,LT,probe1,0,IF" 		\
"CDEF:over_22=probe1,22,GT,probe1,0,IF"             \
"CDEF:right=probe1,18,GE,probe1,22,GT,0,probe1,IF,0,IF"             \
'HRULE:22#0000FF' \
'HRULE:18#0000FF' \
'COMMENT: Kitchen (THN132N-5E)\j' \
'COMMENT:\n' \
'AREA:over_22#FF0000:OMGWFTBBQ'            \
'AREA:under_18#0000FF:Damn Too cold !'            \
'AREA:right#00FF00:Good'            \
'GPRINT:probe1:LAST: %2.1lf C\j'

rrdtool graph ../THGR810-55_temp.png -a PNG --title="Temperature" \
--height=200 --width=750 \
--color 'CANVAS#000000'				  \
--color 'BACK#101010'				  \
--color 'FONT#C0C0C0'				  \
--color 'MGRID#80C080'				  \
--color 'GRID#808020'				  \
--color 'FRAME#808080'				  \
--color 'ARROW#FFFFFF'				  \
--color 'SHADEA#404040'				  \
--color 'SHADEB#404040'				  \
--start end-1d --vertical-label "Deg C" \
'DEF:probe1=tempDB.rrd:THGR810-55:AVERAGE' \
"CDEF:under_18=probe1,18,LT,probe1,0,IF" 		\
"CDEF:over_22=probe1,22,GT,probe1,0,IF"             \
"CDEF:right=probe1,18,GE,probe1,22,GT,0,probe1,IF,0,IF"             \
'HRULE:22#0000FF' \
'HRULE:18#0000FF' \
'COMMENT: Chamber (THGR810-55)\j' \
'COMMENT:\n' \
'AREA:over_22#FF0000:OMGWFTBBQ'            \
'AREA:under_18#0000FF:Damn Too cold !'            \
'AREA:right#00FF00:Good'            \
'GPRINT:probe1:LAST: %2.1lf C\j'


