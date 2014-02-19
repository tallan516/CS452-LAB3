#include "timShader.h"

#include "SDL2/SDL.h"

using namespace std;

GLuint abuffer;
GLuint buffer[2];
GLuint ebuffer;
GLuint program;

//GLfloat pit,yaw,scalar=1;
glm::vec3 cubeTran;

GLfloat vertices[] = {	-10.0f,-10.0f,-10.0f,
				10.0f,-10.0f,-10.0f,
				0.0f,-10.0f,10.0f,
				0.0f,10.0f,10.0f	};


				//R, B, G, A (transparency)
GLfloat colors[] = {	1.0f,0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f	}; 

GLubyte elems[] = {	0,1,2,3,7,4,5,6,
    	          		7,3,0,4,5,6,2,1,
    		  		0,1,5,4,7,3,2,6	};

//Declare functions
void init();
void display(SDL_Window* window);


int main(int argc, char **argv)
{
	//Main method stuff
	SDL_Window *window;	//SDL window
	if(SDL_Init(SDL_INIT_VIDEO) < 0)	//Tries to intitiate SDL
	{
		cerr << "Error, cannot initialize SDL." << endl;
		SDL_Quit();		//Close out of SDL
		exit(0);		//End program
	}
	
	//Create window
	window = SDL_CreateWindow("CS452-LAB3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_OPENGL);
	
	//Check window creation
	if(window == NULL)
	{
		cerr << "Error, cannot create window." << endl;
	}
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);		//Creates opengl context associated with the window
	glewInit();		//Initializes glew
	init();	//Calls function to initialize the shaders and set up buffers
	
	//Keep looping through to make sure
	while(true)
	{
		//input(window);		//Check keyboard input
		display(window);		//Render
	}
	
	//Close out of SDL stuff
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

void display(SDL_Window* window)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		//Clears the frame buffer
	
	
	
	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, NULL);
	glFlush();					//Makes sure all data is rendered as soon as possible
	SDL_GL_SwapWindow(window);		//Updates the window
}

void init()
{
	initShaders();	//Calls the initialize shader function in the header file
	
	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);
	
	glGenBuffers(2, buffer);
	
	//Sets up pointers and stuff
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 8, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glGenBuffers(1, &ebuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elems), elems, GL_STATIC_DRAW);
	
	//Enables vertex arrays to draw stuff
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
}



