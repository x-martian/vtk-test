#pragma once

#include "vtkAlgorithm.h"

/// Provide entry point for testing vtkAlgorithm class as well as utilites
/// for creating mock object of vtkAlgorithm type
class vtkAlgorithmTest
{
public:
    vtkAlgorithmTest(void);
    ~vtkAlgorithmTest(void);

    /// Run the test
    /// \param on run tests if true, skip otherwise
    static bool Run(bool on);

    /// Creates a mock algorithm to track virtual method calls
    /// \param name instance name of the object
    /// \param inPort number of input ports
    /// \param outPort number of output ports
    static vtkAlgorithm* MockAlgorithm(const char* name, unsigned inPort, unsigned outPort);
};

