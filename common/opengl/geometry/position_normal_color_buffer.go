package geometry

import (
	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/mathgl/mgl32"
)

type PositionNormalColorBuffer struct {
	vao         uint32
	positionVbo uint32
	normalVbo   uint32
	colorVbo    uint32

	vertexCount int32
}

func NewPositionNormalColorBuffer() *PositionNormalColorBuffer {
	var buffer PositionNormalColorBuffer

	gl.GenVertexArrays(1, &buffer.vao)
	gl.BindVertexArray(buffer.vao)

	gl.EnableVertexAttribArray(0)
	gl.GenBuffers(1, &buffer.positionVbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, buffer.positionVbo)
	gl.VertexAttribPointer(0, 3, gl.FLOAT, false, 0, nil)

	gl.EnableVertexAttribArray(1)
	gl.GenBuffers(1, &buffer.normalVbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, buffer.normalVbo)
	gl.VertexAttribPointer(1, 3, gl.FLOAT, false, 0, nil)

	gl.EnableVertexAttribArray(2)
	gl.GenBuffers(1, &buffer.colorVbo)
	gl.BindBuffer(gl.ARRAY_BUFFER, buffer.colorVbo)
	gl.VertexAttribPointer(2, 3, gl.FLOAT, false, 0, nil)

	return &buffer
}

func (s *PositionNormalColorBuffer) Reload(positionData []mgl32.Vec3, normalData []mgl32.Vec3, colorData []mgl32.Vec3) {
	s.vertexCount = int32(len(positionData))

	gl.BindBuffer(gl.ARRAY_BUFFER, s.positionVbo)
	gl.BufferData(gl.ARRAY_BUFFER, len(positionData)*3*4, gl.Ptr(positionData), gl.STATIC_DRAW)

	gl.BindBuffer(gl.ARRAY_BUFFER, s.normalVbo)
	gl.BufferData(gl.ARRAY_BUFFER, len(normalData)*3*4, gl.Ptr(normalData), gl.STATIC_DRAW)

	gl.BindBuffer(gl.ARRAY_BUFFER, s.colorVbo)
	gl.BufferData(gl.ARRAY_BUFFER, len(colorData)*3*4, gl.Ptr(colorData), gl.STATIC_DRAW)

}

func (s *PositionNormalColorBuffer) Render() {
	gl.BindVertexArray(s.vao)
	gl.DrawArrays(gl.TRIANGLES, 0, s.vertexCount)
}

func (s *PositionNormalColorBuffer) Delete() {
	gl.DeleteBuffers(1, &s.colorVbo)
	gl.DeleteBuffers(1, &s.normalVbo)
	gl.DeleteBuffers(1, &s.positionVbo)
	gl.DeleteVertexArrays(1, &s.vao)
}
