rm *.o test bot snd

g++ -c robot/gertbot/*.cpp --std=c++11 -march=native
g++ -c vision/*.cpp --std=c++11 -march=native
g++ -c robot/*.cpp --std=c++11 -march=native


g++ test.cpp *.o -std=c++11 -march=native -lopencv_core -lopencv_highgui -lopencv_imgproc -o test
g++ bot.cpp *.o -std=c++11 -march=native -lopencv_core -lopencv_highgui -lopencv_imgproc -o bot
g++ snd.cpp *.o -std=c++11 -march=native -lopencv_core -lopencv_highgui -lopencv_imgproc -o snd

rm *.o

