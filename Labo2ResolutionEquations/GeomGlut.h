// Fichier Geoglut.h

#ifndef GeomGlut_H
#define GeomGlut_H

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>                // Librairie GLUT
#endif

using namespace std;

const GLfloat ARROW = 0.2;
const GLfloat DEFAUL_SIZE_POINT = 2.0;

typedef struct coord2D
{
    double x;
    double y;
};

typedef struct coord2D_UInt
{
    unsigned int x;
    unsigned int y;
};

class GeomGlut
{
  public:

    //--- Constructor ---
    GeomGlut( void );
    //--- Destructor ---
    ~GeomGlut( void );


    //--- Public members ---
    // <none>

    //--- Public methods ---
    void initGraphicsWin( unsigned int pixelWinX, double xMin, double xMax, double yMin, double yMax );

    void drawAxes();
    void plot( GLfloat x, GLfloat y );
    void plot( GLfloat x, GLfloat y, GLfloat sizePoint );

    void segment( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );

    double xMin( void ) { return( minWin.x); }
    double yMin( void ) { return( minWin.y); }
    double xMax( void ) { return( maxWin.x); }
    double yMax( void ) { return( maxWin.y); }

    void setWinPixels( unsigned int x, unsigned int y ) { winPixels.x = x; winPixels.y = y; }

    unsigned int xWinFunc( void ) { return( winFuncPixels.x ); }
    unsigned int yWinFunc( void ) { return( winFuncPixels.y ); }

  private:
    //--- Private members ---
    coord2D minWin;
    coord2D maxWin;
    coord2D_UInt winFuncPixels;
    coord2D_UInt winPixels;

    //--- Private methods ---
    coord2D getMinWin( void ) { return( minWin ); }
    coord2D getMaxWin( void ) { return( maxWin ); }
    coord2D_UInt getFuncWinPixel( void ) { return( winFuncPixels ); }

  protected:
    // <none>

};

// openGL functions
void Display();
void Reshape(int, int);

#endif // GeomGlut_H
