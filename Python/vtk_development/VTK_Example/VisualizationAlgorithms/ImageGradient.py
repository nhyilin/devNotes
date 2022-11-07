#!/usr/bin/env python


import vtk


def main():
    fileName = get_program_parameters()
    colors = vtk.vtkNamedColors()

    # Read the CT data of the human head.
    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)
    reader.Update()

    cast = vtk.vtkImageCast()
    cast.SetInputConnection(reader.GetOutputPort())
    cast.SetOutputScalarTypeToFloat()

    # Magnify the image.
    magnify = vtk.vtkImageMagnify()
    magnify.SetInputConnection(cast.GetOutputPort())
    magnify.SetMagnificationFactors(2, 2, 1)
    magnify.InterpolateOn()

    # Smooth the data.
    # Remove high frequency artifacts due to linear interpolation.
    smooth = vtk.vtkImageGaussianSmooth()
    smooth.SetInputConnection(magnify.GetOutputPort())
    smooth.SetDimensionality(2)
    smooth.SetStandardDeviations(1.5, 1.5, 0.0)
    smooth.SetRadiusFactors(2.01, 2.01, 0.0)

    # Compute the 2D gradient.
    gradient = vtk.vtkImageGradient()
    gradient.SetInputConnection(smooth.GetOutputPort())
    gradient.SetDimensionality(2)

    # Convert the data to polar coordinates.
    # The image magnitude is mapped into saturation value,
    # whilst the gradient direction is mapped into hue value.
    polar = vtk.vtkImageEuclideanToPolar()
    polar.SetInputConnection(gradient.GetOutputPort())
    polar.SetThetaMaximum(255.0)

    # Add a third component to the data.
    # This is needed since the gradient filter only generates two components,
    #  and we need three components to represent color.
    pad = vtk.vtkImageConstantPad()
    pad.SetInputConnection(polar.GetOutputPort())
    pad.SetOutputNumberOfScalarComponents(3)
    pad.SetConstant(200.0)

    # At this point we have Hue, Value, Saturation.
    # Permute components so saturation will be constant.
    # Re-arrange components into HSV order.
    permute = vtk.vtkImageExtractComponents()
    permute.SetInputConnection(pad.GetOutputPort())
    permute.SetComponents(0, 2, 1)

    # Convert back into RGB values.
    rgb = vtk.vtkImageHSVToRGB()
    rgb.SetInputConnection(permute.GetOutputPort())
    rgb.SetMaximum(255.0)

    # Set up a viewer for the image.
    # Note that vtkImageViewer and vtkImageViewer2 are convenience wrappers around
    # vtkActor2D, vtkImageMapper, vtkRenderer, and vtkRenderWindow.
    # So all that needs to be supplied is the interactor.
    viewer = vtk.vtkImageViewer()
    viewer.SetInputConnection(rgb.GetOutputPort())
    viewer.SetZSlice(22)
    viewer.SetColorWindow(255.0)
    viewer.SetColorLevel(127.0)
    viewer.GetRenderWindow().SetSize(512, 512)
    viewer.GetRenderer().SetBackground(colors.GetColor3d("Silver"))

    # Create the RenderWindowInteractor.
    iren = vtk.vtkRenderWindowInteractor()
    viewer.SetupInteractor(iren)
    viewer.Render()

    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'ImageGradient.'
    epilogue = '''
Visualization of gradient information.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('fileName',
                        help='The file FullHead.mhd. Note: file FullHead.raw.gz must also be present in the same folder.')
    args = parser.parse_args()
    return args.fileName


if __name__ == '__main__':
    main()
