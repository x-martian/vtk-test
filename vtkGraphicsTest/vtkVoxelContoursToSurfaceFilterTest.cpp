#include "vtkVoxelContoursToSurfaceFilterTest.h"
#include "vtkGraphicsTestPipelineTemplate.h"

#include "vtkPolyDataAlgorithm.h"
#include "vtkPolyDataMapper.h"
#include "vtkSmartPointer.h"
#include "vtkAppendPolyData.h"
#include "vtkCellArray.h"
#include "vtkMath.h"
#include "vtkVoxelContoursToSurfaceFilter.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"

#include "../lemon.h"


void CreateCircle( const double& z, const double& radius, const int& resolution, vtkPolyData* polyData )
{
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

	points->SetNumberOfPoints( resolution );
	cells->Allocate( 1, resolution );
	cells->InsertNextCell( resolution );

	for( int i = 0 ; i < resolution; ++i )
	{
		double theta = vtkMath::RadiansFromDegrees(360.*i/double(resolution));
		double x = radius*cos(theta);
		double y = radius*sin(theta);
		points->SetPoint( i, x, y, z );
		cells->InsertCellPoint( i );
	}

	polyData->Initialize();
	polyData->SetPolys( cells );
	polyData->SetPoints( points );
}


vtkVoxelContoursToSurfaceFilterDriver::vtkVoxelContoursToSurfaceFilterDriver(void)
{
}

vtkVoxelContoursToSurfaceFilterDriver::~vtkVoxelContoursToSurfaceFilterDriver(void)
{
}

vtkVoxelContoursToSurfaceFilterDriver::FilterType* vtkVoxelContoursToSurfaceFilterDriver::GetFilter()
{
	int numDivisions = 20;
	int resolution = 100;
	double lastz = 0.;
	double z = 0.;
	double radius = 0.;
	double sphereRadius = 1.;
	double zmin = -0.9*sphereRadius;
	double zmax = 0.9*sphereRadius;

	// Append all the discs into one polydata
	//
	vtkAppendPolyData* appendFilter = vtkAppendPolyData::New();

	for( int i = 0; i <= numDivisions; ++i )
	{
		lastz = z;
		double u = i / double(numDivisions);
		z = ( 1. - u )*zmin + u*zmax;
		radius = sqrt( sphereRadius*sphereRadius - z*z );
		vtkPolyData* circle = vtkPolyData::New();
		CreateCircle( z, radius, resolution, circle );
		appendFilter->AddInput( circle );
	}

	double deltaz = z - lastz;

	appendFilter->Update();

	// Convert to ijk coordinates for the contour to surface filter
	//
	double bounds[6];
	vtkPolyData* contours = appendFilter->GetOutput();
	contours->GetBounds( bounds );
	double origin[3]  = { bounds[0], bounds[2], bounds[4] };
	double spacing[3] = { (bounds[1] - bounds[0]) / 128,
		(bounds[3] - bounds[2]) / 128,
		deltaz };

	vtkPolyData* poly = vtkPolyData::New();
	vtkPoints* points = vtkPoints::New();
	vtkPoints* contourPoints = contours->GetPoints();
	int numPoints = contourPoints->GetNumberOfPoints();
	points->SetNumberOfPoints( numPoints );
	for( int i = 0; i < numPoints; ++i )
	{
		double pt[3];
		contourPoints->GetPoint( i, pt );
		pt[0] = static_cast<int>( (pt[0] - origin[0]) / spacing[0] + 0.5 );
		pt[1] = static_cast<int>( (pt[1] - origin[1]) / spacing[1] + 0.5 );
		pt[2] = static_cast<int>( (pt[2] - origin[2]) / spacing[2] + 0.5 );
		points->SetPoint( i, pt );
	}
	poly->SetPolys( contours->GetPolys() );
	poly->SetPoints( points );

	// Create the contour to surface filter
	//
	vtkVoxelContoursToSurfaceFilter* contoursToSurface = vtkVoxelContoursToSurfaceFilter::New();
	contoursToSurface->SetInput( poly );
	contoursToSurface->SetSpacing( spacing[0], spacing[1], spacing[2] );
	contoursToSurface->Update();

	// Rescale the output back into world coordinates and center it
	//
	double scaleCenter[3];
	contoursToSurface->GetOutput()->GetCenter( scaleCenter );
	double scaleBounds[6];
	contoursToSurface->GetOutput()->GetBounds( scaleBounds );
	double center[3];
	contours->GetCenter( center );

	vtkTransformPolyDataFilter* transformFilter = vtkTransformPolyDataFilter::New();
	transformFilter->SetInputConnection( contoursToSurface->GetOutputPort() );
	vtkTransform* transform = vtkTransform::New();
	transformFilter->SetTransform( transform );
	transform->Translate( -scaleCenter[0], -scaleCenter[1], -scaleCenter[2] );
	transform->Scale( 
		(bounds[1] - bounds[0])/(scaleBounds[1] - scaleBounds[0]),
		(bounds[3] - bounds[2])/(scaleBounds[3] - scaleBounds[2]),
		(bounds[5] - bounds[4])/(scaleBounds[5] - scaleBounds[4]) );
	transform->Translate( center[0], center[1], center[2] );

	return transformFilter;
}


vtkVoxelContoursToSurfaceFilterDriver::PropType* vtkVoxelContoursToSurfaceFilterDriver::GetProp()
{
	PropType* actor = PropType::New();
	actor->GetProperty()->SetColor(0,0,1); // sphere color blue
	actor->GetProperty()->SetRepresentationToWireframe();
	actor->GetProperty()->ShadingOff();

	return actor;
}

bool vtkVoxelContourToSurfaceFilterTest(bool on)
{
	lemon::test<> t;

	vtkVoxelContoursToSurfaceFilterDriver driver; 
	vtkGraphicsTestPipelineTemplate<vtkVoxelContoursToSurfaceFilterDriver> pipeline(driver);

	pipeline.StartInteraction();

	return t.done();
}