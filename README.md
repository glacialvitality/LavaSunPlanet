This works with Super Mario Galaxy 2 (SB4E01). Not sure about other regions. Nintendo Switch port is not supported nor planned.

### Setup
You might need to add the following entries to your `ProductMapObjDataTable.bcsv`:
*LavaDomedPlanet, LavaSunPlanet* (ModelName, ClassName)
*LavaRotatePlanet, LavaSunPlanet* (ModelName, ClassName)

### Object Arguments
LavaDomedPlanet: None

LavaRotatePlanet:
This planet is a *MapPart*. Do not attempt to use it in the *General* tab (in Whitehole) or it will not rotate.
All MapParts settings are similar to class RotateMoveObj, unless specified otherwise.

Recomended values are set to 0 unless specified otherwise:
RotateSpeed = 12
RotateAxis = 1
FarClip = -1
