/*
 * Test coordinate conversions.
 */

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkCoordinate.h>


// Absolute tolerance for double-value equality
static const double ABSOLUTE_TOLERANCE = 1e-6;



class Converter
{
public:
    // Return a title like "World->View"
    virtual const char* title() = 0;

    // Convert input in vector[] and return in same.
    virtual void convert( double vector[2] ) = 0;
};




using namespace std;


vtkRenderer* renderer;
vtkRenderWindow* renderWindow;
vtkCamera* camera;
vtkCoordinate* coordinate;


static int numFailedAssertions = 0;


bool isEqual( double vector1[2], double vector2[2] )
{
  return ( fabs( vector1[0] - vector2[0] ) < ABSOLUTE_TOLERANCE &&
           fabs( vector1[1] - vector2[1] ) < ABSOLUTE_TOLERANCE );
}

ostream& operator<<( ostream& out, double vector[2] )
{
  out << "[" << vector[0] << "," << vector[1] << "]";
  return out;
}

static void assertEquals( Converter* converter1,
			  Converter* converter2,
			  double inPoint[2] )
{
  double outPoint1[2] = { inPoint[0], inPoint[1] };
  converter1->convert( outPoint1 );

  double outPoint2[2] = { inPoint[0], inPoint[1] };
  converter2->convert( outPoint2 );

  if ( isEqual( outPoint1, outPoint2 ) )
    return;

  ++numFailedAssertions;
  cerr << inPoint << " maps to " << outPoint1 << " using " << converter1->title()
       << ", but to " << outPoint2 << " using " << converter2->title() << "\n";
}



// Set up world->display transform so that it maps
// an image of specified width and height to a render
// window of the same size.
// This should result in a world->display transformation
// that is a translation by half a pixel since world coordinate
// origin is in pixel centre while display is at pixel edge.
//
static void setupCamera( int width, int height )
{
    renderWindow->SetSize( width, height );

    double xFocal = ( width - 1 ) / 2.0;
    double yFocal = ( height - 1 ) / 2.0;

    camera->SetViewUp( 0, 1, 0 );
    camera->SetFocalPoint( xFocal, yFocal, 0 );
    camera->SetPosition( xFocal, yFocal, 2 );
    camera->SetClippingRange( 1, 3 );

    camera->ParallelProjectionOn();
//    camera->SetParallelScale( height / 2.0 );
	camera->SetParallelScale(11);

	double planes[24];
	camera->GetFrustumPlanes(1.0, planes);
}



class WorldToViewR1 : public Converter
{
    const char* title() { return "vtkRenderer::WorldToView(vector)"; }

    void convert( double vector[2] )
    {
	double z = 0;
	renderer->WorldToView( vector[0], vector[1], z );
    }
};

class WorldToViewR2 : public Converter
{
    const char* title() { return "vtkRenderer::WorldToView()"; }

