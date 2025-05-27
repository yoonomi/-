CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = 

# 源文件和目标文件
SRCS = main.cpp Package.cpp DatabaseManager.cpp SystemManager.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = express_system

# 默认目标
all: $(TARGET)

# 链接
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 编译规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)

# 运行
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run 