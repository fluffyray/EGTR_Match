project(EGTR_Match_Upper)

add_executable(EGTR_Match_Upper main.cpp Device/serialportdevice.cpp Device/botdevice.cpp Device/botdevice.h Control/icontroler.h Control/controlerfactor.cpp Control/controlerfactor.h Control/controlerregister.cpp Control/controlerregister.h Communication/serialcommunicate.h)