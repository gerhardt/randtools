for i in `ls *.dat`; 

do 
BINNAME=`echo $i | sed s/.dat/.bin/`
if [ ! -e $BINNAME ]; then
echo "converting $i to BIN"
./dat2bin.py $i &
fi

NEUNAME=`echo $i | sed s/.dat/.neu/`
if [ ! -e $NEUNAME ]; then
echo "converting $i to NEU"
./dat2neu.py $i &
fi

SELNAME=`echo $i | sed s/.dat/_20000.sel/`
if [ ! -e $NEUNAME ]; then
echo "converting $i to SEL"
./dat2sel.py $i 20000 &
fi

done;
