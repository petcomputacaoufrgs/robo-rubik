#ifndef HUMANARDUINOINTERFACE_H
#define HUMANARDUINOINTERFACE_H

#include <string>
#include <list>

class HumanArduinoInterface
{
    public:
        	enum MoveComplete {
        RIGHTUP90 = 'a',
        RIGHTDOWN90 = 'b',
        LEFTUP90 = 'c',
        LEFTDOWN90 = 'd',
        LEFTTOGGLE = 'e',
        RIGHTTOGGLE = 'f',
        FINAL_STATE = 'S'
	};
        HumanArduinoInterface();
        virtual ~HumanArduinoInterface();

        /**
        * serializeCommands:
        * translate a human readable sequence of moves, in a arduino readable sequence of moves
        * first set the humanMoves and after call serializeCommands, the result may be stored in arduinoMoves variable
        */
        virtual void serializeCommands();

        std::string getHumanMoves() { return humanMoves; }
        void setHumanMoves(std::string val) { humanMoves = val; }

        std::string getArduinoMoves() { return arduinoMoves; }
        void setArduinoMoves(std::string val) { arduinoMoves = val; }

    private:
        std::string humanMoves;
        std::string arduinoMoves;

        std::string humanToArduine(std::string cmd);
        std::list<std::string>* splitString(std::string* phrase, char separator);
};

#endif // HUMANARDUINOINTERFACE_H
