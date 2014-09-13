#include "HumanArduinoInterface.h"

HumanArduinoInterface::HumanArduinoInterface()
{
    humanMoves = "";
    arduinoMoves = "";
}

HumanArduinoInterface::~HumanArduinoInterface()
{
    //dtor
}

void HumanArduinoInterface::serializeCommands() {
	std::list<std::string>* cmdList = splitString(&humanMoves, ' ');
	//for_each(cmdList->begin(), cmdList->end(), humanToArduine);
    for(std::list<std::string>::iterator it = cmdList->begin(); it != cmdList->end(); it++){
		this->arduinoMoves.append(humanToArduine(*it));
	}
	this->arduinoMoves += 'S';
}

std::string HumanArduinoInterface::humanToArduine(std::string a) {
    std::string command("");
      if(!a.compare("U")) {
		    command +=  LEFTTOGGLE;
            command +=  RIGHTUP90;
            command +=  LEFTTOGGLE;
            command +=  RIGHTTOGGLE;
            command +=  RIGHTDOWN90;
            command +=  RIGHTTOGGLE;
			command +=  LEFTTOGGLE;
			command +=  LEFTUP90;
            command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
			command += RIGHTTOGGLE;
            command += RIGHTUP90;
            command += RIGHTTOGGLE;
            command += LEFTTOGGLE;
            command += RIGHTDOWN90;
            command += LEFTTOGGLE;
      } // top left (clock)
      else if (!a.compare("U'")) {
            command +=  LEFTTOGGLE;
            command +=  RIGHTUP90;
            command +=  LEFTTOGGLE;
            command +=  RIGHTTOGGLE;
            command +=  RIGHTDOWN90;
            command +=  RIGHTTOGGLE;
            command +=  LEFTUP90;
            command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
            command +=  LEFTTOGGLE;
            command += RIGHTTOGGLE;
            command += RIGHTUP90;
            command += RIGHTTOGGLE;
            command += LEFTTOGGLE;
            command += RIGHTDOWN90;
            command += LEFTTOGGLE;
      } // top right (anticlock)
      else if (!a.compare("U2")) {
	        command +=  LEFTTOGGLE;
            command +=  RIGHTUP90;
            command +=  LEFTTOGGLE;
            command +=  RIGHTTOGGLE;
            command +=  RIGHTDOWN90;
            command +=  RIGHTTOGGLE;
            command +=  LEFTUP90;
			command +=  LEFTUP90;
            command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
			command += LEFTDOWN90;
            command += LEFTTOGGLE;
            command += RIGHTTOGGLE;
            command += RIGHTUP90;
            command += RIGHTTOGGLE;
            command += LEFTTOGGLE;
            command += RIGHTDOWN90;
            command += LEFTTOGGLE;
        //upper 180 degree
      }
      else if (!a.compare("D'")) {
		  command += RIGHTTOGGLE;
		  command +=  RIGHTUP90;
		  command += RIGHTTOGGLE;
		  command +=  LEFTTOGGLE;
          command +=  RIGHTDOWN90;	//turn the down face to the left claw
		  command +=  LEFTTOGGLE;
			command +=  LEFTUP90;
			command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
            command += RIGHTUP90;
			command +=  LEFTTOGGLE;
            command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
            command += RIGHTTOGGLE;
      } // bottom left (anticlock)
      else if (!a.compare("D" )) {
		  command += RIGHTTOGGLE;
		  command +=  RIGHTUP90;
		  command += RIGHTTOGGLE;
		  command +=  LEFTTOGGLE;
            command +=  RIGHTDOWN90;
			command +=  LEFTUP90;
			command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
			command +=  LEFTTOGGLE;
            command += RIGHTUP90;
			command +=  LEFTTOGGLE;
            command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
            command += RIGHTTOGGLE;
      } // bottom right (clock)
      else if (!a.compare("D2")) {
		  		  command += RIGHTTOGGLE;
		  command +=  RIGHTUP90;
		  command += RIGHTTOGGLE;
		  command +=  LEFTTOGGLE;
          command +=  RIGHTDOWN90;	//turn the down face to the left claw
		  command +=  LEFTTOGGLE;
			command +=  LEFTUP90;
			command +=  LEFTUP90;
			command +=  LEFTTOGGLE;
            command +=  LEFTDOWN90;
            command +=  LEFTDOWN90;
            command += RIGHTUP90;
			command +=  LEFTTOGGLE;
            command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
            command += RIGHTTOGGLE;
        //down 180 degree
      }
      else if (!a.compare("L")) {
		  command += RIGHTTOGGLE;
		  command +=  LEFTUP90;
			command +=  LEFTUP90;	//turn the left face to the right claw
			command += RIGHTTOGGLE;
			command +=  RIGHTUP90;
			command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
			command +=  LEFTDOWN90;
            command +=  LEFTDOWN90;
			command += RIGHTTOGGLE;
      } // left up (anticlock)
      else if (!a.compare("L'" )) {
		  command += RIGHTTOGGLE;
		  command +=  LEFTUP90;
			command +=  LEFTUP90;	//turn the left face to the right claw
			command +=  RIGHTUP90;
			command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
			command += RIGHTTOGGLE;
			command +=  LEFTDOWN90;
            command +=  LEFTDOWN90;
			command += RIGHTTOGGLE;
      } // left down (clocl)
      else if (!a.compare("L2")) {
		  		  command += RIGHTTOGGLE;
		  command +=  LEFTUP90;
			command +=  LEFTUP90;	//turn the left face to the right claw
			command += RIGHTTOGGLE;
			command +=  RIGHTUP90;
			command +=  RIGHTUP90;
			command += RIGHTTOGGLE;
            command += RIGHTDOWN90;
			command += RIGHTDOWN90;
			command +=  LEFTDOWN90;
            command +=  LEFTDOWN90;
			command += RIGHTTOGGLE;
        //left 180 degree
      }
      else if (!a.compare("R" )) {
				command += RIGHTUP90;
				command += RIGHTTOGGLE;
				command += RIGHTDOWN90;
				command += RIGHTTOGGLE;
      } // right up(clock)
      else if (!a.compare("R'")) {
				command += RIGHTTOGGLE;
				command += RIGHTUP90;
				command += RIGHTTOGGLE;
				command += RIGHTDOWN90;
      } // right down (anticlock)
       else if (!a.compare("R2")) {
		   command += RIGHTUP90;
		   command += RIGHTUP90;
				command += RIGHTTOGGLE;
				command += RIGHTDOWN90;
				command += RIGHTDOWN90;
				command += RIGHTTOGGLE;
      } // right 180 degree
      else if (!a.compare("F" )) {
		  command += LEFTTOGGLE;
		  command += RIGHTUP90;
		  command += RIGHTUP90;
		  command +=  LEFTUP90;
		  command += LEFTTOGGLE;
          command +=  LEFTDOWN90;
		  command += LEFTTOGGLE;
		  command += RIGHTDOWN90;
		  command += RIGHTDOWN90;
		  command += LEFTTOGGLE;
      } // front clockwise
      else if (!a.compare("F'")) {
		  command += LEFTTOGGLE;
		  command += RIGHTUP90;
		  command += RIGHTUP90;
		  command += LEFTTOGGLE;
		  command +=  LEFTUP90;
		  command += LEFTTOGGLE;
		  command +=  LEFTDOWN90;
		  command += RIGHTDOWN90;
		  command += RIGHTDOWN90;
		  command += LEFTTOGGLE;
      } // front counterclockwise
      else if (!a.compare("F2")) {
		  command += LEFTTOGGLE;
		  command += RIGHTUP90;
		  command += RIGHTUP90;
		  command += LEFTTOGGLE;
		  command +=  LEFTUP90;
		  command +=  LEFTUP90;
		  command += LEFTTOGGLE;
		  command +=  LEFTDOWN90;
          command +=  LEFTDOWN90;
		  command += RIGHTDOWN90;
		  command += RIGHTDOWN90;
		  command += LEFTTOGGLE;

      } // front 180 degree
      else if (!a.compare("B'" )) {
				command += LEFTUP90;
				command += LEFTTOGGLE;
				command += LEFTDOWN90;
				command += LEFTTOGGLE;
      } // back clockwise (anticlock)
      else if (!a.compare("B")) {
				command += LEFTTOGGLE;
				command += LEFTUP90;
				command += LEFTTOGGLE;
				command += LEFTDOWN90;
      } // back counterclockwise (clock)
      else if (!a.compare("B2")) {
		  command += LEFTUP90;
		  command += LEFTUP90;
				command += LEFTTOGGLE;
				command += LEFTDOWN90;
				command += LEFTDOWN90;
				command += LEFTTOGGLE;

      } // back 180 degree

	return command;
}

std::list<std::string>* HumanArduinoInterface::splitString(std::string* phrase, char separator) {
	std::list<std::string>* listOfWords = new std::list<std::string>();
	std::string tmp = "";
	for(int i = 0; i < phrase->length(); i++){
		if(phrase->at(i) == separator) {
			listOfWords->push_back(tmp);
			tmp = "";
			continue;
		}
		tmp.push_back(phrase->at(i));
	}
	if(!tmp.empty()) {
		listOfWords->push_back(tmp);
	}
	return listOfWords;
}
