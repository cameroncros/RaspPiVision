g++ test.cpp vision/*.cpp -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgproc -o test
g++ bot.cpp robot/*.cpp robot/gertbot/*.cpp vision/*.cpp -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgproc -o bot
g++ snd.cpp robot/*.cpp robot/gertbot/*.cpp vision/*.cpp -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgproc -o snd

