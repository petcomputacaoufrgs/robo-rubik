#ifndef HUMANARDUINOINTERFACE_H
#define HUMANARDUINOINTERFACE_H


class HumanArduinoInterface
{
    public:
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
};

#endif // HUMANARDUINOINTERFACE_H
