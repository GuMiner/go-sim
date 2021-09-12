package basics

import (
	"sim/common/opengl"

	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/mathgl/mgl32"
)

type ShadowLitRendererProgram struct {
	shaderProgram uint32
	projectionLoc int32
	cameraLoc     int32
	modelLoc      int32

	partialShadowMatrixLoc int32
	shadingColorLoc        int32
	shadowTextureLoc       int32

	shadowTextureId uint32
}

func NewShadowLitRendererProgram() *ShadowLitRendererProgram {
	var program ShadowLitRendererProgram
	program.shaderProgram = opengl.CreateProgram("./common/opengl/basics/shadowLitShader")

	program.projectionLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("projection\x00"))
	program.cameraLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("camera\x00"))
	program.modelLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("model\x00"))

	program.partialShadowMatrixLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("partialShadowMatrix\x00"))

	program.shadingColorLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("shadingColor\x00"))
	program.shadowTextureLoc = gl.GetUniformLocation(program.shaderProgram, gl.Str("shadowTexture\x00"))

	return &program
}

func (r *ShadowLitRendererProgram) UseProgram(shadingColor mgl32.Vec3) {
	gl.UseProgram(r.shaderProgram)

	gl.ActiveTexture(gl.TEXTURE0)
	gl.BindTexture(gl.TEXTURE_2D, r.shadowTextureId)
	gl.Uniform1i(r.shadowTextureLoc, 0)

	gl.Uniform3f(r.shadingColorLoc, shadingColor[0], shadingColor[1], shadingColor[2])
}

func (r *ShadowLitRendererProgram) UpdateShadowTexture(partialShadowMatrix *mgl32.Mat4, shadowTextureId uint32) {
	gl.UseProgram(r.shaderProgram)
	gl.UniformMatrix4fv(r.partialShadowMatrixLoc, 1, false, &partialShadowMatrix[0])

	r.shadowTextureId = shadowTextureId
}

func (s *ShadowLitRendererProgram) SetModelMatrix(model *mgl32.Mat4) {
	gl.UseProgram(s.shaderProgram)
	gl.UniformMatrix4fv(s.modelLoc, 1, false, &model[0])
}

func (r *ShadowLitRendererProgram) Delete() {
	gl.DeleteProgram(r.shaderProgram)
}

// Implement Renderer
func (r *ShadowLitRendererProgram) UpdateProjection(projection *mgl32.Mat4) {
	gl.UseProgram(r.shaderProgram)
	gl.UniformMatrix4fv(r.projectionLoc, 1, false, &projection[0])
}

func (r *ShadowLitRendererProgram) UpdateCamera(camera *mgl32.Mat4) {
	gl.UseProgram(r.shaderProgram)
	gl.UniformMatrix4fv(r.cameraLoc, 1, false, &camera[0])
}
