package basics

import (
	"sim/common/opengl"

	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/mathgl/mgl32"
)

type FlatRendererProgram struct {
	shaderProgram uint32
	projectionLoc int32
	cameraLoc     int32
	modelLoc      int32
	colorLoc      int32
}

func NewFlatRendererProgram() *FlatRendererProgram {
	var program FlatRendererProgram
	program.shaderProgram = opengl.CreateProgram("./common/opengl/basics/flatShader")

	program.projectionLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("projection\x00"))
	program.cameraLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("camera\x00"))
	program.modelLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("model\x00"))
	program.colorLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("colorOverride\x00"))

	return &program
}

func (r *FlatRendererProgram) UseProgram() {
	gl.UseProgram(r.shaderProgram)
}

func (r *FlatRendererProgram) SetColor(color mgl32.Vec3) {
	gl.UseProgram(r.shaderProgram)
	gl.Uniform3f(r.colorLoc, color.X(), color.Y(), color.Z())
}

func (s *FlatRendererProgram) SetModelMatrix(model *mgl32.Mat4) {
	gl.UseProgram(s.shaderProgram)
	gl.UniformMatrix4fv(s.modelLoc, 1, false, &model[0])
}

func (r *FlatRendererProgram) Delete() {
	gl.DeleteProgram(r.shaderProgram)
}

// Implement Renderer
func (r *FlatRendererProgram) UpdateProjection(projection *mgl32.Mat4) {
	gl.UseProgram(r.shaderProgram)
	gl.UniformMatrix4fv(r.projectionLoc, 1, false, &projection[0])
}

func (r *FlatRendererProgram) UpdateCamera(camera *mgl32.Mat4) {
	gl.UseProgram(r.shaderProgram)
	gl.UniformMatrix4fv(r.cameraLoc, 1, false, &camera[0])
}
