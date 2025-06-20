Anleitung 
Inhalt
Setup	1
System Debug Menüs	2
Debug Manager	2
Kartenkontrolle	3
AI-Engine-Menü	4
Anpassungen	6
Agentenzahl ändern	6
Projekt-Download schlägt Fehl	7

 
Setup
Das Projekt wurde unter Visual Studio 2022, Version 14.17.6 (Juni 2025) entwickelt. Die einzige installierte Komponente innerhalb der Visual Studio-Installation ist „Desktopentwicklung mit C++“.
Voraussetzungen
Damit das Projekt erfolgreich erstellt werden kann, sind folgende Voraussetzungen zu erfüllen:
•	Visual Studio 2022 (Version 14.17.6 oder kompatibel)
•	vcpkg (für die automatische Verwaltung und Installation externer Bibliotheken)
Projekt öffnen und erstellen
1.	Öffnen Sie die Projektdatei *.sln mit Visual Studio.
2.	Stellen Sie sicher, dass vcpkg korrekt installiert und eingebunden ist.
3.	Wählen Sie die gewünschte Konfiguration (Debug oder Release) und Plattform (x64).
4.	Erstellen Sie das Projekt über Build > Projektmappe erstellen.
Abhängigkeiten
Das Projekt verwendet folgende externe Bibliotheken:
•	SFML – für Grafik, Fenster und Eingabe
•	ImGui – für die GUI
•	nlohmann/json – für die Verarbeitung von JSON-Daten
•	fmt – Formatierung von Zeichenketten
Diese Bibliotheken werden über vcpkg verwaltet und beim ersten Build automatisch installiert, sofern vcpkg korrekt eingebunden ist.
System Debug Menüs
Es gibt vier Debug-Menüs, die jedoch nicht selbsterklärend sind. Daher folgt hier eine kurze Einführung: 
•	Die zwei linken Menüs betreffen die Agenten in der Game Engine.
•	Die zwei rechten Menüs zeigen Informationen aus der AI Engine.
Debug Manager
Das Fenster Debug Manager enthält eine Liste aller aktiven Agenten. Diese können über das „x“ aus der Simulation entfernt werden.
Ein Dropdown-Menü zeigt die Komponenten an, die dem jeweiligen Agenten aktuell zugewiesen sind.
Das darunterliegende „Test-Menü“ zeigt die Positionen aller Agenten an, hat jedoch sonst keine funktionale Bedeutung.

 
Kartenkontrolle
Das in der Abbildung gezeigte Menü steuert alle verfügbaren Kartenansichten.
•	Grid-Zeichnung: Standardmäßig ist die Gitteranzeige aktiviert. Diese kann über das Menü deaktiviert werden.
•	Draw Costs: Zeigt die Kostenwerte aus der CostMap auf dem Spielfeld an.
•	Draw Integration: Visualisiert die Integrationswerte des Flowfields.
→ Nach Auswahl erscheint ein Dropdown-Menü, über das der anzuzeigende Agent ausgewählt werden kann.
•	Draw Flowfield: Funktioniert analog zu „Draw Integration“, zeigt jedoch die Richtungsfelder (Flowfield).
•	Draw TacticalMap: Ermöglicht die Anzeige taktischer Karten.
→ Über das erste Dropdown-Menü kann für jeden Agenten eine beliebige taktische Karte ausgewählt werden.
→ Mit dem Menüpunkt Draw Mode lässt sich zwischen einer numerischen Werteanzeige und einer farbcodierten Darstellung umschalten.
 
AI-Engine-Menü
Diese Abbildung zeigt das Menü der AI Engine. Es besteht aus mehreren Tabs mit spezifischen Informationen:
Global
Zeigt alle Informationen, die im globalen Blackboard gespeichert sind.
•	Über den Select-Button kann versucht werden, die aktuell angezeigte taktische Karte im Flowfield-Menü hervorzuheben.
→ Hinweis: Diese Funktion ist leider nicht zuverlässig, da manche Karten nicht im Menü registriert sind.
Team
Zeigt die Daten aus dem Team-Blackboard des jeweiligen Teams.
Agent Blackboard
Enthält alle Blackboard-Werte des aktuell ausgewählten Agenten.
 
Optionen & Aktionen
Der letzte Tab zeigt Informationen zu:
•	Der aktuell ausgeführten Option des ausgewählten Agenten.
•	Der ausgeführten Aktion, die Teil dieser Option ist.
Die enthaltenen Dropdown-Menüs listen:
1.	Die verfügbaren Optionen.
2.	Den aktuellen Utility-Wert jeder Option.
3.	Die zugehörigen Considerations (Einflussfaktoren).
4.	Den ursprünglichen und den gewichteten Wert jeder Consideration.
Anpassungen
Agentenzahl ändern
Die Anzahl an Agenten wird in Game.cpp in der Funktion initAgents() festgelegt.
 
Beispiel: int flank auf 10 erhöhen. Darunter wird mit minX, maxX und minY, maxY der Bereich angegeben, in dem die Agenten erscheinen.
Agentenverhalten ändern
Standardmäßig sind alle Agenten mit sinnvollen Konfigurationen ausgestattet.
Soll das Verhalten trotzdem verändert werden, ist dies folgendermaßen möglich:
CreateAgent(sf::Vector2f{ (float)x,(float)y },(R"(textures\basic_character.png)"), 1, ("flank_role.json"));
Die letzte Zeichenkette ("flank_role.json") definiert das Verhalten des Agenten.
In der zugehörigen Abbildung sind alle verfügbaren Konfigurationsdateien zu sehen. 
Beispiele für Patrouillen:
•	"standard_patrol" – normale Patrouille
•	"sitting_duck" – bewegungslos
•	"moving_patrol" – bewegt sich zu einer in der Konfiguration angegebenen Position, zeigt aber kein Angriffsverhalten
Für die Erstellung eigener Konfigurationen siehe Kapitel „Konfiguration“ in der Masterarbeit
Projekt-Download schlägt Fehl
Falls der Download über die LRZ-Cloud fehlschlägt, kann das Projekt alternativ über das zugehörige GitHub-Repository heruntergeladen werden. Darauf wird nicht weiterentwickelt.

