OBJ= gl/gl gl/shader gl/program gl/vbo gl/fbo \
	 util/file util/matrix \
	 window/window \
	 loop/single \
	 gui/text/atlas gui/text/program gui/text/vbo gui/text/ibo gui/text/text \
	 game/test/scene game/test/input game/test/display
LIB=m GL glfw GLEW freetype
MAIN=main
APP=app

CC=gcc
CC_FLAGS=-Wall -O2 -L"lib/" -I"include/" -I"/usr/include/freetype2/"

SRC=src
OBJ_PATH=obj
OBJ_SUB=util gl window loop sound game/test gui/text
BUILD=build

OBJ_FILES=$(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(OBJ)))
LIB_FLAGS=$(addprefix -l, $(LIB))
OBJ_PATHS=$(addprefix $(OBJ_PATH)/, $(OBJ_SUB))

define cc-obj
$(CC) -c $(CC_FLAGS) $< -o $@
endef

define cc-app
$(CC) $(CC_FLAGS) $(SRC)/$(MAIN).c -o $(BUILD)/$(APP) $(OBJ_FILES) $(LIB_FLAGS)
endef

$(APP): $(OBJ_FILES) $(OBJ_PATH) $(BUILD)
	$(cc-app)

$(BUILD):
	mkdir $(BUILD)

$(OBJ_PATH)/%.o: $(SRC)/%.c $(OBJ_PATHS)
	$(cc-obj)

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATHS):
	mkdir -p $@

clean:
	rm -f $(BUILD)/$(APP) $(OBJ_FILES)