    void convert( double vector[2] )
    {
        renderer->SetWorldPoint( vector[0], vector[1], 0, 1 );
        
        double result[3];
        renderer->WorldToView();
        renderer->GetViewPoint( result );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class WorldToDisplayR1 : public Converter
{
    const char* title() { return "vtkRenderer::WorldToDisplay()"; }

    void convert( double vector[2] )
    {
        renderer->SetWorldPoint( vector[0], vector[1], 0, 1 );
        
        double result[3];
        renderer->WorldToDisplay();
        renderer->GetDisplayPoint( result );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class WorldToDisplayC1 : public Converter
{
    const char* title() { return "vtkCoordinate::WorldToDisplay"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToWorld();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedDoubleDisplayValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class ViewToWorldR1 : public Converter
{
    const char* title() { return "vtkRenderer::ViewToWorld(vector)"; }

    void convert( double vector[2] )
    {
	double z = 0;
	renderer->ViewToWorld( vector[0], vector[1], z );
    }
};

class ViewToWorldR2 : public Converter
{
    const char* title() { return "vtkRenderer::ViewToWorld()"; }

    void convert( double vector[2] )
    {
        renderer->SetViewPoint( vector[0], vector[1], 0 );
        
        double result[4];
        renderer->ViewToWorld();
        renderer->GetWorldPoint( result );

        vector[0] = result[0] / result[3];
        vector[1] = result[1] / result[3];
    }
};

class ViewToWorldC1 : public Converter
{
    const char* title() { return "vtkCoordinate::ViewToWorld"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToView();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedWorldValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class ViewToDisplayR1 : public Converter
{
    const char* title() { return "vtkRenderer::ViewToDisplay()"; }

    void convert( double vector[2] )
    {
        renderer->SetViewPoint( vector[0], vector[1], 0 );
        
        double result[3];
        renderer->ViewToDisplay();
        renderer->GetDisplayPoint( result );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class ViewToDisplayC1 : public Converter
{
    const char* title() { return "vtkCoordinate::ViewToDisplay"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToView();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedDoubleDisplayValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class NormalizedViewportToViewportR1 : public Converter
{
    const char* title() { return "vtkRenderer::NormalizedViewportToViewport()"; }

    void convert( double vector[2] )
    {
        renderer->NormalizedViewportToViewport( vector[0], vector[1] );
    }
};

class NormalizedViewportToViewportC1 : public Converter
{
    const char* title() { return "vtkCoordinate::NormalizedViewportToViewport"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToNormalizedViewport();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedDoubleViewportValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class NormalizedDisplayToViewportR1 : public Converter
{
    const char* title() { return "vtkRenderer::NormalizedDisplayToViewport()"; }

    void convert( double vector[2] )
    {
        renderer->NormalizedDisplayToViewport( vector[0], vector[1] );
    }
};

class NormalizedDisplayToViewportC1 : public Converter
{
    const char* title() { return "vtkCoordinate::NormalizedDisplayToViewport"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToNormalizedDisplay();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedDoubleViewportValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class NormalizedDisplayToDisplayR1 : public Converter
{
    const char* title() { return "vtkRenderer::NormalizedDisplayToDisplay()"; }

    void convert( double vector[2] )
    {
        renderer->NormalizedDisplayToDisplay( vector[0], vector[1] );
    }
};

class NormalizedDisplayToDisplayC1 : public Converter
{
    const char* title() { return "vtkCoordinate::NormalizedDisplayToDisplay"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToNormalizedDisplay();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedDoubleDisplayValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};

class DisplayToWorldR1 : public Converter
{
    const char* title() { return "vtkRenderer::DisplayToWorld()"; }

    void convert( double vector[2] )
    {
        renderer->SetDisplayPoint( vector[0], vector[1], 0 );
        
        double result[4];
        renderer->DisplayToWorld();
        renderer->GetWorldPoint( result );

        vector[0] = result[0] / result[3];
        vector[1] = result[1] / result[3];
    }
};

class DisplayToWorldC1 : public Converter
{
    const char* title() { return "vtkCoordinate::DisplayToWorld"; }

    void convert( double vector[2] )
    {
        coordinate->SetCoordinateSystemToDisplay();
        coordinate->SetValue( vector[0], vector[1] );

        double* result = coordinate->GetComputedWorldValue( renderer );

        vector[0] = result[0];
        vector[1] = result[1];
    }
};


// Test all equivalent transformations with the specified point
void testEquivalentTransforms( double x, double y )
{
    double point[] = { x, y };
    assertEquals( new WorldToViewR1(), new WorldToViewR2(), point );
    assertEquals( new WorldToDisplayR1(), new WorldToDisplayC1(), point );
    assertEquals( new ViewToWorldR1(), new ViewToWorldR2(), point );
    assertEquals( new ViewToWorldR1(), new ViewToWorldC1(), point );
    assertEquals( new ViewToDisplayR1(), new ViewToDisplayC1(), point );
    assertEquals( new NormalizedViewportToViewportR1(), new NormalizedViewportToViewportC1(), point );
    assertEquals( new NormalizedDisplayToViewportR1(), new NormalizedDisplayToViewportC1(), point );
    assertEquals( new NormalizedDisplayToDisplayR1(), new NormalizedDisplayToDisplayC1(), point );
    assertEquals( new DisplayToWorldR1(), new DisplayToWorldC1(), point );
}


void testEquivalentTransforms( std::string testName )
{
    cerr << testName << "\n";
    testEquivalentTransforms( 0, 0 );
    testEquivalentTransforms( 1, 0 );
    testEquivalentTransforms( 0, 1 );
}


int coordinateConversion( int ac, _TCHAR* av[] )
{
    renderWindow = vtkRenderWindow::New();

    renderer = vtkRenderer::New();
    renderer->SetViewport(0.47, 0.0, 0.9, 1.0);
    renderWindow->AddRenderer( renderer );

    camera = renderer->GetActiveCamera();

    coordinate = vtkCoordinate::New();

    setupCamera( 5, 5 );
    testEquivalentTransforms( "Parallel projection, 5x5 window" );

    setupCamera( 5, 15 );
    testEquivalentTransforms( "Parallel projection, 5x15 window" );

    setupCamera( 15, 15 );
    testEquivalentTransforms( "Parallel projection, 15x5 window" );

    return numFailedAssertions;
}
