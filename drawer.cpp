#include <iostream>
#include "drawer.h"

using namespace std;

ObjectType drawType = Line;
int     curIndex = 0;
Object  curObject;
vector<Object> objects;
bool draged = false;
bool attractedByGrid = false;
bool showGrid = true;
bool showAxes = true;
bool showCursor = true;
vector<Symbol> colorTable;
GLfloat colors[][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1},{1,1,1},{0,0,0}};
Symbol triangleButton;
Symbol squareButton;
Symbol lineButton;
Symbol boldLineButton;
Symbol ballButton;
Symbol ballPartButton;
Symbol circleButton;
Symbol tetrahedronButton;
Symbol cylinderButton;
Symbol coneButton;
Symbol attractButton;
Symbol undoButton;
Symbol saveButton;
Symbol loadButton;
Symbol clearButton;
Symbol showGridButton;
Symbol showAxesButton;
Symbol showCursorButton;
vector<Symbol> shapes;

double z(double x, double y)
{
	double r2 = x*x + y*y;
	return sin(r2/3)/(r2+3);
}

void init(const char * title,int *argc,char *argv[])
{
	initRoutine(title,argc,argv);
	curObject = newObject(drawType,1,1,1,specular,shrininess);
	
	GLfloat x0 = 0, y0 = 50;
	
	for(int i = 0; i<8; i++)
	{
		colorTable.push_back(newSymbol());
		x0 += 50;
		colorTable.back().objects.push_back
		(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,colors[i][0],colors[i][1],colors[i][2]));
	}
	
	x0 += 100;
	triangleButton.objects.push_back(newTriangle(x0,y0,x0+50,y0,x0+25,y0+50,1,1,1));
	
	x0 += 60;
	squareButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	lineButton.objects.push_back(newLine(x0+5,y0+5,x0+45,y0+45,0,0,0));
	lineButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	boldLineButton.objects.push_back(newSquare(x0+7,y0+3,x0+3,y0+7,x0+43,y0+47,x0+47,y0+43,0,0,0));
	boldLineButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	ballButton.objects.push_back(newCircle(x0+25,y0+25,1,1,1,25));
	
	x0 += 60;
	ballPartButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+30,x0,y0+30,0,0,0));
	ballPartButton.objects.push_back(newCircle(x0+25,y0+25,1,1,1,25));
	
	x0 += 60;
	circleButton.objects.push_back(newCircle(x0+25,y0+25,0,0,0,25));
	circleButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	tetrahedronButton.objects.push_back(newTriangle(x0,y0+15,x0+15,y0,x0+15,y0+50,1,1,1));
	tetrahedronButton.objects.push_back(newTriangle(x0+50,y0+15,x0+15,y0,x0+15,y0+50,1,0,0));
	
	x0 += 60;
	cylinderButton.objects.push_back(newCircle(x0+25,y0+35,1,0,0,15));
	cylinderButton.objects.push_back(newSquare(x0+10,y0+15,x0+40,y0+15,x0+40,y0+35,x0+10,y0+35,1,1,1));
	cylinderButton.objects.push_back(newCircle(x0+25,y0+15,1,1,1,15));
	
	x0 += 60;
	coneButton.objects.push_back(newTriangle(x0+10,y0+15,x0+40,y0+15,x0+25,y0+35,1,1,1));
	coneButton.objects.push_back(newCircle(x0+25,y0+15,1,1,1,15));
	
	x0 += 100;
	attractButton.objects.push_back(newLine(x0+25,y0,x0+25,y0+50,0,0,0));
	attractButton.objects.push_back(newLine(x0,y0+25,x0+50,y0+25,0,0,0));
	attractButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	undoButton.objects.push_back(newLine(x0+5,y0+5,x0+45,y0+45,0,0,0));
	undoButton.objects.push_back(newLine(x0+45,y0+5,x0+5,y0+45,0,0,0));
	undoButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	saveButton.objects.push_back(newSquare(x0+15,y0+50,x0+35,y0+50,x0+35,y0+25,x0+15,y0+25,1,1,1));
	saveButton.objects.push_back(newTriangle(x0+5,y0+25,x0+45,y0+25,x0+25,y0+5,1,1,1));
	saveButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+5,x0,y0+5,1,1,1));
	
	x0 += 60;
	loadButton.objects.push_back(newSquare(x0+15,y0+5,x0+35,y0+5,x0+35,y0+30,x0+15,y0+30,1,1,1));
	loadButton.objects.push_back(newTriangle(x0+5,y0+30,x0+45,y0+30,x0+25,y0+50,1,1,1));
	loadButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+5,x0,y0+5,1,1,1));
	
	x0 += 60;
	clearButton.objects.push_back(newSquare(x0+5,y0+5,x0+45,y0+5,x0+45,y0+45,x0+5,y0+45,0,0,0));
	clearButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	showGridButton.objects.push_back(newLine(x0+12,y0,x0+12,y0+50,0,0,0));
	showGridButton.objects.push_back(newLine(x0+25,y0,x0+25,y0+50,0,0,0));
	showGridButton.objects.push_back(newLine(x0+38,y0,x0+38,y0+50,0,0,0));
	showGridButton.objects.push_back(newLine(x0,y0+12,x0+50,y0+12,0,0,0));
	showGridButton.objects.push_back(newLine(x0,y0+25,x0+50,y0+25,0,0,0));
	showGridButton.objects.push_back(newLine(x0,y0+38,x0+50,y0+38,0,0,0));
	showGridButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	showAxesButton.objects.push_back(newLine(x0+25,y0,x0+25,y0+50,1,0,0));
	showAxesButton.objects.push_back(newLine(x0,y0+25,x0+50,y0+25,0,0,1));
	showAxesButton.objects.push_back(newLine(x0,y0+12,x0+50,y0+38,0,1,0));
	showAxesButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
	
	x0 += 60;
	showCursorButton.objects.push_back(newTriangle(x0+25,y0+50,x0+20,y0+25,x0+30,y0+25,0,0,0));
	showCursorButton.objects.push_back(newTriangle(x0+25,y0,x0+20,y0+25,x0+30,y0+25,0,0,0));
	showCursorButton.objects.push_back(newTriangle(x0,y0+25,x0+25,y0+30,x0+25,y0+20,0,0,0));
	showCursorButton.objects.push_back(newTriangle(x0+50,y0+25,x0+25,y0+30,x0+20,y0+20,0,0,0));
	showCursorButton.objects.push_back(newSquare(x0,y0,x0+50,y0,x0+50,y0+50,x0,y0+50,1,1,1));
}

