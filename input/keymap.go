package input

import (
	"sim/autosave"

	"github.com/go-gl/glfw/v3.2/glfw"
)

// Defines the key assignments of each key
type KeyAssignment int

// Ordering is important! Reordering these changes their numerical values
const (
	LookLeft KeyAssignment = iota
	LookRight
	LookUp
	LookDown

	RotateClockwise
	RotateCounterClockwise

	MoveForwards
	MoveBackwards
	MoveLeft
	MoveRight
	MoveUp
	MoveDown

	ToggleDebug
	ToggleWireframe
	ToggleColorOverlay
	ToggleFpsText
	ToggleHelpText
)

const keyMapAutosaveName = "keymap"

var keyMap map[KeyAssignment]glfw.Key = make(map[KeyAssignment]glfw.Key)

func createDefaultKeyMap() {
	keyMap[LookLeft] = glfw.KeyLeft
	keyMap[LookRight] = glfw.KeyRight
	keyMap[LookUp] = glfw.KeyUp
	keyMap[LookDown] = glfw.KeyDown

	keyMap[RotateClockwise] = glfw.KeyE
	keyMap[RotateCounterClockwise] = glfw.KeyD

	keyMap[MoveForwards] = glfw.KeyA
	keyMap[MoveBackwards] = glfw.KeyZ
	keyMap[MoveLeft] = glfw.KeyQ
	keyMap[MoveRight] = glfw.KeyW
	keyMap[MoveUp] = glfw.KeyS
	keyMap[MoveDown] = glfw.KeyX

	keyMap[ToggleDebug] = glfw.KeyG
	keyMap[ToggleWireframe] = glfw.KeyL
	keyMap[ToggleColorOverlay] = glfw.KeyC
	keyMap[ToggleFpsText] = glfw.KeyF
	keyMap[ToggleHelpText] = glfw.KeyH
}

func LoadKeyAssignments() {
	autosaveMiss := autosave.Load(keyMapAutosaveName, false, &keyMap)
	if autosaveMiss {
		createDefaultKeyMap()
	}
}

func SaveKeyAssignments() {
	autosave.Save(keyMapAutosaveName, keyMap)
}

func IsPressed(key KeyAssignment) bool {
	return pressedKeys[keyMap[key]]
}

func IsTyped(key KeyAssignment) bool {
	isTyped := typedKeys[keyMap[key]]
	if isTyped {
		typedKeys[keyMap[key]] = false
	}

	return isTyped
}
