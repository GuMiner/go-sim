package fractal

// Defines a full-screen quad with the gradient
import (
	"sim/common/color"
	"sim/common/config"

	"github.com/go-gl/gl/v4.5-core/gl"
)

type RainbowTexture struct {
	openGlTextureSlot        uint32
	fractalGradientTextureID uint32
}

func NewRainbowTexture() *RainbowTexture {
	var rainbow RainbowTexture

	rainbow.openGlTextureSlot = gl.TEXTURE0
	gl.ActiveTexture(rainbow.openGlTextureSlot)
	gl.GenTextures(1, &rainbow.fractalGradientTextureID)

	gl.BindTexture(gl.TEXTURE_1D, rainbow.fractalGradientTextureID)
	gl.TexStorage1D(gl.TEXTURE_1D, 1, gl.RGB32F, int32(config.Config.ColorGradient.Steps))
	gl.TexSubImage1D(gl.TEXTURE_1D, 0, 0, int32(config.Config.ColorGradient.Steps), gl.RGB, gl.FLOAT, gl.Ptr(color.GetGradient()))

	return &rainbow
}

func (rainbow *RainbowTexture) Delete() {
	gl.DeleteTextures(1, &rainbow.fractalGradientTextureID)
}
