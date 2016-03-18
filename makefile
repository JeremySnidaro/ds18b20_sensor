#OBJS specifies which files to compile as part of the project 
OBJS = main_test_ds18b20.cpp ds18b20.cpp

#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = `pkg-config --cflags --libs glib-2.0`

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = no_name_for_the_moment

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 

