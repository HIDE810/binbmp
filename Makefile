TARGET		:=	binbmp
INCLUDE		:=	inc
SOURCE		:=	$(wildcard src/*.cpp)
BMP			:=	$(wildcard *.bmp)
CXXFLAGS	:=	-std=c++17 -I $(INCLUDE)

ifeq ($(OS),Windows_NT)
	EXT	:=	.exe
else
	EXT	:=	.out
endif

all:
	@$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)$(EXT)

clean:
	@$(RM) $(TARGET)$(EXT) $(BMP)