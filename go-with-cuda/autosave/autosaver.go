package autosave

import (
	"bytes"
	"encoding/gob"
	"fmt"
	"io/ioutil"
	"os"
)

const autosaveRootFolder = "./data/autosave/"
const autosaveExtension = ".gob"

func getautosaveFilename(autosaveName string) string {
	return autosaveRootFolder + autosaveName + autosaveExtension
}

func Load(autosaveName string, outputautosavedData bool, autosaveItem interface{}) (autosaveMiss bool) {
	autosaveFileAsBytes, err := ioutil.ReadFile(getautosaveFilename(autosaveName))
	autosaveMiss = true
	if err == nil {
		// Decode from autosave, ignore failures
		err = gob.NewDecoder(bytes.NewBuffer(autosaveFileAsBytes)).Decode(autosaveItem)
		if err == nil {
			autosaveMiss = false
			if outputautosavedData {
				fmt.Printf("Loaded autosave '%v' (%v bytes) with: %+v\n", autosaveName, len(autosaveFileAsBytes), autosaveItem)
			} else {
				fmt.Printf("Loaded autosave '%v' (%v bytes).\n", autosaveName, len(autosaveFileAsBytes))
			}
		} else {
			fmt.Printf("Could not decode autosave '%v': %v.\n", autosaveName, err)
		}
	} else {
		fmt.Printf("Could not read autosave '%v': %v.\n", autosaveName, err)
	}

	return autosaveMiss
}

func Save(autosaveName string, autosaveItem interface{}) bool {
	byteBuffer := new(bytes.Buffer)
	err := gob.NewEncoder(byteBuffer).Encode(autosaveItem)
	if err != nil {
		fmt.Printf("Unable to encode the '%v' autosave: %v\n", autosaveName, err)
		return false
	} else {
		err = ioutil.WriteFile(getautosaveFilename(autosaveName), byteBuffer.Bytes(), os.ModePerm)
		if err != nil {
			fmt.Printf("Unable to autosave the '%v' encoded data: %v\n", autosaveName, err)
			return false
		}
	}

	return true
}
