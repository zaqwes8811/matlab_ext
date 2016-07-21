/*
 Copyright (c) 2013 Randy Gaul http://RandyGaul.net

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 */

#include "Precompiled.h"

#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#define ESC_KEY 27

using namespace boost;
using namespace std;

//glm::vec

struct Mark
{
	Mark( vec2 pos )
	{
		this->pos = pos;
	}

	void draw();

	vec2 pos;
};

void Mark::draw()
{
	int size = 2;

	glColor3f(1, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(pos.x, pos.y - size);
	glVertex2f(pos.x, pos.y + size);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(pos.x - size, pos.y);
	glVertex2f(pos.x + size, pos.y);
	glEnd();
}

//========================================================

void RenderString( int32 x, int32 y, const char *s )
{
	glColor3f(0.5f, 0.5f, 0.9f);
	glRasterPos2i(x, y);
	uint32 l = (uint32) std::strlen(s);
	for( uint32 i = 0; i < l; ++i )
		glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *(s + i));
}

void RenderString( int32 x, int32 y, string s )
{
	cout << s << endl;
	RenderString(x, y, s.c_str());
}

//=========================================================

class SceneNoGravity: public BaseScene
{
public:
	SceneNoGravity( f32 dt, uint32 iterations ) :
			BaseScene(dt, iterations)
	{
	}
	virtual void Step( void )
	{
	}
};

static BaseScene* g_scene = new SceneNoGravity(1.0f / 60.0f, 10);
Clock g_Clock;
bool g_frameStepping = false;
bool g_canStep = false;

static vector<string> messages_;

void mouse_func( int button, int state, int x, int y )
{
	stringstream ss;
	ss << "(" << x << ", " << y << ")";
	messages_.push_back(ss.str());

	x /= 10.0f;
	y /= 10.0f;

	if( state == GLUT_DOWN )
		switch (button) {
		case GLUT_LEFT_BUTTON: {
//			PolygonShape poly;  // !!!!!!!!!!!!!
//			uint32 count = (uint32) Random(3, MaxPolyVertexCount);
//			vec2 *vertices = new vec2[count];
//			float e = Random(5, 10);
//			for( uint32 i = 0; i < count; ++i )
//				vertices[i].Set(Random(-e, e), Random(-e, e));
//			poly.Set(vertices, count);
//			Body *b = g_scene->Add(&poly, x, y);
//			b->SetOrient(Random(-PI, PI));
//			b->restitution = 0.2f;
//			b->dynamicFriction = 0.2f;
//			b->staticFriction = 0.4f;
//			delete[] vertices;
		}
			break;
		case GLUT_RIGHT_BUTTON: {
//			Circle c(Random(1.0f, 3.0f));
//			Body *b = g_scene->Add(&c, x, y);
		}
			break;
		}
}

void keyboard_func( unsigned char key, int x, int y )
{
	switch (key) {
	case ESC_KEY:
		exit(0);
		break;
	case 's': {
		//Circle c( 25.0f );
		//scene.Add( &c, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
		//OBB obb;
		//real e = Random( 10.0f, 35.0f );
		//obb.extents.Set( e, e );
		//Body *b = scene.Add( &obb, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
		//b->SetOrient( PI / 4.0f );
		//b->restitution = 0.2f;
		//b->dynamicFriction = 0.2f;
		//b->staticFriction = 0.4f;
	}
		break;
	case 'd': {
		//Circle c( 25.0f );
		//scene.Add( &c, 420, 50 );
	}
		break;
	case 'f':
		g_frameStepping = g_frameStepping ? false : true;
		break;
	case ' ':
		g_canStep = true;
		break;
	}
}

void phy_loop_func( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderString(1, 2, "Left click to spawn a polygon");
	RenderString(1, 4, "Right click to spawn a circle");

	for( int i = 0; i < messages_.size(); ++i ){
		RenderString(20, 20, messages_[i]);
	}
	messages_.clear();

	static double s_accumulator = 0;

	// Different time mechanisms for Linux and Windows
#ifdef WIN32
	s_accumulator += g_Clock.Elapsed( );
#else
	s_accumulator += g_Clock.Elapsed()
	        / static_cast<double>(chrono::duration_cast<clock_freq>(
	                chrono::seconds(1)).count());
#endif

	g_Clock.Start();

	s_accumulator = clamp(0.0f, 0.1f, s_accumulator);
	while( s_accumulator >= dt ){
		if( !g_frameStepping )
			g_scene->Step();
		else{
			if( g_canStep ){
				g_scene->Step();
				g_canStep = false;
			}
		}
		s_accumulator -= dt;
	}

	g_Clock.Stop();

	g_scene->Render();

	// my code
	Mark m(vec2(10, 10));
	m.draw();

	glutSwapBuffers();
}

//========================================================

int main( int argc, char** argv )
{
	// fixme: где переход к единицам измерения СИ

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("PhyEngine");
	glutDisplayFunc(phy_loop_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse_func);
	glutIdleFunc(phy_loop_func);

	glMatrixMode( GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 80, 60, 0);
	glMatrixMode( GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	srand(1);
	glutMainLoop();

	return 0;
}
