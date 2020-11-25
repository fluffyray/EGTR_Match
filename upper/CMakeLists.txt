project(EGTR_Match_Upper)

add_executable(EGTR_Match_Upper main.cpp Communicate/serialportdevice.cpp Communicate/botdevice.cpp Communicate/botdevice.h Control/icontroler.h Control/controlerfactor.cpp Control/controlerfactor.h Control/controlerregister.cpp Control/controlerregister.h)