package geometry

import (
	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/mathgl/mgl32"
)

type PositionBuffer struct {
	vao         uint32
	positionVbo uint32
	vertexCount int32
}

func NewPositionBuffer() *PositionBuffer {
	var positionBuffer PositionBuffer

	gl.GenVertexArrays(1, &positionBuffer.vao)
	gl.BindVertexArray(positionBuffer.vao)

	gl.EnableVertexAttribArray(0)
	gl.GenBuffers(1, &positionBuffer.positionVbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, positionBuffer.positionVbo)
	gl.VertexAttribPointer(0, 3, gl.FLOAT, false, 0, nil)

	return &positionBuffer
}

func (s *PositionBuffer) Reload(positionData []mgl32.Vec3) {
	gl.BindBuffer(gl.ARRAY_BUFFER, s.positionVbo)

	// 4-byte floats in a 3-element vector
	s.vertexCount = int32(len(positionData))
	gl.BufferData(gl.ARRAY_BUFFER, len(positionData)*3*4, gl.Ptr(positionData), gl.STATIC_DRAW)

}

func (s *PositionBuffer) Render() {
	gl.BindVertexArray(s.vao)
	gl.DrawArrays(gl.TRIANGLES, 0, s.vertexCount)
}

func (s *PositionBuffer) Delete() {
	gl.DeleteBuffers(1, &s.positionVbo)
	gl.DeleteVertexArrays(1, &s.vao)
}
