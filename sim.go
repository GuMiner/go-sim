package main

import (
	"sim/common/color"
	commonConfig "sim/common/config"
	"sim/common/opengl"
	"sim/common/opengl/basics"
	"sim/common/opengl/geometry"
	"sim/common/opengl/renderer"
	"sim/common/opengl/shadow"
	"sim/common/opengl/text"

	"sim/diagnostics/fractal"

	"sim/config"
	"sim/input"

	"fmt"
	"runtime"
	"time"

	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/glfw/v3.2/glfw"
	"github.com/go-gl/mathgl/mgl32"
)

// void maxmul(float *A, float* B, float *C, int size);
// #cgo LDFLAGS: -Llib -lmaxmul
import "C"

func Maxmul(a []C.float, b []C.float, c []C.float, size int) {
	C.maxmul(&a[0], &b[0], &c[0], C.int(size))
}

func init() {
	runtime.LockOSThread()
}

func setInputCallbacks(window *glfw.Window) {
	window.SetFramebufferSizeCallback(opengl.ResizeViewport)
	window.SetCursorPosCallback(input.HandleMouseMove)
	window.SetMouseButtonCallback(input.HandleMouseButton)
	window.SetKeyCallback(input.HandleKeyInput)
}

func main() {
	config.Load("./data/config/sim.json", "./data/config/common.json")
	opengl.InitGlfw()
	defer glfw.Terminate()

	opengl.InitViewport()
	window, err := glfw.CreateWindow(
		int(opengl.GetWindowSize().X()),
		int(opengl.GetWindowSize().Y()),
		commonConfig.Config.Window.Title, nil, nil)
	if err != nil {
		panic(err)
	}

	window.MakeContextCurrent()

	setInputCallbacks(window)
	opengl.ConfigureOpenGl()

	input.LoadKeyAssignments()
	defer input.SaveKeyAssignments()

	// Test CUDA
	a := []C.float{-1, 2, 4, 0, 5, 3, 6, 2, 1}
	b := []C.float{3, 0, 2, 3, 4, 5, 4, 7, 2}
	var c []C.float = make([]C.float, 9)
	Maxmul(a, b, c, 3)
	fmt.Println(c)

	shadowBuffer := shadow.NewShadowBuffer()
	defer shadowBuffer.Delete()

	color.InitializeColorGradient(
		commonConfig.Config.ColorGradient.Steps,
		commonConfig.Config.ColorGradient.Saturation,
		commonConfig.Config.ColorGradient.Luminosity)

	textRenderer := text.NewTextRenderer(commonConfig.Config.Text.FontFile)
	defer textRenderer.Delete()

	// Really bad flat renderer with parameters that belong on models
	flatRenderer := basics.NewFlatRendererProgram()
	defer flatRenderer.Delete()

	flatRenderer.SetColor(mgl32.Vec3{0.0, 1.0, 0.0})

	modelMatrix := mgl32.Scale3D(10.0, 10.0, 10.0)
	flatRenderer.SetModel(&modelMatrix)

	test_cube := geometry.NewCube()
	defer test_cube.Delete()

	fpsSentence := text.NewSentence(textRenderer, mgl32.Vec3{0, 0, 0}, mgl32.Vec3{0, 1, 0})
	fpsCounter := NewFpsCounter(fpsSentence, 1.0, mgl32.Vec3{-0.4, 0.4, 0.01}) // -0.42, 0.33

	var renderers []renderer.Renderer
	renderers = append(renderers, textRenderer, flatRenderer)

	camera := NewCamera(
		config.Config.Camera.GetDefaultPos(),
		config.Config.Camera.GetDefaultForwards(),
		config.Config.Camera.GetDefaultUp())
	defer camera.AutosavePosition()

	// Diagnostics
	fractal := fractal.NewFullScreenFractal()
	defer fractal.Delete()

	// Update
	startTime := time.Now()
	frameTime := float32(0.1)
	lastElapsed := float32(0.0)
	elapsed := lastElapsed

	update := func() {
		lastElapsed = elapsed
		elapsed = float32(time.Since(startTime)) / float32(time.Second)
		frameTime = elapsed - lastElapsed

		fpsCounter.Update(frameTime)
		fractal.Update(elapsed)
		//vehicle.CheckColorOverlayToggle()
		//checkTextToggles()

		camera.Update(frameTime)

		//UpdateSimulation(frameTime, elapsed)
		glfw.PollEvents()
	}

	render := func() {
		gl.Clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
		//RenderSimulation(voxelArrayObjectRenderer)

		fractal.Render()
		fpsCounter.Render(camera)

		flatRenderer.Render(test_cube.Buffers)
	}

	for !window.ShouldClose() {
		update()

		// Render to shadow buffer, for general rendering and with shadows
		projection, cameraMatrix := shadowBuffer.PrepareCamera()

		renderer.UpdateProjections(renderers, &projection)
		renderer.UpdateCameras(renderers, &cameraMatrix)

		//shadowBuffer.RenderToBuffer(func() {
		//	gl.Clear(gl.DEPTH_BUFFER_BIT)
		//	gl.CullFace(gl.FRONT)

		//	renderer.EnableDepthModeOnly()
		//	RenderSimulation(voxelArrayObjectRenderer)
		//	renderer.DisableDepthModeOnly()

		//	gl.CullFace(gl.BACK)
		//})

		// Prepare for normal rendering...
		// shadowBiasMatrix := mgl32.Mat4FromRows(
		// 	mgl32.Vec4{0.5, 0, 0, 0.5},
		// 	mgl32.Vec4{0, 0.5, 0, 0.5},
		// 	mgl32.Vec4{0, 0, 0.5, 0.5},
		// 	mgl32.Vec4{0, 0, 0, 1.0})

		// partialShadowMatrix := shadowBiasMatrix.Mul4(projection.Mul4(cameraMatrix))
		// voxelArrayObjectRenderer.UpdateShadows(&partialShadowMatrix, shadowBuffer.GetTextureId())

		// Render the full display.
		opengl.ResetViewport()

		projection = mgl32.Perspective(
			mgl32.DegToRad(commonConfig.Config.Perspective.FovY),
			opengl.GetWindowSize().X()/opengl.GetWindowSize().Y(),
			commonConfig.Config.Perspective.Near,
			commonConfig.Config.Perspective.Far)
		renderer.UpdateProjections(renderers, &projection)

		cameraMatrix = camera.GetLookAtMatrix()
		renderer.UpdateCameras(renderers, &cameraMatrix)

		render()
		window.SwapBuffers()
	}
}
