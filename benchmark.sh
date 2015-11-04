for i in $( ls tests ); do
./test ./tests/$i RGBBasic 1000 ./tests/blueball.txt
./test ./tests/$i HSVBasic 1000 ./tests/blueball.txt
./test ./tests/$i HSVRegion 1000 ./tests/blueball.txt
./test ./tests/$i HSVRegionMinAlloc 1000 ./tests/blueball.txt
./test ./tests/$i HoughCircleDetection 1000 ./tests/blueball.txt
./test ./tests/$i BasicShapeDetection 1000 ./tests/blueball.txt
done;
