
SetCustomCursor( true )

LoadResource("Resources.xml")

LoadEffects("My.xml"); 

UploadResourceGroup("TestGroup")

UploadResourceGroup("MyGroup")

GUI:LoadLayers("Layers.xml")

Screen:pushLayer(GUI:getLayer("TestLayer"))