void updateCurObject()
{
	switch(drawType)
	{
	case Line:
	case BoldLine:
	case Triangle:
	case Square:
	case Tetrahedron:
		if(curIndex<requiredNumberOfSteps(drawType))
		{
			curObject.points[curIndex][0] = cursorx;
			curObject.points[curIndex][1] = cursory;
			curObject.points[curIndex][2] = cursorz;
		}
		break;
	case Ball:
		if(curIndex==0)
		{
			curObject.points[curIndex][0] = cursorx;
			curObject.points[curIndex][1] = cursory;
			curObject.points[curIndex][2] = cursorz;
		}
		else if(curIndex==1)
		{
			GLfloat dx = cursorx - curObject.points[0][0];
			GLfloat dy = cursory - curObject.points[0][1];
			GLfloat dz = cursorz - curObject.points[0][2];
			curObject.radius = sqrt(dx*dx+dy*dy+dz*dz);
			std::ostringstream os;
			os << "r: " << curObject.radius;
			printString(os.str().c_str(),colors[6],20,50,800);
		}
		break;
	case BallPart:
		if(curIndex==0)
		{
			curObject.points[curIndex][0] = cursorx;
			curObject.points[curIndex][1] = cursory;
			curObject.points[curIndex][2] = cursorz;
		}
		else if(curIndex==1)
		{
			GLfloat dx = cursorx - curObject.points[0][0];
			GLfloat dy = cursory - curObject.points[0][1];
			GLfloat dz = cursorz - curObject.points[0][2];
			curObject.radius = sqrt(dx*dx+dy*dy+dz*dz);
			std::ostringstream os;
			os << "r: " << curObject.radius;
			printString(os.str().c_str(),colors[6],20,50,800);
		}
		else if(curIndex==2)
		{
			curObject.points[1][0] = cursorx;
			curObject.points[1][1] = cursory;
			curObject.points[1][2] = cursorz;
		}
		break;
	case Circle:
		if(curIndex==0)
		{
			curObject.points[0][0] = cursorx;
			curObject.points[0][1] = cursory;
			curObject.points[0][2] = cursorz;
		}
		else if(curIndex==1)
		{
			GLfloat dx = cursorx - curObject.points[0][0];
			GLfloat dy = cursory - curObject.points[0][1];
			GLfloat dz = cursorz - curObject.points[0][2];
			curObject.points[2][0] = cursorx;
			curObject.points[2][1] = cursory;
			curObject.points[2][2] = cursorz;
			curObject.radius = sqrt(dx*dx+dy*dy+dz*dz);
			std::ostringstream os;
			os << "r: " << curObject.radius;
			printString(os.str().c_str(),colors[6],20,50,800);
		}
		else if(curIndex==2)
		{
			GLfloat d1[] = {curObject.points[2][0]-curObject.points[0][0],
							curObject.points[2][1]-curObject.points[0][1],
							curObject.points[2][2]-curObject.points[0][2]};
			GLfloat d2[] = {cursorx-curObject.points[0][0],
							cursory-curObject.points[0][1],
							cursorz-curObject.points[0][2]};
			GLfloat r[3];
			crossProduct(d1,d2,r);
			curObject.points[1][0] = curObject.points[0][0]+r[0];
			curObject.points[1][1] = curObject.points[0][1]+r[1];
			curObject.points[1][2] = curObject.points[0][2]+r[2];
		}
		break;
	case Cylinder:
	case Cone:
		if(curIndex==0 || curIndex==1)
		{
			curObject.points[curIndex][0] = cursorx;
			curObject.points[curIndex][1] = cursory;
			curObject.points[curIndex][2] = cursorz;
		}
		else if(curIndex==2)
		{
			GLfloat bottom[] = {curObject.points[0][0]-curObject.points[1][0],
								curObject.points[0][1]-curObject.points[1][1],
								curObject.points[0][2]-curObject.points[1][2]};
			GLfloat edge1[] = { cursorx-curObject.points[0][0],
								cursory-curObject.points[0][1],
								cursorz-curObject.points[0][2]};
			GLfloat edge2[] = { cursorx-curObject.points[1][0],
								cursory-curObject.points[1][1],
								cursorz-curObject.points[1][2]};
			GLfloat b = sqrt(bottom[0]*bottom[0]+bottom[1]*bottom[1]+bottom[2]*bottom[2]);
			GLfloat e1 = sqrt(edge1[0]*edge1[0]+edge1[1]*edge1[1]+edge1[2]*edge1[2]);
			GLfloat e2 = sqrt(edge2[0]*edge2[0]+edge2[1]*edge2[1]+edge2[2]*edge2[2]);
			GLfloat p = (b+e1+e2)/2;
			GLfloat S = sqrt(p*(p-b)*(p-e1)*(p-e2));
			curObject.radius = 2*S/b;
			std::ostringstream os;
			os << "r: " << curObject.radius;
			printString(os.str().c_str(),colors[6],20,50,800);
		}
		break;
	}
}

