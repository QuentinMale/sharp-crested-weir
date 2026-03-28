from paraview.simple import *
import os
import glob

# Ensure output directory exists
os.makedirs("output_png", exist_ok=True)

# Load the state, but point readers to a directory that may contain newer files
LoadState(
    "water.pvsm",
    LoadStateDataFileOptions="Search files under specified directory",
    DataDirectory="output"
)

# This is the time-series reader
reader = FindSource("weir-000000.xdmf2*")
if reader is None:
    raise RuntimeError("Could not find the series reader 'weir-000000.xdmf2*'")

files = sorted(glob.glob("output/weir-*.xdmf2"))
print("Found", len(files), "files")

if not files:
    raise RuntimeError("No files found matching output/weir-*.xdmf2")

reader.FileNames = files
reader.UpdatePipeline()

# Make sure pipeline is updated
scene = GetAnimationScene()
scene.UpdateAnimationUsingDataTimeSteps()

# Use exact data timesteps
scene.PlayMode = 'Snap To TimeSteps'

# Safety check
timesteps = scene.TimeKeeper.TimestepValues
if not timesteps:
    raise RuntimeError("No timesteps found. Check that the state and file series were loaded correctly.")

scene.StartTime = timesteps[0]
scene.EndTime = timesteps[-1]

# Get render view
renderView = GetActiveViewOrCreate('RenderView')

# Set camera
renderView.CameraParallelProjection = 1
renderView.CameraFocalPoint = [-0.16315765609880706, 0.0400853491078169, -0.10910628377061124]
renderView.CameraParallelScale = 0.7138239443342305
renderView.CameraPosition = [1.6720810425356325, 0.5563786743852568, 1.8838628117959928]
renderView.CameraViewAngle = 30
renderView.CameraViewUp = [-0.1366608110229403, 0.9822338392959264, -0.1286099050327629]

print("CameraParallelProjection:", renderView.CameraParallelProjection)
print("CameraPosition:", renderView.CameraPosition)
print("CameraFocalPoint:", renderView.CameraFocalPoint)
print("CameraViewUp:", renderView.CameraViewUp)
print("CameraParallelScale:", renderView.CameraParallelScale)
print("ViewTime:", renderView.ViewTime)

Render()

# Use the view size stored in the state
resolution = renderView.ViewSize

print("Using resolution:", resolution)
print("Reader now has", len(reader.FileNames), "files")
print("First file:", reader.FileNames[0])
print("Last file:", reader.FileNames[-1])
print("Using timesteps:", timesteps[0], "to", timesteps[-1], f"({len(timesteps)} steps)")

# Save animation
SaveAnimation(
    "output_png/frame.png",
    renderView,
    ImageResolution=resolution
)

