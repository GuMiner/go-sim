package main

import (
	"sim/common/config"
	"sim/common/opengl"

	"fmt"
	"runtime"
	"time"

	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/glfw/v3.2/glfw"
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

func main() {
	config.Load("./data/config/common.json")
	opengl.InitGlfw()
	defer glfw.Terminate()

	opengl.InitViewport()
	window, err := glfw.CreateWindow(
		int(opengl.GetWindowSize().X()),
		int(opengl.GetWindowSize().Y()),
		config.Config.Window.Title, nil, nil)
	if err != nil {
		panic(err)
	}

	window.MakeContextCurrent()

	// setInputCallbacks(window)
	opengl.ConfigureOpenGl()

	a := []C.float{-1, 2, 4, 0, 5, 3, 6, 2, 1}
	b := []C.float{3, 0, 2, 3, 4, 5, 4, 7, 2}
	var c []C.float = make([]C.float, 9)
	Maxmul(a, b, c, 3)
	fmt.Println(c)

	// Update
	startTime := time.Now()
	//frameTime := float32(0.1)
	lastElapsed := float32(0.0)
	elapsed := lastElapsed

	update := func() {
		lastElapsed = elapsed
		elapsed = float32(time.Since(startTime)) / float32(time.Second)
		//frameTime = elapsed - lastElapsed

		//fpsCounter.Update(frameTime)
		//opengl.CheckWireframeToggle()
		//diagnostics.CheckDebugToggle()
		//vehicle.CheckColorOverlayToggle()
		//checkTextToggles()

		//camera.Update(frameTime)

		//UpdateSimulation(frameTime, elapsed)
		glfw.PollEvents()
	}

	render := func() {
		gl.Clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
		//RenderSimulation(voxelArrayObjectRenderer)

		//if isFpsEnabled {
		//	fpsCounter.Render(camera)
		//}

		//if isHelpTextEnabled {
		//	helpText.Render(camera)
		//}
	}

	for !window.ShouldClose() {
		update()

		// Render to shadow buffer
		//projection, cameraMatrix := shadowBuffer.PrepareCamera()

		//renderer.UpdateProjections(renderers, &projection)
		//renderer.UpdateCameras(renderers, &cameraMatrix)

		//shadowBuffer.RenderToBuffer(func() {
		//	gl.Clear(gl.DEPTH_BUFFER_BIT)
		//	gl.CullFace(gl.FRONT)

		//	renderer.EnableDepthModeOnly()
		//	RenderSimulation(voxelArrayObjectRenderer)
		//	renderer.DisableDepthModeOnly()

		//	gl.CullFace(gl.BACK)
		//})

		// Prepare for normal rendering...
		//shadowBiasMatrix := mgl32.Mat4FromRows(
		//	mgl32.Vec4{0.5, 0, 0, 0.5},
		//	mgl32.Vec4{0, 0.5, 0, 0.5},
		//	mgl32.Vec4{0, 0, 0.5, 0.5},
		//	mgl32.Vec4{0, 0, 0, 1.0})

		//partialShadowMatrix := shadowBiasMatrix.Mul4(projection.Mul4(cameraMatrix))
		//voxelArrayObjectRenderer.UpdateShadows(&partialShadowMatrix, shadowBuffer.GetTextureId())

		// Render the full display.
		opengl.ResetViewport()

		//projection = mgl32.Perspective(
		//	mgl32.DegToRad(commonConfig.Config.Perspective.FovY),
		//	commonOpenGl.GetWindowSize().X()/commonOpenGl.GetWindowSize().Y(),
		//	commonConfig.Config.Perspective.Near,
		//	commonConfig.Config.Perspective.Far)
		//renderer.UpdateProjections(renderers, &projection)

		//cameraMatrix = camera.GetLookAtMatrix()
		//renderer.UpdateCameras(renderers, &cameraMatrix)

		render()
		window.SwapBuffers()
	}
}
