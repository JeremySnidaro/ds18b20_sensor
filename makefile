#OBJS specifies which files to compile as part of the project 
OBJS1 = main_test_ds18b20.cpp ds18b20.cpp
OBJS2 = main_test_app.cpp app.cpp ds18b20.cpp

#CC specifies which compiler we're using
CC = g++

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS_1 = `pkg-config --cflags --libs glib-2.0 `
LINKER_FLAGS_2 = -I/usr/include/mysql 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = no_name_for_the_moment

#This is the target that compiles our executable
ds18b20 : $(OBJS1)
		$(CC) $(OBJS1) $(LINKER_FLAGS_1) $(LINKER_FLAGS_2) 
app : $(OBJS2)
		$(CC) $(OBJS2) $(LINKER_FLAGS_1) $(LINKER_FLAGS_2) 

