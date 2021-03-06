package geometry

import (
	"github.com/go-gl/mathgl/mgl32"
)

// Directly from https://github.com/go-gl/example/blob/master/gl41core-cube/cube.go
var cubeVertices = []mgl32.Vec3{
	// Bottom
	{-0.5, -0.5, -0.5},
	{0.5, -0.5, -0.5},
	{-0.5, -0.5, 0.5},
	{0.5, -0.5, -0.5},
	{0.5, -0.5, 0.5},
	{-0.5, -0.5, 0.5},

	// Top
	{-0.5, 0.5, -0.5},
	{-0.5, 0.5, 0.5},
	{0.5, 0.5, -0.5},
	{0.5, 0.5, -0.5},
	{-0.5, 0.5, 0.5},
	{0.5, 0.5, 0.5},

	// Front
	{-0.5, -0.5, 0.5},
	{0.5, -0.5, 0.5},
	{-0.5, 0.5, 0.5},
	{0.5, -0.5, 0.5},
	{0.5, 0.5, 0.5},
	{-0.5, 0.5, 0.5},

	// Back
	{-0.5, -0.5, -0.5},
	{-0.5, 0.5, -0.5},
	{0.5, -0.5, -0.5},
	{0.5, -0.5, -0.5},
	{-0.5, 0.5, -0.5},
	{0.5, 0.5, -0.5},

	// Left
	{-0.5, -0.5, 0.5},
	{-0.5, 0.5, -0.5},
	{-0.5, -0.5, -0.5},
	{-0.5, -0.5, 0.5},
	{-0.5, 0.5, 0.5},
	{-0.5, 0.5, -0.5},

	// Right
	{0.5, -0.5, 0.5},
	{0.5, -0.5, -0.5},
	{0.5, 0.5, -0.5},
	{0.5, -0.5, 0.5},
	{0.5, 0.5, -0.5},
	{0.5, 0.5, 0.5}}

var cubeNormals = []mgl32.Vec3{
	// Bottom
	{0, -1, 0},
	{0, -1, 0},
	{0, -1, 0},
	{0, -1, 0},
	{0, -1, 0},
	{0, -1, 0},

	// Top
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0},

	// Front
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},

	// Back
	{0, 0, -1},
	{0, 0, -1},
	{0, 0, -1},
	{0, 0, -1},
	{0, 0, -1},
	{0, 0, -1},

	// Left
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},

	// Right
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0}}

var cubeColors = []mgl32.Vec3{
	// Bottom
	{0.5, 1.0, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 1.0, 0.5},

	// Top
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},

	// Front
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},

	// Back
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},

	// Left
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},

	// Right
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0},
	{0.5, 0.5, 1.0}}

type Cube struct {
	Buffers  *PositionBuffer
	Position mgl32.Mat4
	Color    mgl32.Vec3
}

func NewCube() *Cube {
	cube := Cube{NewPositionBuffer(), mgl32.Ident4(), mgl32.Vec3{0.0, 1.0, 0.0}}
	cube.Buffers.Reload(cubeVertices)
	return &cube
}

func (c *Cube) Delete() {
	c.Buffers.Delete()
}

type ShadedCube struct {
	Buffers  *PositionNormalColorBuffer
	Position mgl32.Mat4
}

func NewShadedCube() *ShadedCube {
	cube := ShadedCube{NewPositionNormalColorBuffer(), mgl32.Ident4()}
	cube.Buffers.Reload(cubeVertices, cubeNormals, cubeColors)
	return &cube
}

func (c *ShadedCube) Delete() {
	c.Buffers.Delete()
}
