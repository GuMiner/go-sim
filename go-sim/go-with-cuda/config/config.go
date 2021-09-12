package config

import (
	"sim/common/config"
	"sim/common/io"

	"encoding/json"
	"fmt"

	"github.com/go-gl/mathgl/mgl32"
)

type DefaultCamera struct {
	Position config.SerializableVec3
	Forwards config.SerializableVec3
	Up       config.SerializableVec3
}

type Camera struct {
	MotionSpeed   float32
	RotationSpeed float32
	Default       DefaultCamera
}

type Configuration struct {
	Camera Camera
}

var Config Configuration

func (c *Camera) GetDefaultPos() mgl32.Vec3 {
	return mgl32.Vec3{
		c.Default.Position.X,
		c.Default.Position.Y,
		c.Default.Position.Z}
}

func (c *Camera) GetDefaultForwards() mgl32.Vec3 {
	return mgl32.Vec3{
		c.Default.Forwards.X,
		c.Default.Forwards.Y,
		c.Default.Forwards.Z}
}

func (c *Camera) GetDefaultUp() mgl32.Vec3 {
	return mgl32.Vec3{
		c.Default.Up.X,
		c.Default.Up.Y,
		c.Default.Up.Z}
}

func Load(configFileName string, commonConfigFileName string) {
	config.Load(commonConfigFileName)
	bytes := io.ReadFileAsBytes(configFileName)

	if err := json.Unmarshal(bytes, &Config); err != nil {
		panic(err)
	}

	fmt.Printf("Read in config '%v'.\n", configFileName)
	fmt.Printf("  Config data: %v\n\n", Config)
}