void display()
{
	displayRoutine();
	
	if(showAxes) drawAxes();
	if(showGrid) drawGrid();
	//drawLight();
	
	for(int i = 0; i < objects.size(); i++)
	{
		drawObject(objects[i]);
	}
	prepareFor2D();
	
	printCoordinate();
	
	printString("Press Z to move in Y-O-Z plane\nPress X to move in X-O-Z plane",
				colors[6],20,700,950);
	
	for(int i = 0; i<colorTable.size(); i++)
		printSymbol(colorTable[i]);
	
	printSymbol(triangleButton);
	if(symbolClicked(triangleButton))
		printString("Draw Triangle",colors[6],20,50,800);
	printSymbol(squareButton);
	if(symbolClicked(squareButton))
		printString("Draw Square",colors[6],20,50,800);
	printSymbol(lineButton);
	if(symbolClicked(lineButton))
		printString("Draw Line",colors[6],20,50,800);
	printSymbol(boldLineButton);
	if(symbolClicked(boldLineButton))
		printString("Draw Bold Line",colors[6],20,50,800);
	printSymbol(ballButton);
	if(symbolClicked(ballButton))
		printString("Draw Ball",colors[6],20,50,800);
	printSymbol(ballPartButton);
	if(symbolClicked(ballPartButton))
		printString("Draw Ball Part",colors[6],20,50,800);
	printSymbol(circleButton);
	if(symbolClicked(circleButton))
		printString("Draw Circle",colors[6],20,50,800);
	printSymbol(tetrahedronButton);
	if(symbolClicked(tetrahedronButton))
		printString("Draw Tetrahedron",colors[6],20,50,800);
	printSymbol(cylinderButton);
	if(symbolClicked(cylinderButton))
		printString("Draw Cylinder",colors[6],20,50,800);
	printSymbol(coneButton);
	if(symbolClicked(coneButton))
		printString("Draw Cone",colors[6],20,50,800);
	printSymbol(attractButton);
	if(symbolClicked(attractButton))
		printString("Attracted By Grid",colors[6],20,50,800);
	printSymbol(undoButton);
	if(symbolClicked(undoButton))
		printString("Undo",colors[6],20,50,800);
	printSymbol(saveButton);
	if(symbolClicked(saveButton))
		printString("Save",colors[6],20,50,800);
	printSymbol(loadButton);
	if(symbolClicked(loadButton))
		printString("Load",colors[6],20,50,800);
	printSymbol(clearButton);
	if(symbolClicked(clearButton))
		printString("Clear",colors[6],20,50,800);
	printSymbol(showGridButton);
	if(symbolClicked(showGridButton))
		printString("Show/Hide Grid",colors[6],20,50,800);
	printSymbol(showAxesButton);
	if(symbolClicked(showAxesButton))
		printString("Show/Hide Axes",colors[6],20,50,800);
	printSymbol(showCursorButton);
	if(symbolClicked(showCursorButton))
		printString("Show/Hide Cursor",colors[6],20,50,800);
	goBackTo3D();
	
	locateMouse(&cursorx,&cursory,&cursorz,-100,-100,100,100,fixCursor);
	
	if(attractedByGrid)
	{
		cursorx = (int)(cursorx>0? cursorx+0.5: cursorx-0.5);
		cursory = (int)(cursory>0? cursory+0.5: cursory-0.5);
		cursorz = (int)(cursorz>0? cursorz+0.5: cursorz-0.5);
	}
	
	updateCurObject();
	
	drawPartialObject(curObject,curIndex);
	
	if(showCursor) drawCursor(curObject.color);
	
	glFlush();
}

