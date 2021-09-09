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

type Cube struct {
	Buffers *PositionBuffer
}

func NewCube() *Cube {
	cube := Cube{NewPositionBuffer()}
	cube.Buffers.Reload(cubeVertices)
	return &cube
}

func (c *Cube) Delete() {
	c.Buffers.Delete()
}
