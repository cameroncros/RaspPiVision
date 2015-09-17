g++ test.cpp -march=native vision/*.cpp -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgproc -pthread -o test
g++ bot.cpp -march=native robot/*.cpp robot/gertbot/*.cpp vision/*.cpp -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgproc -pthread -o bot
