source setenv.sh // setup compile tool chain, make sure compiler is in $PATH
make spi -s // make all
make clean // clean up all
make // make main code
make rom // make main rom
cd boot;make // make boot code
cd boot;make rom // make boot rom
