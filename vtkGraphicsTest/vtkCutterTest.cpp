#include "vtkCutterTest.h"

#include "vtkSphereSource.h"
#include "vtkCutter.h"
#include "vtkPolyDataMapper.h"
#include "vtkMatrix4x4.h"
#include "vtkPlane.h"
#include "vtkAppendPolyData.h"
#include "vtkActor2D.h"
#include "vtkProperty2D.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkAppendPolyData.h"
#include "vtkCellArray.h"
//#include "vtkVoxelContoursToSurfaceFilter.h"
#include "vtkRuledSurfaceFilter.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"
#include "vtkCommand.h"
#include "vtkInteractorStyle.h"


#include "vtkGraphicsTestPipelineTemplate.h"
#include "../lemon.h"

vtkCutterDriver::vtkCutterDriver(void)
{
}

vtkCutterDriver::~vtkCutterDriver(void)
{
}

vtkCutterDriver::FilterType* vtkCutterDriver::GetFilter()
{/*
	vtkAppendPolyData* append = vtkAppendPolyData::New();

	// create sphere geometry
	vtkSphereSource *sphere = vtkSphereSource::New();
	sphere->SetCenter(0.0, 0.0, 0.0);
	sphere->SetRadius(1.0);
	sphere->SetThetaResolution(180);
	sphere->SetPhiResolution(180);

	vtkPlane* plane = vtkPlane::New();
	plane->SetOrigin(0.0, 0.0, 0.0);
	plane->SetNormal(0.0, 0.0, 1.0);
	
	vtkCutter* cutter = vtkCutter::New();
	cutter->SetCutFunction(plane);
	cutter->SetInput(sphere->GetOutput());
	cutter->Update();

	append->AddInput(cutter->GetOutput());
	
	plane = vtkPlane::New();
	plane->SetOrigin(0.2, 0.2, 0.0);
	plane->SetNormal(0.0, 1.41, 1.41);

	cutter = vtkCutter::New();
	cutter->SetCutFunction(plane);
	cutter->SetInput(sphere->GetOutput());
	cutter->Update();

	append->AddInput(cutter->GetOutput());
	
	return append;
*/
	vtkAppendPolyData* append = vtkAppendPolyData::New();
		vtkPoints* points = vtkPoints::New();
		vtkCellArray* cells = vtkCellArray::New();

		// create a concave polygon (equilateral with a cutout at the bottom)
		points->SetNumberOfPoints(4);
		//points->SetPoint(0, -100.0, 0.0, 0.0);
		//points->SetPoint(1, 0.0, 173.2, 0.0);
		//points->SetPoint(2, 100.0, 0.0, 0.0);
		//points->SetPoint(3, 0.0, 100.0, 0.0);
		points->SetPoint(0, 10.0, 10.0, 0.0);
		points->SetPoint(1, 110.0, 183.2, 0.0);
		points->SetPoint(2, 210.0, 10.0, 0.0);
		points->SetPoint(3, 110.0, 110.0, 0.0);

		cells->Allocate(1, 5);
		cells->InsertNextCell(5);
		cells->InsertCellPoint(0);
		cells->InsertCellPoint(1);
		cells->InsertCellPoint(2);
		cells->InsertCellPoint(3);
		cells->InsertCellPoint(0);

		vtkPolyData* poly = vtkPolyData::New();
		poly->Initialize();
		poly->SetGlobalWarningDisplay(1);
		poly->SetPoints(points);
		poly->SetPolys(cells);

    points->Delete();
    cells->Delete();

    //return poly;
    append->AddInput(poly);
    poly->Delete();

	return append;
}
/*
vtkCutterDriver::FilterType* vtkCutterDriver::GetFilter()
{
	vtkAppendPolyData* append = vtkAppendPolyData::New();

	qzRTStructureSet* rtStructureSet = qzRTStructureSet::Load("D:/DCMSamples/DICOM-RT/RS.1.2.246.352.71.4.754569130.1201772.20100222111847.dcm");

	qzStructureSetIE& ie = rtStructureSet->GetStructureSetIE();

	// create a vector of surfaces
	// first find the max value of the roi numbers
	int max = 0;
	int n = ie.structureSetModule.GetStructureSetROICount();
	for (int i=0; i<n; ++i) {
		qzStructureSetROI& roi = ie.structureSetModule.GetStructureSetROI(i);
		ROINUMBER number = roi.ROINumber();
		if (number>max) max = number;
	}

	std::vector<vtkPolyData*> roiStructures;
	roiStructures.resize(max+1, 0);	// the contour number starts with one

	// turn contour set into surfaces
	// the algorithm, vtkContours2PolyDataFilter, used here requires the
	// coordinates of the points in the contours to be at integer values.
	// So the contours are first transformed into the image coordinate
	// (col, row, frame), do the conversion, then transformed back to the
	// world (patient) coordinate.

	// TODO get the following from the image data, this is needed for the contours-to-surface algorithm
	//double origin[3] = {-250.0, -250.0, -95.0};
	//double dxdydz[3] = {0.976562, 0.976562, 2.5};
	double origin[3] = {0.0, 0.0, 0.0};
	double dxdydz[3] = {1.0, 1.0, 1.0};

	n = ie.roiContourModule.GetROIContourCount();
//	for (int i=4; i<5; ++i) {
		// the output
		vtkPolyData* surface = vtkPolyData::New();

//		vtkAppendPolyData* append = vtkAppendPolyData::New();
		//append->SetOutput(surface);

		// get the contours and convert into vtkPolyData
		qzROIContour& roi = ie.roiContourModule.GetROIContour(4);
		int m = roi.RTContourCount();
		for (int j=0; j<m; ++j) {
			qzRTContour& rtContour = roi.GetRTContour(j);
			vtkPolyData* contour = vtkPolyData::New();
			vtkPoints* points = vtkPoints::New();
			vtkCellArray* cells = vtkCellArray::New();
			qzRTContour::Point* rtPoints;
			unsigned int size = rtContour.GetData(rtPoints);
			if (size == 0)
				continue;
			points->SetNumberOfPoints(size);
			cells->Allocate(1, size);
			cells->InsertNextCell(size);
			for (int k=0; k<size; ++k)
			{
				// convert point into image coordinate
				double x = (rtPoints[k].x-origin[0])/dxdydz[0];
				double y = (rtPoints[k].y-origin[1])/dxdydz[1];
				double z = (rtPoints[k].z-origin[2])/dxdydz[2];
				points->SetPoint(k, x, y, z);
				cells->InsertCellPoint(4);
			}
			contour->Initialize();
			contour->SetPolys(cells);
			contour->SetPoints(points);
			append->AddInput(contour);
		}

		// convert the vtkPolyData collection into a surface
		//vtkVoxelContoursToSurfaceFilter* c2s = vtkVoxelContoursToSurfaceFilter::New();
		vtkRuledSurfaceFilter* c2s = vtkRuledSurfaceFilter::New();
		//c2s->SetOutput(surface);
		//c2s->SetInputConnection(append->GetOutputPort());
		//c2s->SetRuledModeToResample();
		//c2s->CloseSurfaceOn();
		//c2s->SetSpacing(dxdydz);
		//c2s->Update();
		//surface = c2s->GetOutput();
		roiStructures.at(roi.ReferencedROI().ROINumber()) = surface;

//	return cutter;
	return append;
}
*/
vtkCutterDriver::PropType* vtkCutterDriver::GetProp()
{
	PropType* actor = PropType::New();
	actor->GetProperty()->SetColor(0, 1.0, 0.0); // sphere color blue
//	actor->GetProperty()->SetRepresentationToWireframe();
//	actor->GetProperty()->ShadingOff();
//	actor->GetProperty()->SetEdgeVisibility(0);
	actor->GetProperty()->SetLineWidth(1.6);
//	actor->GetProperty()->SetAmbientColor(1.0, 1.0, 1.0);
//	actor->GetProperty()->SetDiffuseColor(1.0, 1.0, 1.0);
	actor->GetProperty()->SetOpacity(1.0);

	return actor;
}


bool vtkCutterTest(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkCutterDriver driver;
    vtkGraphicsTestPipelineTemplate<vtkCutterDriver> pipeline(driver);
    pipeline.StartInteraction();

    return t.done();
}