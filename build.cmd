CL /SUBSYSTEM:Window main.cpp src\script\Script.cpp src\window\GameApp.cpp src\Kalix.cpp /I include /I include\lua /I include\projinclude /I include\SFML\Graphics /I include\SFML\System /I include\SFML\Window /I include\SFML -o debug\LastStar /link sfml-graphics.lib sfml-main.lib sfml-system.lib sfml-window.lib lua.lib /LIBPATH:lib /LIBPATH:lib\lua_lib 
