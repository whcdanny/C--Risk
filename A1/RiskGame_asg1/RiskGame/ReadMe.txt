COMP 345 Assignment1 part4 save/load
Name: Haochen wang

In RiskGame file

	There are 7 .cpp c++ files, and 6 .h header files.

	The MapDriver.cpp is main.

	The continent.cpp, TerritoryNode.cpp and World.cpp for the map.
	
	The IniParser.cpp: INI-like file analysis program

	The IniWriter.cpp and MapIni.cpp are save and load the map.
	
In resources file

	There is a world.map.

	When the program done, there will be create a newWorld.map, which is delete the Quebec from North American.


Part 4 save/load
	In this part, map focue on these rules
		1. the map represents a connected graph
		2. continents are connected subgraphs
		3. each country belongs to on and only one continent
	In the first, load world.map, then check this .map by the rule. If false, print error. If true, then continue. I delete Quebec from North America, because i need to check my save part is also focused on the rule.When i save the newWorld.map to rewrite by rule and check it whether is true map.
	Finally, i have checked both of save and load part which are focused on the rule. 