void reshape(int w, int h)
{
	reshapeWithoutDeform(w,h);
}

void handleKeyEvent(unsigned char keyCode, int x, int y)
{
	switch(keyCode)
	{
	case 'z':
		fixCursor = 0;
		break;
	case 'x':
		fixCursor = 1;
		break;
	case 's':
		saveFile("data.txt",objects);
		break;
	case 'o':
		openFile("data.txt",objects);
		break;
	}
	glutPostRedisplay();
}

void handleKeyUpEvent(unsigned char keyCode, int x, int y)
{
	fixCursor = 2;
	glutPostRedisplay();
}

void handleMouseEvent(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_UP)
		{
			bool buttonClicked = false;
			for(int i = 0; i<colorTable.size(); i++)
				if(symbolClicked(colorTable[i]))
				{
					curObject.color[0] = colors[i][0];
					curObject.color[1] = colors[i][1];
					curObject.color[2] = colors[i][2];
					buttonClicked = true;
				}
			if(symbolClicked(triangleButton))
			{
				drawType = Triangle;
				buttonClicked = true;
			}
			if(symbolClicked(squareButton))
			{
				drawType = Square;
				buttonClicked = true;
			}
			if(symbolClicked(lineButton))
			{
				drawType = Line;
				buttonClicked = true;
			}
			if(symbolClicked(boldLineButton))
			{
				drawType = BoldLine;
				buttonClicked = true;
			}
			if(symbolClicked(ballButton))
			{
				drawType = Ball;
				buttonClicked = true;
			}
			if(symbolClicked(ballPartButton))
			{
				drawType = BallPart;
				buttonClicked = true;
			}
			if(symbolClicked(circleButton))
			{
				drawType = Circle;
				buttonClicked = true;
			}
			if(symbolClicked(tetrahedronButton))
			{
				drawType = Tetrahedron;
				buttonClicked = true;
			}
			if(symbolClicked(cylinderButton))
			{
				drawType = Cylinder;
				buttonClicked = true;
			}
			if(symbolClicked(coneButton))
			{
				drawType = Cone;
				buttonClicked = true;
			}
			if(symbolClicked(attractButton))
			{
				attractedByGrid = !attractedByGrid;
				buttonClicked = true;
			}
			if(symbolClicked(undoButton))
			{
				if(!objects.empty())
					objects.pop_back();
				buttonClicked = true;
			}
			if(symbolClicked(saveButton))
			{
				saveObjects("data.dat",objects);
				buttonClicked = true;
			}
			if(symbolClicked(loadButton))
			{
				loadObjects("data.dat",objects);
				buttonClicked = true;
			}
			if(symbolClicked(clearButton))
			{
				objects.clear();
				buttonClicked = true;
			}
			if(symbolClicked(showGridButton))
			{
				showGrid = !showGrid;
				buttonClicked = true;
			}
			if(symbolClicked(showAxesButton))
			{
				showAxes = !showAxes;
				buttonClicked = true;
			}
			if(symbolClicked(showCursorButton))
			{
				showCursor = !showCursor;
				buttonClicked = true;
			}
			if(buttonClicked)
			{
				curIndex = 0;
				curObject.type = drawType;
			}
			
			if(!draged && !buttonClicked)
			{
				if(curIndex>=requiredNumberOfSteps(drawType)-1)
				{
						objects.push_back(curObject);
						curObject = newObject(drawType,curObject.color[0],
											  curObject.color[1],curObject.color[2],
											  curObject.specular,curObject.shrininess);
						curIndex = 0;
				}
				else
					curIndex++;
			}
			else
			{
				draged = false;
			}
		}
	}
	else if(button==GLUT_RIGHT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			curIndex = 0;
		}
	}
	glutPostRedisplay();
}


void handleMouseMoveEvent(int x, int y)
{
	drag(x,y);
	draged = true;
	trackMouse(x,y);
	glutPostRedisplay();
}

void handlePassiveMouseMoveEvent(int x, int y)
{
	trackMouse(x,y);
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	init("Drawer",&argc,argv);
		
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(handleKeyEvent);
	glutKeyboardUpFunc(handleKeyUpEvent);
	glutMouseFunc(handleMouseEvent);
	glutMotionFunc(handleMouseMoveEvent);
	glutPassiveMotionFunc(handlePassiveMouseMoveEvent);
	
	glutMainLoop();
}
