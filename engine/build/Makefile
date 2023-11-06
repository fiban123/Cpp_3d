LDFLAGS = -L../dependencies/GLEW/lib/Release/x64\
		-L../dependencies/GLFW/lib

LDLIBS = -lglew32s -lglfw3 -lopengl32

$(BUILD)/main.exe: $(OBJ)
	@echo LINKING $^
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)