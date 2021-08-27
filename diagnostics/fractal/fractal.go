package fractal

import (
	"sim/common/config"
	"sim/common/opengl"
	"sim/input"

	"github.com/go-gl/gl/v4.5-core/gl"
	"github.com/go-gl/mathgl/mgl32"
)

type FullScreenFractal struct {
	program uint32

	mouseUniformPos int32
	timeUniformPos  int32

	texture *RainbowTexture
	quad    *FullScreenQuad
}

func (f *FullScreenFractal) Delete() {
	f.texture.Delete()
	f.quad.Delete()

	gl.DeleteProgram(f.program)
}

func NewFullScreenFractal() *FullScreenFractal {
	var fractal FullScreenFractal

	fractal.program = opengl.CreateProgram("./diagnostics/fractal/juliaFractal")
	fractal.mouseUniformPos = gl.GetUniformLocation(fractal.program, gl.Str("c\x00"))
	fractal.timeUniformPos = gl.GetUniformLocation(fractal.program, gl.Str("time\x00"))

	fractal.quad = NewFullScreenQuad()
	fractal.texture = NewRainbowTexture()

	// Enable our program and do first-time uniform setup
	gl.UseProgram(fractal.program)

	gl.ActiveTexture(fractal.texture.openGlTextureSlot)
	gl.BindTexture(gl.TEXTURE_1D, fractal.texture.fractalGradientTextureID)

	fractalGradientLoc := gl.GetUniformLocation(fractal.program, gl.Str("fractalGradient\x00"))
	gl.Uniform1i(fractalGradientLoc, int32(fractal.texture.openGlTextureSlot)-gl.TEXTURE0) // Yes it is zero.

	maxIterationsLoc := gl.GetUniformLocation(fractal.program, gl.Str("maxIterations\x00"))
	gl.Uniform1i(maxIterationsLoc, int32(config.Config.ColorGradient.Steps))

	return &fractal
}

func (f *FullScreenFractal) Update(elapsedTime float32) {
	gl.UseProgram(f.program)
	gl.Uniform1f(int32(f.timeUniformPos), elapsedTime)

	normalizedPos := mgl32.Vec2{-0.5, -0.5}.Add(mgl32.Vec2{input.MousePos.X() / opengl.GetWindowSize().X(), input.MousePos.Y() / opengl.GetWindowSize().Y()})
	gl.Uniform2f(f.mouseUniformPos, normalizedPos.X(), normalizedPos.Y())
}

func (f *FullScreenFractal) Render() {
	gl.UseProgram(f.program)
	f.quad.Render()
}
