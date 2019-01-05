CC  	= gcc
CCLIBS	= -lGL -lGLU -lglut
CFLAGS	= -lm
PROGRAM	= ball
OBJ 	= 		 	 \
	main.o  	 	 \
	DrawingElements.o	 \
	Print.o          	 \
	CallBack.o		 \
	
	
VPATH 	= src


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(PROGRAM)
