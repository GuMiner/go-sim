package shadow

import (
	"sim/common/opengl"

	"github.com/go-gl/mathgl/mgl32"

	"github.com/go-gl/gl/v4.5-core/gl"
)

type DepthRenderer struct {
	program uint32

	projectionLoc int32
	cameraLoc     int32
	modelLoc      int32
}

func NewDepthRenderer() *DepthRenderer {
	var depthRenderer DepthRenderer
	depthRenderer.program = opengl.CreateProgram("./common/opengl/shadow/depthRenderer")
	depthRenderer.projectionLoc = gl.GetUniformLocation(depthRenderer.program, gl.Str("projection\x00"))
	depthRenderer.cameraLoc = gl.GetUniformLocation(depthRenderer.program, gl.Str("camera\x00"))
	depthRenderer.modelLoc = gl.GetUniformLocation(depthRenderer.program, gl.Str("model\x00"))

	return &depthRenderer
}

func (r *DepthRenderer) Delete() {
	gl.DeleteProgram(r.program)
}

func (r *DepthRenderer) UseProgram() {
	gl.UseProgram(r.program)
}

func (r *DepthRenderer) SetModelMatrix(model *mgl32.Mat4) {
	gl.UniformMatrix4fv(r.modelLoc, 1, false, &model[0])
}

// Implement Renderer
func (renderer *DepthRenderer) UpdateProjection(projection *mgl32.Mat4) {
	gl.UseProgram(renderer.program)
	gl.UniformMatrix4fv(renderer.projectionLoc, 1, false, &projection[0])
}

func (renderer *DepthRenderer) UpdateCamera(camera *mgl32.Mat4) {
	gl.UseProgram(renderer.program)
	gl.UniformMatrix4fv(renderer.cameraLoc, 1, false, &camera[0])
}
