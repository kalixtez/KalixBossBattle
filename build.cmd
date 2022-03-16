cd C:\Users\OmGIt\OneDrive\Escritorio\C++ practice\KalixBossBattle

cl main.cpp src\window\EventManager.cpp src\window\Animation.cpp src\script\Script.cpp src\window\GameApp.cpp src\Kalix.cpp src\Entity.cpp /I include /I include\lua /I include\proj_include /I include\SFML\Graphics /I include\SFML\System /I include\SFML\Window /I include\SFML /I include\rapidjson -o debug\LastStar /link sfml-graphics.lib sfml-main.lib sfml-system.lib sfml-window.lib lua.lib /LIBPATH:lib /LIBPATH:lib\lua_lib
